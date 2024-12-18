#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "InvertIndex.h"
#include "utils/base/SingleWord.h"

InvertIndex::InvertIndex(std::string dict_path, std::string index_path)
  :m_dict_path(std::move(dict_path)),m_index_path(std::move(index_path))
{

}


bool InvertIndex::buildInvertIndex() {
  std::ifstream ifs(m_dict_path);
  if (!ifs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }
  std::string line;
  static unsigned int index = 0;  // 所在行
  while (getline(ifs, line)) {
    std::string word;
    std::istringstream ss(line);
    ss >> word; // 读取第一个字符串即可
    Words data = SingleWord::splitString(word); // 单个词的集合
    for (const auto &ch : data) {
      m_invert_index_map[ch].insert(index); // 没有会自动创建 key
    }
    ++index;
  }
  return true;
}

bool InvertIndex::createInvertIndex() {
  std::ofstream ofs(m_index_path);
  if (!ofs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }
  for (const auto &item : m_invert_index_map) {
    ofs << item.first << " ";
    for (const auto index : item.second) {
      ofs << index << " ";
    }
    ofs << "\n";
  }
  return true;
}