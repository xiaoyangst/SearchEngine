#include "WordWeight.h"

void WordWeight::buildTF(const std::string &word, unsigned int id) {
  auto it = m_tf_map.find(word);
  if (it != m_tf_map.end()) {
    it->second[id].tf++;
  } else {
    m_tf_map[word].insert({id, {.tf = 1}});
  }
}

void WordWeight::buildDF() {
  for (const auto &kItem : m_tf_map) {
    m_df_map[kItem.first].df = kItem.second.size();
  }
}

void WordWeight::buildIDF(unsigned int webpages) {
  for (const auto &kItem : m_df_map) {
    m_idf_map[kItem.first].idf = std::log2((webpages / (kItem.second.df + 1)) + 1);
  }
}

void WordWeight::allWordsWeight() {
  for (const auto &kItem : m_tf_map) {
    for (const auto &item : kItem.second) {
      auto it = m_idf_map.find(kItem.first);
      if (it != m_idf_map.end()) {
        m_weight_sum_map[item.first].push_back({.weight = item.second.tf * it->second.idf});  // 同一篇文章下的单词的权重集合
      }
    }
  }

  for (const auto &it : m_weight_sum_map) {
    double sum_of_squares = 0.0;
    for (const auto &w : it.second) {
      sum_of_squares += (w.weight * w.weight);
    }
    m_sqrt_weight_map[it.first].weight += std::sqrt(sum_of_squares);
  }
}