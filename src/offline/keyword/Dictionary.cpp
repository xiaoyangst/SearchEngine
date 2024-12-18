#include <fstream>
#include <filesystem>
#include <iostream>
#include "Dictionary.h"
#include <utility>

Dictionary::Dictionary(std::string corpus_dir, std::string dict_path, std::shared_ptr<SplitTool> split_tool)
    : m_corpus_dir(std::move(corpus_dir)), m_dict_path(std::move(dict_path)), m_split_tool(std::move(split_tool)) {}

bool Dictionary::buildMap() {
  // 遍历该目录下的所有文件
  for (const auto &entry : std::filesystem::directory_iterator(m_corpus_dir)) {
    if (entry.is_regular_file()) {
      std::ifstream file(entry.path());
      if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
          auto words = m_split_tool->rmStopWords(line); // 分词
          for (const auto &item : words) {
            m_map[item]++;  // 统计频率
          }
        }
        file.close();
      } else {
        std::cerr << "Failed to open file: " << entry.path() << std::endl;
      }
    }
  }

  return true;
}

bool Dictionary::CreateDictionary() {
  std::ofstream ofs(m_dict_path, std::ios::out);
  if (!ofs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }
  for (const auto &item : m_map) {
    ofs << item.first << " " << item.second << std::endl;
  }
  return true;
}


