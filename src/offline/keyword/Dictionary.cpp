#include <fstream>
#include <filesystem>
#include <iostream>
#include "Dictionary.h"
#include <utility>

Dictionary::Dictionary(std::string corpus_dir, std::string dict_path, std::shared_ptr<SplitTool> split_tool)
    : m_corpus_dir(std::move(corpus_dir)), m_dict_path(std::move(dict_path)), m_split_tool(std::move(split_tool)) {

}

bool Dictionary::buildMap() {
  // 遍历该目录下的所有文件
  for (const auto &entry : std::filesystem::directory_iterator((m_corpus_dir))) {
    if (entry.is_regular_file()) {
      std::ifstream file(entry.path());
      file.seekg(0, std::ios::end);
      std::streampos file_size = file.tellg();
      file.seekg(0, std::ios::beg);
      std::string content(file_size, '\0');
      file.read(content.data(), file_size); //读取整个文件内容
      auto words = m_split_tool->rmStopWords(content); // 分词
      for (const auto &item : words) {
        m_map[item]++;  // 统计频率
      }
      file.close();
    } else {
      std::cerr << "Failed to open file: " << entry.path() << std::endl;
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


