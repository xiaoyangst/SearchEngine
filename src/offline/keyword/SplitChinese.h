/**
  ******************************************************************************
  * @file           : SplitChinese.h
  * @author         : xy
  * @brief          : 中文分词
  * @attention      : 中文需要分词
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITCHINESE_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITCHINESE_H_

#include <string>
#include <vector>
#include <unordered_set>
#include "SplitTool.h"
#include "JiebaSplitCn.h"

class SplitChinese : public SplitTool {
  using Words = std::vector<std::string>;
 public:
  explicit SplitChinese(std::string stop_path, std::string json_path);
  ~SplitChinese() = default;
  Words rmStopWords(std::string &sentence) override; // 去除停用词
 private:
  void rinse(std::string &sentence) override; // 清洗 \r 和 \n
  Words splitWords(std::string &sentence); // 分词
 private:
  std::string m_json_path;  // cppjieba.json 路径
  std::unordered_set<std::string> m_stop_words; // 停用词集合，用以查询
  std::shared_ptr<JiebaSplitCn> m_jieba;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITCHINESE_H_
