#include <iostream>
#include "LRU.h"

LRU::LRU(unsigned int capacity) : m_capacity(capacity) {}

std::optional<std::set<std::string>> LRU::get(const std::string &key) {
  // 查询用 m_map
  auto item = m_map.find(key);
  if (item != m_map.end()) {
    // 查询之后记得更新 m_cache  --> splice 函数 --> 移动到头部
    m_cache.splice(m_cache.begin(), m_cache, item->second);
    return item->second->find(key)->second; // 查询词对应的 匹配集合
  }
  return std::nullopt;  // 不存在的返回标志
}

void LRU::put(const std::string &key,const std::set<std::string> &value) {
  // 查询用 m_map
  // 检查 是否已经存在
  auto item = m_map.find(key);
  if (item != m_map.end()) {
    // 更新 m_cache
    m_cache.splice(m_cache.begin(), m_cache, item->second);
    // 更新 value
    item->second->find(key)->second = value;
    return;
  }
  if (m_cache.size() == m_capacity) { // 触发淘汰机制
    auto delItem = m_cache.back();
    m_cache.pop_back();
    m_map.erase(delItem.begin()->first);
  }

  m_pending.push_front({{key, {value}}});
  m_cache.push_front({{key, {value}}});

  m_map[key] = m_cache.begin(); // 因为是在 头部插入，也就可以直接获取
}

cacheList LRU::getPending() {
  return m_pending;
}
cacheList LRU::getCache() {
  return m_cache;
}

void LRU::clearPending() {
  m_pending.clear();
}
void LRU::clearAll() {
  m_cache.clear();
  m_pending.clear();
  m_map.clear();
}

