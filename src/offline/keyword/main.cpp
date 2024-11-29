#include "DictionaryEnglish.h"
#include "json.hpp"
#include "DictionaryChinese.h"
using nlohmann::json;

int main() {

  std::string src = "sources/project/corpus/en/English.txt";
  std::string dict = "data/en.txt";
  std::string stop = "sources/project/dict/stop_words.utf8";
  DictionaryEnglish dictionaryEnglish(src,dict,stop);
  dictionaryEnglish.buildMap();
  dictionaryEnglish.CreateDictionary();


  std::string asrc = "sources/project/corpus/cn/C3-Art0002.txt";
  std::string adict = "data/zn.txt";
  std::string astop = "sources/project/dict/stop_words.utf8";
  std::string ajieba = "conf/jieba.json";
  DictionaryChinese dictionaryen(asrc,adict,astop,ajieba);
  dictionaryen.buildMap();
  dictionaryen.CreateDictionary();
  return 0;
}