/**
  ******************************************************************************
  * @file           : DictionaryEnglish.h
  * @author         : xy
  * @brief          : 生成英文词典文件
  * @attention      : None
  * @date           : 2024/11/29
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYENGLISH_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYENGLISH_H_
#include "Dictionary.h"
class DictionaryEnglish : public Dictionary {
 public:
    DictionaryEnglish(std::string src_path, std::string dict_path, std::string stop_path);
    ~DictionaryEnglish() = default;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYENGLISH_H_
