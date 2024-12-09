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
  static size_t nBytecode(const char ch) {
    int nBytes = 1;
    if (ch & (1 << 7)) {
      for (int idx = 0; idx != 6; ++idx) {
        if (ch & (1 << (6 - idx))) {
          ++nBytes;
        } else {
          break;
        }
      }
    }
    return nBytes;
  }

  static Words splitString(const std::string &str) {
    size_t i = 0;
    Words words;
    while (i < str.size()) {
      size_t bytes = nBytecode(str[i]);
      std::string substring = str.substr(i, bytes);
      // 检查字符串是否由数字组成
      if (std::all_of(substring.begin(), substring.end(), ::isdigit)) {
        i += bytes;
        continue; // 跳过数字字符串
      }
      words.push_back(substring);
      i += bytes;
    }
    return words;
  }
};
#endif //SEARCHENGINE_UTILS_BASE_SINGLEWORD_H_
