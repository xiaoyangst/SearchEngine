#include "LRU.h"

LRU::LRU(unsigned int capacity) : m_capacity(capacity) {}

std::optional<std::unordered_set<std::string>> LRU::get(std::string key) {
  // 查询用 m_map
  auto item = m_map.find(key);
  if (item != m_map.end()) {
    // 查询之后记得更新 m_cache  --> splice 函数 --> 移动到头部
    m_cache.splice(m_cache.begin(), m_cache, item->second);
    return item->second->second;
  }
  return std::nullopt;  // 不存在的返回标志
}

void LRU::put(std::string key, std::string value) {
  // 检查 是否已经存在
  auto item = m_map.find(key);
  if (item != m_map.end()) {
    // 更新 m_cache
    m_cache.splice(m_cache.begin(), m_cache, item->second);
    // 更新 value
    item->second->second.insert(value);
    return;
  }
  if (m_cache.size() == m_capacity) { // 触发淘汰机制
    auto delItem = m_cache.back();
    m_cache.pop_back();
    m_map.erase(delItem.first);
  }
  m_cache.push_front({key, {value}});

  m_map[key] = m_cache.begin(); // 因为是在 头部插入，也就可以直接获取
}