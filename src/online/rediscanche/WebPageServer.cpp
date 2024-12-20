#include <cmath>
#include <fstream>
#include <unordered_set>
#include "WebPageServer.h"
#include "utils/base/Log.h"
using json = nlohmann::json;

bool WebPageServer::init() {
  std::string new_webpage_dict = Configure::getInstance()->get("new_webpage_dict").value();
  std::string new_webpage_offset = Configure::getInstance()->get("new_webpage_offset").value();
  std::string webpage_invert = Configure::getInstance()->get("webpage_invert").value();
  std::string redis_ip = Configure::getInstance()->get("redis_ip").value();
  std::string redis_port = Configure::getInstance()->get("redis_port").value();
  std::string redis_ttl = Configure::getInstance()->get("redis_ttl").value();
  m_redis_ttl = std::stoi(redis_ttl);

  m_candidatePage = std::make_shared<CandidatePage>(webpage_invert, new_webpage_offset, new_webpage_dict);
  if (!m_candidatePage->preheat()) {
    ERROR_LOG("candidatePage preheat failed");
    return false;
  }

  sw::redis::ConnectionOptions connOpts;
  connOpts.host = redis_ip;
  connOpts.port = std::stoi(redis_port);
  connOpts.socket_timeout = std::chrono::seconds(1);
  m_redis = std::make_shared<sw::redis::Redis>(connOpts);

  if (m_redis->ping() != "PONG") {
    ERROR_LOG("redis connect failed");
    return false;
  }

  return true;
}

std::string WebPageServer::getWebPage(std::string &sentence) {
  // 先走缓存

  if (m_redis->exists(sentence)) {
    std::cout << "keyword 走缓存" << std::endl;
    std::unordered_set<std::string> re;
    m_redis->smembers(sentence, std::inserter(re, re.begin()));
    json data(re);
    return data.dump();
  }

  // 分词
  auto sig_word_vec = SingleWord::splitString(sentence);
  // 交集，得到候选页面
  CandMap result;
  m_candidatePage->CandidatePages(sig_word_vec, result);
  // 计算 sentence 权重序列
  auto sentence_weight = weightSentence(sig_word_vec);
  // 排序
  sortCandidatePage(sentence_weight, result);
  // 将 page 对应的网页信息打包（理论上获取前 10 个）
  json j_array;
  for (int i = 0; i < 10; ++i) {
    if (m_similar_pages.empty()) { break; }
    auto data = m_candidatePage->getWebPageInfo(m_similar_pages.top().page_id); // 走磁盘
    m_redis->sadd(sentence, data); // 记得插入到 redis，以便后续走缓存
    m_redis->expire(sentence,m_redis_ttl);  // 设置过期时间
    j_array.push_back(data);
    j_array.emplace_back(data);
    m_similar_pages.pop();
  }
  // std::cout<<"webpage 走磁盘"<<std::endl;
  return j_array.dump();
}
void WebPageServer::sortCandidatePage(PageWeight &sentence, CandMap &pages) {
  for (const auto &page : pages) {
    auto cosine_val = CosineAlgorithm::CosineSimilarity(sentence, page.second);
    m_similar_pages.push({page.first, cosine_val});
  }
}
PageWeight WebPageServer::weightSentence(const Words &words) {
  std::unordered_map<std::string, unsigned int> tf_map;
  int sum = 0;
  for (const auto &word : words) {
    ++tf_map[word];
    sum++;
  }
  PageWeight result;
  sum == 0 ? sum = 1 : sum;
  for (const auto &weight : tf_map) {
    result[weight.first] = static_cast<double>(weight.second) / sum;  // 频次作为权重
  }
  return result;
}

