#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SplitEnglish.h"
SplitEnglish::SplitEnglish(std::string stop_path) : m_stop_path(std::move(stop_path)) {
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


std::string SplitEnglish::rmStopWords(std::string &sentence) {
  rinse(sentence);
  std::stringstream ss(sentence);
  std::string word;
  std::string new_sentence;
  while (ss >> word) {
    rinse(word);
    if (m_stop_words.find(word) == m_stop_words.end()) {  // 不是停用词
      if (!new_sentence.empty()) {
        new_sentence += " " + word;
      }else{
        new_sentence = word;
      }
    }
  }
  return new_sentence;
}
