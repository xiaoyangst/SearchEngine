/**
  ******************************************************************************
  * @file           : WebPageInvert.h
  * @author         : xy
  * @brief          : 生成网页倒排索引库
  * @attention      : None
  * @date           : 2024/12/2
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEINVERT_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEINVERT_H_
#include <string>
#include <unordered_map>
#include <set>
#include <memory>
#include "utils/splitword/SplitTool.h"
#include "utils/base/WordWeight.h"
using WebPageInvertMap = std::unordered_map<std::string, std::set<std::pair<int, double>>>;
class WebPageInvert {
 public:
  WebPageInvert(std::string invert_path,
                std::string new_webpage_path, std::string new_webpage_index_path,
                std::shared_ptr<SplitTool> split_tool);
  ~WebPageInvert() = default;
  bool buildWeight();
  bool buildMap();
  bool createInvert();
 private:
  std::string m_invert_path;
  std::string m_new_webpage_path;
  std::string m_new_webpage_index_path;
  WebPageInvertMap m_webpage_invert;
  std::shared_ptr<SplitTool> m_split_tool;  // 分词工具
  WordWeight m_word_weight;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEINVERT_H_
