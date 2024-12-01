#include "json.hpp"
#include "Dictionary.h"
#include "SplitEnglish.h"
#include "SplitChinese.h"
#include "InvertIndex.h"


int main() {



  //==================build dictionary==================

  std::string src = "sources/project/corpus/en/English.txt";
  std::string dict = "data/en.txt";
  std::string stop = "sources/project/dict/stop_words.utf8";
  std::shared_ptr<SplitTool> en_split_tool = std::make_shared<SplitEnglish>(stop);
  Dictionary dictionaryEnglish(src, dict, en_split_tool);
  dictionaryEnglish.buildMap();
  dictionaryEnglish.CreateDictionary();

  std::string asrc = "sources/project/corpus/cn/C3-Art0002.txt";
  std::string adict = "data/zn.txt";
  std::string astop = "sources/project/dict/stop_words.utf8";
  std::string ajieba = "conf/jieba.json";
  std::shared_ptr<SplitTool> cn_split_tool = std::make_shared<SplitChinese>(astop, ajieba);
  Dictionary dictionaryChinese(asrc, adict, cn_split_tool);
  dictionaryChinese.buildMap();
  dictionaryChinese.CreateDictionary();


  //=====================build invertIndex=====================
  std::string m_dict = "data/en.txt";
  std::string m_invert_index_file = "data/en_invert_index.txt";
  std::shared_ptr<InvertIndex> enInvert = std::make_shared<InvertIndex>(m_dict, m_invert_index_file);
  enInvert->buildInvertIndex();
  enInvert->createInvertIndex();


  std::string m_dict_c = "data/zn.txt";
  std::string m_invert_index_file_c = "data/cn_invert_index.txt";
  std::shared_ptr<InvertIndex> enInvert_c = std::make_shared<InvertIndex>(m_dict_c, m_invert_index_file_c);
  enInvert_c->buildInvertIndex();
  enInvert_c->createInvertIndex();

  return 0;
}