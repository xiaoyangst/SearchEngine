/**
  ******************************************************************************
  * @file           : CosineAlgorithm.h
  * @author         : xy
  * @brief          : 余弦相似算法
  * @attention      : None
  * @date           : 2024/12/18
  ******************************************************************************
  */
#ifndef SEARCHENGINE_SRC_ONLINE_SERVER_COSINEALGORITHM_H_
#define SEARCHENGINE_SRC_ONLINE_SERVER_COSINEALGORITHM_H_
#include <unordered_map>
#include <string>
using PageWeight = std::unordered_map<std::string, double>;
class CosineAlgorithm {
 public:
  static double CosineSimilarity(const PageWeight& lhs, const PageWeight& rhs);
};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_COSINEALGORITHM_H_
