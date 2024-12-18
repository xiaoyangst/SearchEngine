#include <cmath>
#include <fstream>
#include "WebPageServer.h"
#include "utils/base/Log.h"
using json = nlohmann::json;
WebPageServer::WebPageServer(std::string path)
    : m_path(std::move(path)) {

}

std::string WebPageServer::getWebPage(std::string &sentence) {
  // 交集
  auto sig_word_vec = SingleWord::splitString(sentence);
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
    j_array.push_back(m_candidatePage->getWebPageInfo(m_similar_pages.top().page_id));
    m_similar_pages.pop();
  }
  return j_array.dump();
}
bool WebPageServer::init() {
  std::ifstream ifs(m_path);
  if (!ifs.is_open()) {
    ERROR_LOG("open json file %s failed", m_path.c_str());
    return false;
  }

  json parse;
  ifs >> parse;

  std::string new_webpage_dict = parse["new_webpage_dict"].get<std::string>();
  std::string new_webpage_offset = parse["new_webpage_offset"].get<std::string>();
  std::string webpage_invert = parse["webpage_invert"].get<std::string>();

  m_candidatePage = std::make_shared<CandidatePage>(webpage_invert, new_webpage_offset, new_webpage_dict);

  return true;
}
void WebPageServer::sortCandidatePage(PageWeight &sentence, CandMap &pages) {
  for (const auto& page:pages) {
    auto cosine_val = CosineAlgorithm::CosineSimilarity(sentence, page.second);
    std::cout << page.first << " " << cosine_val << std::endl;
    m_similar_pages.push({page.first, cosine_val});
  }
}
PageWeight WebPageServer::weightSentence(const Words &words) {
  // TF
  std::unordered_map<std::string, unsigned int> tf_map;
  for (const auto &word : words) {
    ++tf_map[word];
  }
  // DF 都为 1
  // int fd = 1;
  // IDF
  //auto idf = std::log2(0.5) = -1;
  // Weight
  PageWeight result;
  for (const auto &weight : tf_map) {
    std::cout << weight.first << " " << weight.second << std::endl;
    result[weight.first] = weight.second;
  }
  return result;
}

