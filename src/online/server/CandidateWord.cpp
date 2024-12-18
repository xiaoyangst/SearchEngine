#include "CandidateWord.h"
#include "utils/base/Log.h"
#include <fstream>
CandidateWord::CandidateWord(std::string m_dict_path, std::string invert_path)
    : m_dict_path(std::move(m_dict_path)), m_invert_path(std::move(invert_path)) {

}
bool CandidateWord::preheat() {

  std::ifstream invert_ifs(m_invert_path);
  if (!invert_ifs.is_open()) {
    ERROR_LOG("open %s failed!", m_invert_path.c_str());
    return false;
  }
  std::ifstream dict_ifs(m_dict_path);
  if (!dict_ifs.is_open()) {
    ERROR_LOG("open %s failed!", m_dict_path.c_str());
    return false;
  }

  // 预热

  std::string invert_line;
  while (getline(invert_ifs, invert_line)) {
    std::string word;
    std::istringstream iss(invert_line);
    iss >> word;
    unsigned int index;
    while (iss >> index) {
      m_invert_map[word].insert(index);
    }
  }

  std::string dict_line;
  static int index = 0;
  while (getline(dict_ifs, dict_line)) {
    std::string word;
    unsigned int fre;
    std::istringstream iss(dict_line);
    iss >> word >> fre;
    m_dict_map[index++] = std::make_pair(word,fre);
  }



  return true;
}
void CandidateWord::CandidateWords(const Words &words,CandVec & result) {

  std::unordered_set<unsigned int> gather;
  for (auto &word : words) {
    if (m_invert_map.find(word) != m_invert_map.end()) {
      gather.insert(m_invert_map[word].begin(), m_invert_map[word].end());  // 并集
    }
  }

  // 根据索引得到实际 word
  for (auto &index : gather) {
    result.push_back(m_dict_map[index]);
  }
}
