/**
  ******************************************************************************
  * @file           : WebPage.h
  * @author         : xy
  * @brief          : 生成网页库
  * @attention      : None
  * @date           : 2024/12/2
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGE_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGE_H_
#include <string>
#include <tinyxml2.h>
#include <vector>
#include <unordered_map>
using namespace tinyxml2;
struct WebPageInfo {
  std::string m_title;
  std::string m_link;
  std::string m_description;
  std::string m_content;
  WebPageInfo(std::string title, std::string link, std::string description, std::string content)
    :m_title(std::move(title))
    ,m_link(std::move(link))
    ,m_description(std::move(description))
    ,m_content(std::move(content)) {}
};

class WebPage {
 public:
  WebPage(std::string xml_dir, std::string dst);
  ~WebPage() = default;
  void Parse();
  void Generate();
 private:
  std::string rinse(const std::string& input);
 private:
  std::string m_xml_dir;
  std::string m_dst;
  XMLDocument m_doc;
  std::unordered_map<int,WebPageInfo> m_infos;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGE_H_
