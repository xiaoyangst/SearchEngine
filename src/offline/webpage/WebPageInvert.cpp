#include <utility>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include "WebPageInvert.h"
#include "utils/base/SingleWord.h"

WebPageInvert::WebPageInvert(std::string invert_path,
                             std::string new_webpage_path,
                             std::string new_webpage_index_path,
                             std::shared_ptr<SplitTool> split_tool)
    : m_invert_path(std::move(invert_path)),
      m_new_webpage_path(std::move(new_webpage_path)),
      m_new_webpage_index_path(std::move(new_webpage_index_path)),
      m_split_tool(std::move(split_tool)) {
  buildWeight();
}

bool WebPageInvert::buildWeight() {
  std::ifstream webpage_ifs(m_new_webpage_path);
  if (!webpage_ifs.is_open()) {
    std::cerr << "open webpage file failed" << std::endl;
    return false;
  }

  std::ifstream index_ifs(m_new_webpage_index_path);
  if (!index_ifs.is_open()) {
    std::cerr << "open index file failed" << std::endl;
    return false;
  }

  std::string line;
  std::istringstream iss;
  unsigned int webpages = 0;

  // 遍历所有 webpage
  while (getline(index_ifs, line)) {
    iss.clear();
    unsigned int id;
    unsigned int start;
    unsigned int length;
    iss.str(line);
    iss >> id >> start >> length;
    webpage_ifs.seekg(start, std::ios::beg);
    std::vector<char> buffer(length);
    webpage_ifs.read(buffer.data(), length);
    std::string content(buffer.begin(), buffer.end());  // content 中包含一个 webpage所有内容

    auto words = m_split_tool->rmStopWords(content);  // 分词
    for (const auto &word : words) {
      auto data = SingleWord::splitString(word);
      for (const auto &ch : data) { // 得到单个词
        m_word_weight.TF(ch, id);
      }
    }
    webpages = id + 1;
  }
  m_word_weight.buildDF();
  m_word_weight.buildIDF(webpages);
  m_word_weight.buildWeight();

  return true;
}

bool WebPageInvert::buildMap() {
  std::ifstream webpage_ifs(m_new_webpage_path);
  if (!webpage_ifs.is_open()) {
    std::cerr << "open webpage file failed" << std::endl;
    return false;
  }

  std::ifstream index_ifs(m_new_webpage_index_path);
  if (!index_ifs.is_open()) {
    std::cerr << "open index file failed" << std::endl;
    return false;
  }

  std::string line;
  std::istringstream iss;
  unsigned int webpages = 0;

  // 遍历所有 webpage
  while (getline(index_ifs, line)) {
    iss.clear();
    unsigned int id;
    unsigned int start;
    unsigned int length;
    iss.str(line);
    iss >> id >> start >> length;
    webpage_ifs.seekg(start, std::ios::beg);
    std::vector<char> buffer(length);
    webpage_ifs.read(buffer.data(), length);
    std::string content(buffer.begin(), buffer.end());  // content 中包含一个 webpage所有内容

    auto words = m_split_tool->rmStopWords(content);  // 分词
    for (const auto &word : words) {
      auto data = SingleWord::splitString(word);
      for (std::string &ch : data) { // 得到单个词
        if (m_webpage_invert.find(ch) == m_webpage_invert.end()) {  // 没有就插入，有就跳过即可
          m_webpage_invert[ch].insert({id, m_word_weight.Weight(ch)});
        }
      }
    }
  }

  return true;
}

bool WebPageInvert::createInvert() {
  std::ofstream ofs(m_invert_path);
  if (!ofs.is_open()) {
    std::cerr << "open file failed" << std::endl;
    return false;
  }

  for (const auto &kItem : m_webpage_invert) {
    for (const auto &vItem : kItem.second) {
      ofs << kItem.first << " " << vItem.first << " " << vItem.second << std::endl;
    }
  }
  return true;
}
