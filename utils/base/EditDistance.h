/**
  ******************************************************************************
  * @file           : EditDistance.h
  * @author         : xy
  * @brief          : 最小编辑距离算法
  * @attention      : 不需要创建该对象
  * @date           : 2024/12/17
  ******************************************************************************
  */
#ifndef SEARCHENGINE_SRC_ONLINE_SERVER_EDITDISTANCE_H_
#define SEARCHENGINE_SRC_ONLINE_SERVER_EDITDISTANCE_H_
#include <string>
class EditDistance {
 public:
  static int editDistance(const std::string &lhs, const std::string &rhs);
 private:
  static size_t nBytesCode(const char ch);
  static std::size_t length(const std::string &str);
  static int triple_min(const int &a, const int &b, const int &c);
};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_EDITDISTANCE_H_
