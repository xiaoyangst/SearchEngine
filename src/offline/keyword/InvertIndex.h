/**
  ******************************************************************************
  * @file           : InvertIndex.h
  * @author         : xy
  * @brief          : 创建词典索引文件
  * @attention      : None
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_INVERTINDEX_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_INVERTINDEX_H_
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "utils/base/noncopyable.h"
class InvertIndex : public noncopyable{
  using Words = std::vector<std::string>;
  using invertIndexMap = std::unordered_map<std::string , std::unordered_set<unsigned int>>;
 public:
  explicit InvertIndex(std::string dict_path, std::string index_path);
  ~InvertIndex() = default;
  bool buildInvertIndex();
  bool createInvertIndex();
 protected:
  std::string m_dict_path;
  std::string m_index_path;
  invertIndexMap m_invert_index_map;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_INVERTINDEX_H_
