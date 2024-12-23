#include "LRU.h"

LRU::LRU(unsigned int capacity) : m_capacity(capacity) {}

std::optional<std::string> LRU::get(const std::string& key) {
  if (m_map.find(key) != m_map.end()) {
    // 将访问的元素移至缓存的前端
    auto it = m_map[key];
    m_cache.splice(m_cache.begin(), m_cache, it);
    return it->second;
  }
  return std::nullopt;  // 不存在的返回标志
}

void LRU::put(const std::string& key, const std::string& value) {
  // 检查 是否已经存在
  auto item = m_map.find(key);
  if (item != m_map.end()) {
    // 更新 m_cache
    m_cache.splice(m_cache.begin(), m_cache, item->second);
    // 更新 value
    item->second->second = value;
    return;
  }
  if (m_cache.size() == m_capacity) { // 触发淘汰机制
    auto delItem = m_cache.back();
    m_cache.pop_back();
    m_map.erase(delItem.first);
  }
  m_cache.emplace_front(key,value);
  m_map[key] = m_cache.begin(); // 因为是在 头部插入，也就可以直接获取
}