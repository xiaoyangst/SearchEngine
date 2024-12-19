#include "JiebaSplitCn.h"
#include "cppjieba/Jieba.hpp"

// 写死，不读配置文件处理
std::string cppjiebb_dict = "sources/project/dict/jieba.dict.utf8";
std::string cppjieba_hmm = "sources/project/dict/hmm_model.utf8";
std::string cppjieba_user = "sources/project/dict/user.dict.utf8";
std::string cppjieba_idf = "sources/project/dict/idf.utf8";
std::string cppjieba_stop_words = "sources/project/dict/stop_words.utf8";

JiebaSplitCn::JiebaSplitCn() {
  m_jieba = std::make_unique<cppjieba::Jieba>(
      cppjiebb_dict, cppjieba_hmm, cppjieba_user, cppjieba_idf, cppjieba_stop_words);
}
JiebaSplitCn::Words JiebaSplitCn::splitWords(const std::string &sentence) {
  std::vector<std::string> words;
  m_jieba->CutAll(sentence, words);
  return words;
}
