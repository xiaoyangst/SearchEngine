#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SplitEnglish.h"
using Words = std::vector<std::string>;

SplitEnglish::SplitEnglish(std::string stop_path)
    : SplitTool(std::move(stop_path)) {
  std::ifstream ifs(m_stop_path);
  if (!ifs.is_open()) {
    std::cerr << "open stop words file failed" << std::endl;
    return;
  }
  std::string line;
  while (getline(ifs, line)) {
    m_stop_words.insert(line);
  }
}

// 非英文字母和数字转换为空格，英文字母转换为小写
void SplitEnglish::rinse(std::string &sentence) {
  for (auto &item : sentence) {
    if (!isalnum(item)) {
      item = ' ';
    } else if (isalpha(item) && isupper(item)) {
      item = tolower(item);
    }
  }
}

Words SplitEnglish::rmStopWords(std::string &sentence) {
  rinse(sentence);
  std::stringstream ss(sentence);
  std::string word;
  Words new_sentence;
  while (ss >> word) {
    if (m_stop_words.find(word) == m_stop_words.end()) {  // 不是停用词
      new_sentence.push_back(word);
    }
  }
  return new_sentence;
}
