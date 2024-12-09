#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "WebPage.h"
WebPage::WebPage(std::string xml_dir, std::string dst)
    : m_xml_dir(std::move(xml_dir)), m_dst(std::move(dst)) {

}
void WebPage::Parse() {
  static int docid = 0;
  for (const auto &entry : std::filesystem::directory_iterator(m_xml_dir)) {
    if (entry.is_regular_file()) {  // 判断是文件
      if (m_doc.LoadFile(entry.path().c_str()) != XML_SUCCESS) {
        std::cerr << "Failed to load file: " << entry.path() << std::endl;
        continue;
      }

      XMLElement *channel = m_doc.FirstChildElement("rss")->FirstChildElement("channel");
      if (!channel) {
        std::cerr << "<channel> element not found." << std::endl;
        return;
      }

      for (auto item = channel->FirstChildElement("item"); item != nullptr; item = item->NextSiblingElement("item")) {
        const char *title = item->FirstChildElement("title") ? item->FirstChildElement("title")->GetText() : "";
        const char *link = item->FirstChildElement("link") ? item->FirstChildElement("link")->GetText() : "";
        const char *content = item->FirstChildElement("content") ? item->FirstChildElement("content")->GetText() : "";
        const char *descriptionText = item->FirstChildElement("description") ? item->FirstChildElement("description")->GetText() : "";

        std::string m_title = title ? title : "";
        std::string m_link = link ? link : "";
        std::string m_content = content ? content : "";
        std::string m_description = rinse(descriptionText ? descriptionText : "");

        m_infos.emplace(docid++,WebPageInfo(m_title, m_link, m_description, m_content));
      }
    } else {
      std::cerr << "Failed to open file: " << entry.path() << std::endl;
    }
  }
}

//TODO 清洗还不够干净
std::string WebPage::rinse(const std::string &input) {
  std::string noHtml;
  noHtml.reserve(input.size());
  bool inTag = false;
  for (char c : input) {
    if (c == '<') inTag = true;
    else if (c == '>') inTag = false;
    else if (!inTag) noHtml += c;
  }

  static const std::unordered_map<std::string, std::string> htmlEntities = {
      {"&#8211;", "-"},
      {"&#8217;", "'"}
  };
  for (const auto &entity : htmlEntities) {
    auto pos = noHtml.find(entity.first);
    while (pos != std::string::npos) {
      noHtml.replace(pos, entity.first.size(), entity.second);
      pos = noHtml.find(entity.first, pos + entity.second.size());
    }
  }

  return noHtml;
}


void WebPage::Generate() {
  std::ofstream file(m_dst, std::ios::out);
  if (!file.is_open()) {
    std::cerr << "Failed to open file for writing." << std::endl;
    return;
  }
  int docid = 0;
  std::ostringstream buffer;
  for (const auto &item : m_infos) {
    buffer << "<doc>\n"
           << "\t<docid>" << docid++ << "</docid>\n"
           << "\t<title>" << item.second.m_title << "</title>\n"
           << "\t<link>" << item.second.m_link << "</link>\n"
           << "\t<description>" << item.second.m_description << "</description>\n"
           << "\t<content>" << item.second.m_content << "</content>\n"
           << "</doc>\n";
  }
  file << buffer.str();
}
