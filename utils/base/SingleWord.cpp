#include "SingleWord.h"

size_t SingleWord::nBytecode(const char ch) {
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

Words SingleWord::splitString(const std::string &str) {
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