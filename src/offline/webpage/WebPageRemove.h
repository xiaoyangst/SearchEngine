/**
  ******************************************************************************
  * @file           : WebPageRemove.h
  * @author         : xy
  * @brief          : 网页去重，即移除重复的网页
  * @attention      : None
  * @date           : 2024/12/7
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEREMOVE_H_
#define SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEREMOVE_H_
#include <string>
#include <unordered_set>
#include <memory>
#include <sstream>
#include "json.hpp"
#include "SimHashWebPage.h"
#include "utils/base/noncopyable.h"
using json = nlohmann::json;
class WebPageRemove : public noncopyable{
 public:
    WebPageRemove(std::string dict_path, std::string index_path,
                  std::string new_dict_path, std::string new_index_path,std::string json_path);
    ~WebPageRemove() = default;

    void buildNewDict();
    void buildNewIndex();
 private:
  std::string m_dict_path;
  std::string m_index_path;
  std::string m_new_dict_path;
  std::string m_new_index_path;
  std::string m_json_path;
  std::unordered_set<uint64_t> m_hash_set;  // 计算之后如果没有，就写入 Dict
  std::shared_ptr<SimHashWebPage> m_simhasher;
};

#endif //SEARCHENGINE_SRC_OFFLINE_WEBPAGE_WEBPAGEREMOVE_H_
