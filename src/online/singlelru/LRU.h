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
class LRU {
  using cacheList = std::list<std::pair<std::string, std::string>>;
  using cacheMap = std::unordered_map<std::string, cacheList::iterator>;
 public:
  explicit LRU(unsigned int capacity);
  void put(const std::string& key, const std::string& value);
  std::optional<std::string> get(const std::string& key);
 private:
  unsigned int m_capacity;
  cacheList m_cache;
  cacheMap m_map;
};

#endif //SEARCHENGINE_SRC_ONLINE_SINGLELRU_LRU_H_
