/**
  ******************************************************************************
  * @file           : KeyWordProducer.h
  * @author         : xy
  * @brief          : 对外提供的唯一的类
  * @attention      : None
  * @date           : 2024/11/26
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_KEYWORDPRODUCER_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_KEYWORDPRODUCER_H_
#include "utils/splitword/SplitChinese.h"
#include "utils/splitword/SplitEnglish.h"
#include "utils/base/Configure.h"
#include "Dictionary.h"
#include "InvertIndex.h"
#include "utils/base/noncopyable.h"
class KeyWordProducer : public noncopyable{
 public:
  explicit KeyWordProducer();
  ~KeyWordProducer() = default;
  void start();
 private:
  void buildEnglish();
  void buildChinese();
 private:
  std::unique_ptr<Dictionary> m_en_dictionary;
  std::unique_ptr<Dictionary> m_cn_dictionary;
  std::unique_ptr<InvertIndex> m_en_invertIndex;
  std::unique_ptr<InvertIndex> m_cn_invertIndex;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_KEYWORDPRODUCER_H_
