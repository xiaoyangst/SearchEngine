#include <unordered_set>
#include "WebPageServer.h"
#include "utils/base/Log.h"
using json = nlohmann::json;

WebPageServer::WebPageServer() {
  if (!init()) {
    ERROR_LOG("webpage init failed");
    return;
  }
}

bool WebPageServer::init() {
  std::string new_webpage_dict = Configure::getInstance()->get("new_webpage_dict").value();
  std::string new_webpage_offset = Configure::getInstance()->get("new_webpage_offset").value();
  std::string webpage_invert = Configure::getInstance()->get("webpage_invert").value();
  std::string lru_capacity = Configure::getInstance()->get("lru_capacity").value();

  int lru_capacity_int = std::stoi(lru_capacity);
  m_lru = std::make_unique<LRU>(lru_capacity_int);
  m_candidatePage = std::make_shared<CandidatePage>(webpage_invert, new_webpage_offset, new_webpage_dict);
  if (!m_candidatePage->preheat()) {
    ERROR_LOG("candidatePage preheat failed");
    return false;
  }

  return true;
}

std::string WebPageServer::getWebPage(std::string &sentence) {
  // 走缓存
  std::lock_guard<std::mutex> lock_guard(m_mtx);
  auto cache_data = m_lru->get(sentence);
  if (cache_data != std::nullopt) {
    std::cout << "webpage 走缓存" << std::endl;
    json j_array(cache_data.value());
    return j_array.dump();
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
    m_lru->put(sentence, data);
    j_array.emplace_back(data);
    m_similar_pages.pop();
  }
  std::cout << "webpage 走磁盘" << std::endl;
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

cacheList WebPageServer::getPending() {
  std::lock_guard<std::mutex> lock_guard(m_mtx);
  return m_lru->getPending();
}


cacheList WebPageServer::getCache() {
  std::lock_guard<std::mutex> lock_guard(m_mtx);
  return m_lru->getCache();
}