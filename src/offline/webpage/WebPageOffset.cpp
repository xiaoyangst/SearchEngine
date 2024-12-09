#include <fstream>
#include <iostream>
#include <sstream>
#include "WebPageOffset.h"
WebPageOffset::WebPageOffset(std::string webpage_dict, std::string dst)
    : m_webpage_dict(std::move(webpage_dict)), m_dst(std::move(dst)) {

}


void WebPageOffset::Parse() {
  std::ifstream ifs(m_webpage_dict);
  if (!ifs.is_open()) {
    std::cerr << "open " << m_webpage_dict << " failed" << std::endl;
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
      m_offset[docID++] = {docStart, docEnd-docStart};
      inDoc = false;
    }
    cur_offset += line.size() + 1;  // 换行符得 + 1
  }
}

void WebPageOffset::Generate() {
  std::ofstream ofs(m_dst);
  if (!ofs.is_open()){
    std::cerr << "open " << m_dst << " failed" << std::endl;
    return;
  }

  //int docid = 0;
  std::ostringstream oss;
  for (const auto &item : m_offset) {
    oss << item.first << " " << item.second.first << " " << item.second.second << "\n";
  }
  ofs << oss.str();
}