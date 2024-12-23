/**
  ******************************************************************************
  * @file           : LRU.h
  * @author         : xy
  * @brief          : LRU 缓存
  * @attention      : None
  * @date           : 2024/12/21
  ******************************************************************************
  */
#ifndef SEARCHENGINE_SRC_ONLINE_SINGLELRU_LRU_H_
#define SEARCHENGINE_SRC_ONLINE_SINGLELRU_LRU_H_
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <set>
using cacheList = std::list<std::unordered_map<std::string, std::set<std::string>>>;
using cacheMap = std::unordered_map<std::string, cacheList::iterator>;
class LRU {
 public:
  explicit LRU(unsigned int capacity);
  void put(const std::string& key,const std::set<std::string>& value);
  std::optional<std::set<std::string>> get(const std::string& key);
  cacheList getPending(); // cacheManager 需要
  cacheList getCache();
  void clearPending();
 public:
  void clearAll();
 private:
  unsigned int m_capacity;
  cacheList m_cache;
  cacheList m_pending;
  cacheMap m_map;
};

#endif //SEARCHENGINE_SRC_ONLINE_SINGLELRU_LRU_H_
