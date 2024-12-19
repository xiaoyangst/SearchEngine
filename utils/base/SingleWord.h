//
// Created by xy on 2024/12/8.
//

#ifndef SEARCHENGINE_UTILS_BASE_SINGLEWORD_H_
#define SEARCHENGINE_UTILS_BASE_SINGLEWORD_H_
#include <vector>
#include <string>
#include <algorithm>
using Words = std::vector<std::string>;
class SingleWord {
 public:
  static size_t nBytecode(char ch);
  static Words splitString(const std::string &str);
};
#endif //SEARCHENGINE_UTILS_BASE_SINGLEWORD_H_
