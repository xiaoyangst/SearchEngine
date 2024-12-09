#include "SimHashWebPage.h"
SimHashWebPage::SimHashWebPage(const string &dictPath,
                               const string &hmmPath,
                               const string &idfPath,
                               const string &stopWordPath) {
    m_simhasher = std::make_shared<Simhasher>(dictPath, hmmPath, idfPath, stopWordPath);
}
uint64_t SimHashWebPage::getSimHash(const string &sentence,size_t TopN) {
  uint64_t u64 = 0;
  m_simhasher->make(sentence,TopN,u64);
  return Simhasher::binaryStringToUint64(to_string(u64));
}
bool SimHashWebPage::isEqual(uint64_t hash1, uint64_t hash2) {
  return Simhasher::isEqual(hash1,hash2);
}
