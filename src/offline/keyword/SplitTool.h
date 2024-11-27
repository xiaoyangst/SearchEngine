/**
  ******************************************************************************
  * @file           : SplitTool.h
  * @author         : xy
  * @brief          : 分词工具抽象基类：分词
  * @attention      : 应用 策略模式
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITTOOL_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITTOOL_H_
#include <string>
#include <vector>
class SplitTool {
  using Words = std::vector<std::string>;
 protected:
  SplitTool() = default;
  virtual ~SplitTool() = default;
  virtual std::string rmStopWords(std::string& sentence) = 0;  // 去除停用词
  virtual void rinse(std::string &sentence) = 0;  // 清洗
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITTOOL_H_
