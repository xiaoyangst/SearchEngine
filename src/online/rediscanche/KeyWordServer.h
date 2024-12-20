/**
  ******************************************************************************
  * @file           : KeyWordServer.h
  * @author         : xy
  * @brief          : 关键字服务
  * @attention      : TcpServer 负责把客户端发送的词传到此类; 单个词用 SingleWord 类的静态函数即可
  * @date           : 2024/12/16
  ******************************************************************************
  */

#ifndef SEARCHENGINE_KEYWORDSERVER_H
#define SEARCHENGINE_KEYWORDSERVER_H
#include <memory>
#include <queue>
#include "utils/base/json.hpp"
#include "CandidateWord.h"
#include "utils/base/Configure.h"
#include "utils/base/SingleWord.h"
#include "utils/splitword/SplitChinese.h"
#include "utils/splitword/SplitEnglish.h"
#include <sw/redis++/redis++.h>
using json = nlohmann::json;

struct SimilarityWord{
  std::string word;
  int similarity; // 相似度
  unsigned int frequency; // 词频

  bool operator<(const SimilarityWord& rhs) const { // TODO 好好弄清楚
    if(this->similarity < rhs.similarity){
      return false;
    }else if (this->similarity > rhs.similarity){
      return true;
    }
    if (this->frequency > rhs.frequency){
      return false;
    }else if (this->frequency < rhs.frequency){
      return true;
    }
    return this->word > rhs.word;
  }

};
class KeyWordServer {
 public:
  explicit KeyWordServer() = default;
  bool init();
  std::string getKeyWord(std::string& word); // 放入一个 json 的array中
 private:
  void sortCandidateWord(CandVec & words,const std::string& key_word);
 private:
  std::shared_ptr<CandidateWord> m_en_candidateWord;
  std::shared_ptr<CandidateWord> m_cn_candidateWord;
  std::priority_queue<SimilarityWord> m_result; // 默认大顶堆
  std::shared_ptr<sw::redis::Redis> m_redis;
};


#endif //SEARCHENGINE_KEYWORDSERVER_H
