#include "KeyWordServer.h"
#include "utils/base/Log.h"
#include "utils/base/EditDistance.h"
bool KeyWordServer::init() {

  std::string en_dict_path = Configure::getInstance()->get("en_dict").value();
  std::string en_invert_path = Configure::getInstance()->get("en_invert").value();
  std::string cn_dict_path = Configure::getInstance()->get("cn_dict").value();
  std::string cn_invert_path = Configure::getInstance()->get("cn_invert").value();
  std::string redis_ip = Configure::getInstance()->get("redis_ip").value();
  std::string redis_port = Configure::getInstance()->get("redis_port").value();

  m_en_candidateWord = std::make_shared<CandidateWord>(en_dict_path, en_invert_path);
  m_cn_candidateWord = std::make_shared<CandidateWord>(cn_dict_path, cn_invert_path);

  if (!m_en_candidateWord->preheat()) {
    ERROR_LOG("en candidateWord preheat failed");
    return false;
  }
  if (!m_cn_candidateWord->preheat()) {
    ERROR_LOG("cn candidateWord preheat failed");
    return false;
  }

  sw::redis::ConnectionOptions connOpts;
  connOpts.host = redis_ip;
  connOpts.port = std::stoi(redis_port);
  connOpts.socket_timeout = std::chrono::seconds(1);
  m_redis = std::make_shared<sw::redis::Redis>(connOpts);

  if (m_redis->ping() != "PONG") {
    ERROR_LOG("redis connect failed");
    return false;
  }

  return true;
}

std::string KeyWordServer::getKeyWord(std::string &word) {
  // 先走缓存
  if (m_redis->exists(word)) {
    std::cout << "keyword 走缓存" << std::endl;
    std::unordered_set<std::string> re;
    m_redis->smembers(word,std::inserter(re,re.begin()));
    json data(re);
    return data.dump();
  }

  auto sig_word_vec = SingleWord::splitString(word);
  CandVec result;
  m_cn_candidateWord->CandidateWords(sig_word_vec, result);
  m_en_candidateWord->CandidateWords(sig_word_vec, result);
  // 排序
  sortCandidateWord(result, word);
  // 理论上取前面十个
  json j_array;
  for (int i = 0; i < 10; ++i) {
    if (m_result.empty()) { break; }
    auto data = m_result.top().word;
    j_array.push_back(data);
    m_redis->sadd(word, data); // 记得插入到 redis，以便后续走缓存
    m_result.pop();
  }
  std::cout << "keyword 走磁盘" << std::endl;
  return j_array.dump();
}
/*
 * 比较规则：
 *  a.优先比较最小编辑距离
 *  b.在编辑距离相同的条件下，再比较候选词的词频；词频越大优先选择
 *  c.在词频相同的条件下，按字母表顺序比较候选词
 */
void KeyWordServer::sortCandidateWord(CandVec &words, const std::string &key_word) {
  for (const auto &word : words) {
    int sim = EditDistance::editDistance(key_word, word.first);
    struct SimilarityWord sim_word = {
        .word = word.first,
        .similarity = sim,
        .frequency = word.second
    };
    m_result.push(sim_word);
  }
}


