/**
  ******************************************************************************
  * @file           : CandidatePage.h
  * @author         : xy
  * @brief          : 候选页面
  * @attention      : None
  * @date           : 2024/12/18
  ******************************************************************************
  */
#ifndef SEARCHENGINE_SRC_ONLINE_SERVER_CANDIDATEPAGE_H_
#define SEARCHENGINE_SRC_ONLINE_SERVER_CANDIDATEPAGE_H_
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "utils/base/noncopyable.h"
using WebPageInvertMap = std::unordered_map<std::string, std::unordered_map<int, double>>;
using WebPageOffsetMap = std::map<int,std::pair<unsigned int,unsigned int>>;
using Words = std::vector<std::string>;
using UnionSet = std::unordered_map<std::string, std::set<int>>;
using CandMap = std::map<int, std::unordered_map<std::string , double>>;  // 交集后
class CandidatePage : public noncopyable{
 public:
  CandidatePage(std::string invert_path, std::string offset_path,std::string dict_path);
  ~CandidatePage() = default;
  bool preheat();
  void CandidatePages(const Words& words,CandMap& result);
  std::string getWebPageInfo(int page_id);
 private:
  std::string m_invert_path;
  std::string m_offset_path;
  std::string m_dict_path;
  std::unique_ptr<std::ifstream> m_dict_ifs;
  WebPageInvertMap m_webpage_invert;
  WebPageOffsetMap m_offset;
  UnionSet m_union_set;
 public:
  FRIEND_TEST(CandidatePageTest, CandidatePages);
};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_CANDIDATEPAGE_H_
