#include "WebPageProducer.h"
#include "json.hpp"
using json = nlohmann::json;
WebPageProducer::WebPageProducer()
{
  std::string xml_path = Configure::getInstance()->get("xml_path").value();
  std::string webpage_dict = Configure::getInstance()->get("webpage_dict").value();
  std::string webpage_offset = Configure::getInstance()->get("webpage_offset").value();
  std::string new_webpage_dict = Configure::getInstance()->get("new_webpage_dict").value();
  std::string new_webpage_offset = Configure::getInstance()->get("new_webpage_offset").value();
  std::string webpage_invert = Configure::getInstance()->get("webpage_invert").value();
  std::string simhash_path = Configure::getInstance()->get("simhash_path").value();
  std::string stop_word = Configure::getInstance()->get("stop_word").value();

  m_web_page = std::make_unique<WebPage>(xml_path,webpage_dict);
  m_web_page_offset = std::make_unique<WebPageOffset>(webpage_dict,webpage_offset);
  m_web_page_remove = std::make_unique<WebPageRemove>(webpage_dict, webpage_offset, new_webpage_dict, new_webpage_offset);
  m_split_chinese = std::make_shared<SplitChinese>(stop_word);
  m_web_page_invert = std::make_unique<WebPageInvert>(webpage_invert, new_webpage_dict, new_webpage_offset, m_split_chinese);
}
void WebPageProducer::start() {
  m_web_page->Parse();
  m_web_page->Generate();
  m_web_page_offset->Parse();
  m_web_page_offset->Generate();
  m_web_page_remove->buildNewDict();
  m_web_page_remove->buildNewIndex();
  m_web_page_invert->buildWeight();
  m_web_page_invert->buildMap();
  m_web_page_invert->createInvert();
}


