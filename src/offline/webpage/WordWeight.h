/**
  ******************************************************************************
  * @file           : WordWeight.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024/12/10
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WORDWEIGHT_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WORDWEIGHT_H_
#include <string>
#include <unordered_map>
#include <cmath>
#include <list>
#include "utils/base/noncopyable.h"
class WebPageInvert;
class WordWeight : public noncopyable{
  friend class WebPageInvert;
 private:
  struct WEIGHT {
    double weight;
  };
  struct TF {
    unsigned int tf;
  };
  struct DF {
    unsigned int df;
  };
  struct IDF {
    double idf;
  };
 public:
  WordWeight() = default;
  ~WordWeight() = default;
  void buildTF(const std::string &word, unsigned int id);
  void buildDF();
  void buildIDF(unsigned int webpages);
  void allWordsWeight();
 private:
  std::unordered_map<std::string, std::unordered_map<unsigned int, TF>> m_tf_map; // <字符-<webpage_id,次数>>
  std::unordered_map<std::string, DF> m_df_map;
  std::unordered_map<std::string, IDF> m_idf_map;
  std::unordered_map<unsigned int, std::list < WEIGHT>> m_weight_sum_map;
  std::unordered_map<unsigned int, WEIGHT> m_sqrt_weight_map;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WORDWEIGHT_H_
