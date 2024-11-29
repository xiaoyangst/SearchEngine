#include <fstream>
#include <iostream>
#include "Dictionary.h"
#include <utility>

Dictionary::Dictionary(std::string src_path,std::string dict_path,std::shared_ptr<SplitTool> split_tool)
  :m_src_path(std::move(src_path))
  ,m_dict_path(std::move(dict_path))
  ,m_split_tool(std::move(split_tool))
{}

bool Dictionary::CreateDictionary() {
  std::ofstream ofs(m_dict_path,std::ios::out);
  if (!ofs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }
  for (const auto &item : m_map) {
    ofs << item.first << " " << item.second << std::endl;
  }
  return true;
}

bool Dictionary::buildMap() {
  std::ifstream ifs(m_src_path);
  if (!ifs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }
  std::string line;
  while (getline(ifs, line)) {
    auto words = m_split_tool->rmStopWords(line);
    for (const auto& item : words){
      m_map[item]++;
    }
  }
  return true;
}
