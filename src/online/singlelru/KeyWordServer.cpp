#include "KeyWordServer.h"
#include "utils/base/Log.h"
#include "utils/base/EditDistance.h"
bool KeyWordServer::init() {

  std::string en_dict_path = Configure::getInstance()->get("en_dict").value();
  std::string en_invert_path = Configure::getInstance()->get("en_invert").value();
  std::string cn_dict_path = Configure::getInstance()->get("cn_dict").value();
  std::string cn_invert_path = Configure::getInstance()->get("cn_invert").value();
  std::string lru_capacity = Configure::getInstance()->get("lru_capacity").value();
  int lru_capacity_int = std::stoi(lru_capacity);
  m_lru = std::make_unique<LRU>(lru_capacity_int);
  m_en_candidateWord = std::make_shared<CandidateWord>(en_dict_path, en_invert_path);
  m_cn_candidateWord = std::make_shared<CandidateWord>(cn_dict_path, cn_invert_path);

  if (!m_en_candidateWord->preheat()) {
    ERROR_LOG("en candidateWord preheat failed");
    return false;
  }
  if (!m_cn_candidateWord->preheat()) {
    ERROR_LOG("cn candidateWord preheat failed");
    return false;
  }

  return true;
}

std::string KeyWordServer::getKeyWord(std::string &word) {
  // 走缓存
  std::unique_lock<std::mutex> uq_lock(m_mtx);
  auto cache_data = m_lru->get(word);
  if (cache_data != std::nullopt) {
    std::cout<<"keyword 走缓存"<<std::endl;
    json j_array(cache_data.value());
    return j_array.dump();
  }
  // 分词

  auto sig_word_vec = SingleWord::splitString(word);
  CandVec result;
  m_cn_candidateWord->CandidateWords(sig_word_vec, result);
  m_en_candidateWord->CandidateWords(sig_word_vec, result);
  // 排序
  sortCandidateWord(result, word);
  // 理论上取前面十个
  json j_array;
  for (int i = 0; i < 10; ++i) {
    if (m_result.empty()) { break; }
    auto data = m_result.top().word;
    m_lru->put(word, data);
    j_array.push_back(data);
    m_result.pop();
  }
  std::cout<<"keyword 走磁盘"<<std::endl;
  return j_array.dump();
}
/*
 * 比较规则：
 *  a.优先比较最小编辑距离
 *  b.在编辑距离相同的条件下，再比较候选词的词频；词频越大优先选择
 *  c.在词频相同的条件下，按字母表顺序比较候选词
 */
void KeyWordServer::sortCandidateWord(CandVec &words, const std::string &key_word) {
  for (const auto &word : words) {
    int sim = EditDistance::editDistance(key_word, word.first);
    struct SimilarityWord sim_word = {
        .word = word.first,
        .similarity = sim,
        .frequency = word.second
    };
    m_result.push(sim_word);
  }
}


