//
// Created by xy on 2024/12/8.
//

#ifndef SEARCHENGINE_UTILS_BASE_WORDWEIGHT_H_
#define SEARCHENGINE_UTILS_BASE_WORDWEIGHT_H_
#include <string>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include <iostream>
using TfMap = std::unordered_map<std::string, std::unordered_map<unsigned int, unsigned int >>;
class WordWeight {
 public:
  WordWeight() = default;
  ~WordWeight() = default;
  double Weight(std::string &word){
    auto it = m_weight_map.find(word);
    if (it != m_weight_map.end()) {
      return it->second;
    }
    return 0.0;
  }
  // 某个词在 webpage 中出现的词
  void TF(const std::string &word, unsigned int id) {
    auto it = m_tf_map.find(word);
    if (it != m_tf_map.end()) {
      it->second[id]++;
    } else {
      m_tf_map[word].insert({id, 1});
    }
  }
  // 某个词在所有 webpage 中出现的次数，即包含该词语的文档数量
  void buildDF() {
    for (const auto &kItem : m_tf_map) {
      m_df_map[kItem.first] = kItem.second.size();
    }
  }
  void buildIDF(unsigned int webpages) {
    for (const auto &kItem : m_df_map) {
      m_idf_map[kItem.first] = std::log2((webpages / (kItem.second + 1)) + 1);
    }
  }

  //TODO 归一化待处理
  void buildWeight() {
    for (const auto &kItem : m_idf_map) {
      unsigned int sum = 0;
      auto item = m_tf_map.find(kItem.first);
        if (item != m_tf_map.end()) {
          for (const auto &vItem : item->second) {
            sum += vItem.second * vItem.second;
          }
        }
        m_weight_map[kItem.first] = sum;
    }
  }
 private:
  TfMap m_tf_map; // <字符-<webpage_id,次数>>
  std::unordered_map<std::string, unsigned int> m_df_map;
  std::unordered_map<std::string, double> m_idf_map;
  std::unordered_map<std::string, double> m_weight_map;
};
#endif //SEARCHENGINE_UTILS_BASE_WORDWEIGHT_H_
