#include <condition_variable>
#include <thread>
#include <chrono>
#include "WebPageRemove.h"

WebPageRemove::WebPageRemove(std::string dict_path, std::string index_path,
                             std::string new_dict_path, std::string new_index_path)
    : m_dict_path(std::move(dict_path)),
      m_index_path(std::move(index_path)),
      m_new_dict_path(std::move(new_dict_path)),
      m_new_index_path(std::move(new_index_path)) {

  std::string dict = Configure::getInstance()->get("dict").value();
  std::string hmm = Configure::getInstance()->get("hmm").value();
  std::string idf = Configure::getInstance()->get("idf").value();
  std::string stop_words = Configure::getInstance()->get("stop_words").value();

  m_simhasher = std::make_shared<SimHashWebPage>(dict, hmm, idf, stop_words);
}
void WebPageRemove::buildNewDict() {
  // 根据索引读取网页，然后去重
  std::ifstream dict_ifs(m_dict_path);
  if (!dict_ifs.is_open()) {
    std::cerr << "open dict file failed" << std::endl;
    return;
  }
  std::ifstream index_ifs(m_index_path);
  if (!index_ifs.is_open()) {
    std::cerr << "open index file failed" << std::endl;
    return;
  }
  std::ofstream new_dict_ifs(m_new_dict_path);
  if (!new_dict_ifs.is_open()) {
    std::cerr << "open new dict file failed" << std::endl;
    return;
  }

  // 获取 index 中起始和要读取的长度
  std::string line;
  std::istringstream iss;
  while (getline(index_ifs, line)) {
    iss.clear();
    int id;
    int start;
    int length;
    iss.str(line);
    iss >> id >> start >> length;
    dict_ifs.seekg(start, std::ios::beg);
    std::vector<char> buffer(length);
    dict_ifs.read(buffer.data(), length);
    std::string content(buffer.begin(), buffer.end());
    auto simhash = m_simhasher->getSimHash(content);
    if (m_hash_set.find(simhash) == m_hash_set.end()) {
      m_hash_set.insert(simhash);
      new_dict_ifs << content;
    }
  }
  m_hash_set.clear();
}
void WebPageRemove::buildNewIndex() {
  std::ifstream ifs(m_new_dict_path);
  if (!ifs.is_open()) {
    std::cerr << "open new dict file failed" << std::endl;
    return;
  }
  std::ofstream new_index_ofs(m_new_index_path);
  if (!new_index_ofs.is_open()) {
    std::cerr << "open new index file failed" << std::endl;
    return;
  }
  std::string line;
  unsigned int cur_offset = 0;
  unsigned int docStart = 0;
  int docID = 0;
  bool inDoc = false; // 标记是否在一个 <doc> 段落内

  while (std::getline(ifs, line)) {
    if (line.find("<doc>") != std::string::npos) {
      docStart = cur_offset;
      inDoc = true;
    }
    if (line.find("</doc>") != std::string::npos && inDoc) {
      unsigned int docEnd = cur_offset + line.size() + 1; // 换行符得 + 1
      new_index_ofs << docID++ << " " << docStart << " " << docEnd - docStart << "\n";
      inDoc = false;
    }
    cur_offset += line.size() + 1;  // 换行符得 + 1
  }
}
