#include <fstream>
#include <iostream>
#include "KeyWordProducer.h"
#include "json.hpp"
using json = nlohmann::json;
KeyWordProducer::KeyWordProducer(std::string path) : m_path(std::move(path)) {
  json json_parse;
  std::ifstream ifs(m_path);
  if (!ifs.is_open()) {
    std::cerr << "open json file failed" << std::endl;
    return;
  }
  ifs >> json_parse;

  std::string en_stop = json_parse["en_stop"].get<std::string>();
  std::string cn_stop = json_parse["cn_stop"].get<std::string>();
  std::string en_corpus = json_parse["en_corpus"].get<std::string>();
  std::string cn_corpus = json_parse["cn_corpus"].get<std::string>();
  std::string en_dict = json_parse["en_dict"].get<std::string>();
  std::string cn_dict = json_parse["cn_dict"].get<std::string>();
  std::string en_invert = json_parse["en_invert"].get<std::string>();
  std::string cn_invert = json_parse["cn_invert"].get<std::string>();

  std::string jieba_json = json_parse["jieba_json"].get<std::string>();

  std::shared_ptr<SplitTool> en_split_tool = std::make_shared<SplitEnglish>(en_stop);
  m_en_dictionary = std::make_unique<Dictionary>(en_corpus, en_dict, en_split_tool);

  std::shared_ptr<SplitTool> cn_split_tool = std::make_shared<SplitChinese>(cn_stop,jieba_json);
  m_cn_dictionary = std::make_unique<Dictionary>(cn_corpus, cn_dict, cn_split_tool);

  m_en_invertIndex = std::make_unique<InvertIndex>(en_dict, en_invert);
  m_cn_invertIndex = std::make_unique<InvertIndex>(cn_dict, cn_invert);
}
void KeyWordProducer::start() {
  buildEnglish();
  buildChinese();
}
void KeyWordProducer::buildEnglish() {
  m_en_dictionary->buildMap();
  m_en_dictionary->CreateDictionary();

  m_en_invertIndex->buildInvertIndex();
  m_en_invertIndex->createInvertIndex();
}
void KeyWordProducer::buildChinese() {
  m_cn_dictionary->buildMap();
  m_cn_dictionary->CreateDictionary();

  m_cn_invertIndex->buildInvertIndex();
  m_cn_invertIndex->createInvertIndex();
}
