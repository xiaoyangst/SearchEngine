#include "JiebaSplitCn.h"

JiebaSplitCn::JiebaSplitCn(const std::string &dictPath,
                           const std::string &hmmPath,
                           const std::string &userDictPath,
                           const std::string &idfPath,
                           const std::string &stopWordPath) {
  m_jieba = std::make_unique<cppjieba::Jieba>(
      dictPath, hmmPath, userDictPath, idfPath, stopWordPath
  );
}
JiebaSplitCn::Words JiebaSplitCn::splitWords(const std::string &sentence) {
  std::vector<std::string> words;
  m_jieba->CutAll(sentence, words);
  return words;
}
