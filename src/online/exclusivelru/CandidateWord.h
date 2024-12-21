/**
  ******************************************************************************
  * @file           : CandidateWord.h
  * @author         : xy
  * @brief          : 候选词
  * @attention      : 拿到的关键词是已分词，即单个词组成的集合
  * @date           : 2024/12/16
  ******************************************************************************
  */
#ifndef SEARCHENGINE_PREHEAT_H
#define SEARCHENGINE_PREHEAT_H
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include "gtest/gtest.h"
#include "utils/base/noncopyable.h"
using CandVec = std::vector<std::pair<std::string,unsigned int >>;
using Words = std::vector<std::string>;
using invertIndexMap = std::unordered_map<std::string, std::unordered_set<unsigned int>>;
using dictMap = std::unordered_map<unsigned int ,std::pair<std::string,unsigned int>>;
class CandidateWord : public noncopyable{
 public:
  CandidateWord(std::string m_dict_path, std::string invert_path);
  ~CandidateWord() = default;
  void CandidateWords(const Words& words,CandVec & result);
  bool preheat();
 private:
  std::string m_dict_path;
  std::string m_invert_path;
  invertIndexMap m_invert_map; // 获取多个集合
  dictMap m_dict_map; //  通过索引获取对应的词和词频
 public:
  FRIEND_TEST(CandidateWordTest, CandidateWords);
};

#endif //SEARCHENGINE_PREHEAT_H
