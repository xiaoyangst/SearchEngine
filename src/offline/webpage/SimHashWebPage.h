/**
  ******************************************************************************
  * @file           : SimHashWebPage.h
  * @author         : xy
  * @brief          : simhash 封装
  * @attention      : None
  * @date           : 2024/12/7
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_SIMHASHWEBPAGE_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_SIMHASHWEBPAGE_H_
#include <string>
#include <memory>
#include "simhash/Simhasher.hpp"
using namespace simhash;
class SimHashWebPage {
 public:
  SimHashWebPage(const std::string &dictPath,const std::string &hmmPath,
                 const std::string &idfPath,const std::string &stopWordPath);
  ~SimHashWebPage() = default;
  uint64_t getSimHash(const std::string &sentence,size_t TopN = 5);
  bool isEqual(uint64_t hash1,uint64_t hash2);
 private:
  std::shared_ptr<Simhasher> m_simhasher;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_SIMHASHWEBPAGE_H_
