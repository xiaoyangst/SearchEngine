/**
  ******************************************************************************
  * @file           : SplitEnglish.h
  * @author         : xy
  * @brief          : 英文分词
  * @attention      : 英文不用分词
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITENGLISH_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITENGLISH_H_

#include "SplitTool.h"
#include <unordered_set>

class SplitEnglish : public SplitTool {
  using Words = std::vector<std::string>;
 public:
  explicit SplitEnglish(std::string stop_path);
  ~SplitEnglish() = default;
 private:
  void rinse(std::string &sentence) override; // 清洗
 public:
  std::string rmStopWords(std::string &sentence) override;  // 去除停用词
 private:
  std::string m_stop_path;  // 停用词路径
  std::unordered_set<std::string> m_stop_words; // 方便查询，在构造函数中初始化
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITENGLISH_H_
