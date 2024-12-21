#include "CandidatePage.h"
#include "utils/base/Log.h"
#include <iostream>
#include <fstream>

CandidatePage::CandidatePage(std::string invert_path, std::string offset_path, std::string dict_path)
    : m_invert_path(std::move(invert_path)), m_offset_path(std::move(offset_path)), m_dict_path(std::move(dict_path)) {}

bool CandidatePage::preheat() {
  std::ifstream offset_file(m_offset_path);
  if (!offset_file.is_open()) {
    ERROR_LOG("open offset file %s failed", m_offset_path.c_str());
    return false;
  }
  std::ifstream invert_file(m_invert_path);
  if (!invert_file.is_open()) {
    ERROR_LOG("open invert file %s failed", m_invert_path.c_str());
    return false;
  }
  m_dict_ifs = std::make_unique<std::ifstream>(m_dict_path);
  if (!m_dict_ifs->is_open()) {
    ERROR_LOG("open dict file %s failed", m_dict_path.c_str());
    return false;
  }

  // 预热
  offset_file.seekg(0, std::ios::end);
  auto offset_size = offset_file.tellg();
  offset_file.seekg(0, std::ios::beg);
  std::string offset_data(offset_size, 0);
  offset_file.read(offset_data.data(), offset_size);
  std::istringstream offset_stream(offset_data);
  std::string offset_line;
  while (getline(offset_stream, offset_line)) {
    int page_index;
    unsigned int start;
    unsigned int end;
    std::istringstream iss(offset_line);
    iss >> page_index >> start >> end;
    m_offset[page_index] = std::make_pair(start, end);

  }

  invert_file.seekg(0, std::ios::end);
  auto invert_size = invert_file.tellg();
  invert_file.seekg(0, std::ios::beg);
  std::string invert_data(invert_size, 0);
  invert_file.read(invert_data.data(), invert_size);
  std::istringstream invert_stream(invert_data);
  std::string invert_line;
  while (getline(invert_stream, invert_line)) {
    std::string word;
    int page_index;
    double weight;
    std::istringstream iss(invert_line);
    iss >> word >> page_index >> weight;
    m_webpage_invert[word].insert(std::make_pair(page_index, weight));
    m_union_set[word].insert(page_index);
  }

  return true;
}

void CandidatePage::CandidatePages(const Words &words, CandMap &result) {
  std::set<int> intersection_set;
  for (const auto &word : words) {
    auto page_weight_set = m_union_set.find(word);
    if (page_weight_set != m_union_set.end()) {
      if (intersection_set.empty()) {
        intersection_set = page_weight_set->second;  // 初次赋值
      } else {
        std::set<int> tmp;
        std::set_intersection(intersection_set.begin(), intersection_set.end(),
                              page_weight_set->second.begin(), page_weight_set->second.end(),
                              std::inserter(tmp, tmp.end()));
        intersection_set = std::move(tmp);
      }
    }
  } // 保证  intersection_set 存储的页面（id） 必然包含所有的 words

  for (const auto& word : words) {  // TODO 严格审查此处代码
    auto page_weight_set = m_webpage_invert.find(word);
    if (page_weight_set != m_webpage_invert.end()) {
      for (auto doc_id : intersection_set) {  // 有价值的页面
        auto word_weight = page_weight_set->second.find(doc_id);
        if (word_weight != page_weight_set->second.end()) {
          result[doc_id].insert(std::make_pair(word, word_weight->second));
        }
      }
    }
  }
}
std::string CandidatePage::getWebPageInfo(int page_id) {
  // 先去 走 Redis 缓存

  // 发现没有，再往下执行 走磁盘

  auto iter = m_offset.find(page_id);
  if (iter != m_offset.end()) {
    auto start = iter->second.first;
    auto end = iter->second.second;
    m_dict_ifs->seekg(start, std::ios::beg);
    std::string word(end, 0);
    m_dict_ifs->read(word.data(), end);
    m_dict_ifs->seekg(0, std::ios::beg);
    return word;
  }
  return "";
}
