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
 public:
  explicit SplitTool(std::string stop_path);
  virtual ~SplitTool() = default;
  virtual Words rmStopWords(std::string& sentence) = 0;  // 去除停用词
  virtual void rinse(std::string &sentence) = 0;  // 清洗
 protected:
  std::string m_stop_path;  // 停用词路径
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_SPLITTOOL_H_
