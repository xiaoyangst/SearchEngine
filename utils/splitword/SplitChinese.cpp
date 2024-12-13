#include <fstream>
#include <iostream>
#include "SplitChinese.h"
#include "json.hpp"

using json = nlohmann::json;
using Words = std::vector<std::string>;

SplitChinese::SplitChinese(std::string stop_path)
    : SplitTool(std::move(stop_path)) {

  std::ifstream stop_ifs(m_stop_path);
  if (!stop_ifs.is_open()) {
    std::cerr << "open stop words file failed" << std::endl;
    return;
  }

  // 加载停用词
  std::string line;
  while (getline(stop_ifs, line)) {
    m_stop_words.insert(line);
  }
}

std::vector<std::string> SplitChinese::splitWords(std::string &sentence) {
  rinse(sentence);
  return JiebaSplitCn::getInstance()->splitWords(sentence);
}

Words SplitChinese::rmStopWords(std::string &sentence) {
  Words words = splitWords(sentence);
  Words res;
  for (auto &word : words) {
    if (word == " ") continue;
    if (m_stop_words.find(word) == m_stop_words.end()) {
      res.push_back(word);
    }
  }
  return res;
}
void SplitChinese::rinse(std::string &sentence) {
  sentence.erase(std::remove_if(sentence.begin(), sentence.end(), [](char c) {
    return c == '\r' || c == '\n';
  }), sentence.end());
}
