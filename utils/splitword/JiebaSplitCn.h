/**
  ******************************************************************************
  * @file           : JiebaSplitCn.h
  * @author         : xy
  * @brief          : jieba 操作的封装
  * @attention      : None
  * @date           : 2024/11/27
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_JIEBASPLITCN_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_JIEBASPLITCN_H_
#include <string>
#include <vector>
#include "json.hpp"
#include "cppjieba/Jieba.hpp"
using json = nlohmann::json;
class JiebaSplitCn {
  using Words = std::vector<std::string>;
 public:
  explicit JiebaSplitCn(const std::string& dictPath, const std::string& userDictPath, const std::string& hmmPath,
                        const std::string& idfPath, const std::string& stopWordPath);
  ~JiebaSplitCn() = default;
  Words splitWords(const std::string &sentence);
 private:
  std::unique_ptr<cppjieba::Jieba> m_jieba;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_JIEBASPLITCN_H_
