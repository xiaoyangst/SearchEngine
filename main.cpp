/*
#include <iostream>
#include <queue>
#include <string>

struct SimilarityWord {
  std::string word;
  int similarity; // 相似度
  unsigned int frequency; // 词频

  bool operator<(const SimilarityWord &rhs) const {
    if (this->similarity < rhs.similarity) {
      return false;
    } else if (this->similarity > rhs.similarity) {
      return true;
    }
    if (this->frequency > rhs.frequency) {
      return false;
    } else if (this->frequency < rhs.frequency) {
      return true;
    }
    return this->word > rhs.word;
  }

};

// 测试函数
void testPriorityQueue() {
  // 创建优先队列，存储 SimilarityWord 类型元素
  std::priority_queue<SimilarityWord> m_result;

  // 向队列中添加一些元素
  m_result.push({"apple", 3, 100});
  m_result.push({"banana", 2, 150});
  m_result.push({"cherry", 3, 120});
  m_result.push({"apricot", 2, 180});
  m_result.push({"blueberry", 1, 200});
  m_result.push({"kiwi", 4, 50});
  m_result.push({"kiwa", 4, 50});

  // 打印弹出的元素，应该按照优先级顺序
  while (!m_result.empty()) {
    const SimilarityWord &word = m_result.top();
    std::cout << "Word: " << word.word
              << ", Similarity: " << word.similarity
              << ", Frequency: " << word.frequency
              << std::endl;
    m_result.pop();
  }
}

#include "utils/base/HvProtocol.h"
#include <fstream>
#include <sstream>
int main() {

  //const char *name = "hello";
/*
  short len = strlen(name);
  char buf[1024] = {0};

  memcpy(buf, &len, 4);
  memcpy(buf + 4, name, len);
  std::cout << "buf = " << std::string(buf,4+len)<< std::endl;
*/
/*
  std::string name = "hello";
  auto re = HvProtocol::packMessageAsString(name.c_str());
  std::cout << "re = " << re << std::endl;
  auto tmp = HvProtocol::unpackMessage(re);
  std::cout << "tmp = " << tmp << std::endl;
  return 0;
  */
/*
  std::string path = "data/new_webpage_offset.dat";
  std::ifstream ifs(path);
  if (!ifs.is_open()) {
    std::cout << "open file failed!" << std::endl;
    return 0;
  }

  ifs.seekg(0, std::ios::end);
  auto size = ifs.tellg();
  ifs.seekg(0, std::ios::beg);
  std::string data(size, 0);
  ifs.read(data.data(), size);

  std::istringstream stream(data);
  std::string line;
  while (std::getline(stream, line)) {
    std::cout << line << std::endl;
  }
  }
*/
#include <iostream>
#include <queue>
#include <vector>

struct SimilarityPage {
  int page_id;  // 页面 id
  double cosine_val;  // 余弦值，值越小越相似，越靠前

  // 重载 < 运算符，使得余弦值小的对象排在前面
  bool operator<(const SimilarityPage& other) const {
    return cosine_val < other.cosine_val;  // 余弦值小的排前面
  }
};


int main() {
  std::priority_queue<SimilarityPage> pq;

  pq.push({1, 0.8});
  pq.push({2, 0.5});
  pq.push({3, 0.9});

  while (!pq.empty()) {
    const SimilarityPage& page = pq.top();
    std::cout << "Page ID: " << page.page_id << ", Cosine Value: " << page.cosine_val << std::endl;
    pq.pop();
  }

  return 0;
}


