#include <cmath>
#include <iostream>
#include "CosineAlgorithm.h"
double CosineAlgorithm::CosineSimilarity(const PageWeight &lhs, const PageWeight &rhs) {
  double son = 0;
  double l_mom = 0;
  double r_mom = 0;

  for (const auto &lvalue : lhs) {
    auto it = rhs.find(lvalue.first);
    if (it != rhs.end()) {
      son += lvalue.second * it->second;
      l_mom += lvalue.second * lvalue.second;
      r_mom += it->second * it->second;
    }
  }

  double denominator = sqrt(l_mom) * sqrt(r_mom);
  if (denominator == 0) {
    return 0.0;  // 或者返回一个其他适当的值，取决于你对零向量相似度的处理需求
  }
  return son / denominator;

}
