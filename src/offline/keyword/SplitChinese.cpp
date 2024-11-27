#include <fstream>
#include <iostream>
#include "SplitChinese.h"
#include "json.hpp"

using json = nlohmann::json;

SplitChinese::SplitChinese(std::string stop_path, std::string json_path)
    : m_stop_path(std::move(stop_path)), m_json_path(std::move(json_path)) {
  std::ifstream json_ifs(m_json_path);
  if (!json_ifs.is_open()) {
    std::cerr << "open jieba json file failed" << std::endl;
    return;
  }

  std::ifstream stop_ifs(m_stop_path);
  if (!stop_ifs.is_open()) {
    std::cerr << "open stop words file failed" << std::endl;
    return;
  }

  // 初始化分词器（cppjieba）
  json json_parse;
  json_ifs >> json_parse;
  m_jieba = std::make_shared<JiebaSplitCn>(json_parse["dict"].get<std::string>(),
                                           json_parse["hmm"].get<std::string>(),
                                           json_parse["user"].get<std::string>(),
                                           json_parse["idf"].get<std::string>(),
                                           json_parse["stop_words"].get<std::string>());

  // 加载停用词
  std::string line;
  while (getline(stop_ifs, line)) {
    m_stop_words.insert(line);
  }
}

std::vector<std::string> SplitChinese::splitWords(std::string &sentence) {
  rinse(sentence);
  return m_jieba->splitWords(sentence);
}

std::string SplitChinese::rmStopWords(std::string &sentence) {
    std::vector<std::string> words = splitWords(sentence);
    std::string res;
    for (auto word : words) {
      if (word == " ") continue;
      if (m_stop_words.find(word) == m_stop_words.end()) {
        if (!res.empty()) {
          res += " " + word;
        } else{
          res += word;
        }
      }
    }
  return res;
}
void SplitChinese::rinse(std::string &sentence) {
  sentence.erase(std::remove_if(sentence.begin(), sentence.end(), [](char c) {
    return c == '\r' || c == '\n';
  }), sentence.end());
}
