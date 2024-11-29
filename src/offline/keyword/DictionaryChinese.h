/**
  ******************************************************************************
  * @file           : DictionaryChinese.h
  * @author         : xy
  * @brief          : 生成中文词典文件
  * @attention      : None
  * @date           : 2024/11/29
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYCHINESE_H_
#define SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYCHINESE_H_
#include "Dictionary.h"
class DictionaryChinese : public Dictionary{
 public:
  DictionaryChinese(std::string src_path,std::string dict_path,std::string stop_path,std::string json_path);
  ~DictionaryChinese() = default;
};

#endif //SEARCHENGINE_SRC_OFFLINE_KEYWORD_DICTIONARYCHINESE_H_
