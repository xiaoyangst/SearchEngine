#include <iostream>
#include "KeyWordProducer.h"
#include "json.hpp"
using json = nlohmann::json;
KeyWordProducer::KeyWordProducer() {

  std::string en_stop = Configure::getInstance()->get("en_stop").value();
  std::string cn_stop = Configure::getInstance()->get("cn_stop").value();
  std::string en_corpus = Configure::getInstance()->get("en_corpus").value();
  std::string cn_corpus = Configure::getInstance()->get("cn_corpus").value();
  std::string en_dict = Configure::getInstance()->get("en_dict").value();
  std::string cn_dict = Configure::getInstance()->get("cn_dict").value();
  std::string en_invert = Configure::getInstance()->get("en_invert").value();
  std::string cn_invert = Configure::getInstance()->get("cn_invert").value();

  std::shared_ptr<SplitTool> en_split_tool = std::make_shared<SplitEnglish>(en_stop);
  m_en_dictionary = std::make_unique<Dictionary>(en_corpus, en_dict, en_split_tool);

  std::shared_ptr<SplitTool> cn_split_tool = std::make_shared<SplitChinese>(cn_stop);
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
