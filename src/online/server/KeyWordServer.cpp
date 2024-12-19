#include "KeyWordServer.h"
#include "utils/base/Log.h"
#include "EditDistance.h"
bool KeyWordServer::init() {

  std::string en_dict_path = Configure::getInstance()->get("en_dict").value();
  std::string en_invert_path = Configure::getInstance()->get("en_invert").value();
  std::string cn_dict_path = Configure::getInstance()->get("cn_dict").value();
  std::string cn_invert_path = Configure::getInstance()->get("cn_invert").value();

  m_en_candidateWord = std::make_shared<CandidateWord>(en_dict_path, en_invert_path);
  m_cn_candidateWord = std::make_shared<CandidateWord>(cn_dict_path, cn_invert_path);

  if (!m_en_candidateWord->preheat()) { return false; }
  if (!m_cn_candidateWord->preheat()) { return false; }

  return true;
}

std::string KeyWordServer::getKeyWord(std::string &word) {
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
    j_array.push_back(m_result.top().word);
    m_result.pop();
  }
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


