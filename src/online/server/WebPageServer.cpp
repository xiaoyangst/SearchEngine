#include <cmath>
#include <fstream>
#include "WebPageServer.h"
#include "utils/base/Log.h"
using json = nlohmann::json;


std::string WebPageServer::getWebPage(std::string &sentence) {
  // 交集
  auto sig_word_vec = SingleWord::splitString(sentence);
  CandMap result;
  m_candidatePage->CandidatePages(sig_word_vec, result);  // TODO result 为空
  // 计算 sentence 权重序列
  auto sentence_weight = weightSentence(sig_word_vec);
  // 排序
  sortCandidatePage(sentence_weight, result);
  // 将 page 对应的网页信息打包（理论上获取前 10 个）
  json j_array;
  for (int i = 0; i < 10; ++i) {
    if (m_similar_pages.empty()) { break; }
    j_array.push_back(m_candidatePage->getWebPageInfo(m_similar_pages.top().page_id));
    m_similar_pages.pop();
  }
  return j_array.dump();
}
bool WebPageServer::init() {
  std::string new_webpage_dict = Configure::getInstance()->get("new_webpage_dict").value();
  std::string new_webpage_offset = Configure::getInstance()->get("new_webpage_offset").value();
  std::string webpage_invert = Configure::getInstance()->get("webpage_invert").value();

  m_candidatePage = std::make_shared<CandidatePage>(webpage_invert, new_webpage_offset, new_webpage_dict);
  m_candidatePage->preheat();
  return true;
}

void WebPageServer::sortCandidatePage(PageWeight &sentence, CandMap &pages) {
  for (const auto& page:pages) {
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

