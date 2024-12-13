/**
  ******************************************************************************
  * @file           : WebPageOffset.h
  * @author         : xy
  * @brief          : 生成网页偏移库
  * @attention      : None
  * @date           : 2024/12/2
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEOFFSET_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEOFFSET_H_
#include <string>
#include <map>
#include "utils/base/noncopyable.h"
class WebPageOffset : public noncopyable{
 public:
  WebPageOffset(std::string webpage_dict,std::string dst);
  ~WebPageOffset() = default;
  void Parse();
  void Generate();
 private:
  std::string m_webpage_dict;
  std::string m_dst;
  std::map<int,std::pair<unsigned int,unsigned int>> m_offset;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEOFFSET_H_
