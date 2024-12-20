/**
  ******************************************************************************
  * @file           : WebPageServer.h
  * @author         : xy
  * @brief          : None
  * @attention      : None
  * @date           : 2024/12/18
  ******************************************************************************
  */
#ifndef SEARCHENGINE_SRC_ONLINE_SERVER_WEBPAGESERVER_H_
#define SEARCHENGINE_SRC_ONLINE_SERVER_WEBPAGESERVER_H_
#include <string>
#include <memory>
#include <queue>
#include <istream>
#include "CandidatePage.h"
#include "utils/base/SingleWord.h"
#include "utils/base/Configure.h"
#include "CosineAlgorithm.h"
#include <sw/redis++/redis++.h>
#include "utils/base/json.hpp"
struct SimilarityPage {
  int page_id;  // 页面 id
  double cosine_val;  // 余弦值，值越小越相似，越靠前

  bool operator<(const SimilarityPage &rhs) const {
    return cosine_val > rhs.cosine_val;
  }
};

class WebPageServer {
 public:
  WebPageServer() = default;
  bool init();
  std::string getWebPage(std::string &sentence);
 private:
  PageWeight weightSentence(const Words& words);
  void sortCandidatePage(PageWeight& sentence,CandMap& pages);
 private:
  std::shared_ptr<CandidatePage> m_candidatePage;
  std::priority_queue<SimilarityPage> m_similar_pages;
  CandMap m_sentence_weight;
  std::shared_ptr<sw::redis::Redis> m_redis;
 private:

};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_WEBPAGESERVER_H_
