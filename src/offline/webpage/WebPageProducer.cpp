#include "WebPageProducer.h"
#include "json.hpp"
using json = nlohmann::json;
WebPageProducer::WebPageProducer(std::string path)
  :m_path(std::move(path))
{
  json json_parse;
  std::ifstream ifs(m_path);
  if (!ifs.is_open()) {
    std::cerr << "open json file failed" << std::endl;
    return;
  }
  ifs >> json_parse;

  std::string xml_path = json_parse["xml_path"].get<std::string>();
  std::string webpage_dict = json_parse["webpage_dict"].get<std::string>();
  std::string webpage_offset = json_parse["webpage_offset"].get<std::string>();
  std::string new_webpage_dict = json_parse["new_webpage_dict"].get<std::string>();
  std::string new_webpage_offset = json_parse["new_webpage_offset"].get<std::string>();
  std::string webpage_invert = json_parse["webpage_invert"].get<std::string>();
  std::string simhash_path = json_parse["simhash_path"].get<std::string>();
  std::string stop_word = json_parse["stop_word"].get<std::string>();
  std::string jieba_json = json_parse["jieba_json"].get<std::string>();

  m_web_page = std::make_unique<WebPage>(xml_path,webpage_dict);
  m_web_page_offset = std::make_unique<WebPageOffset>(webpage_dict,webpage_offset);
  m_web_page_remove = std::make_unique<WebPageRemove>(webpage_dict, webpage_offset, new_webpage_dict, new_webpage_offset,simhash_path);
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


