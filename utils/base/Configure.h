/**
  ******************************************************************************
  * @file           : Configure.h
  * @author         : xy
  * @brief          : None
  * @attention      : 非线程安全
  * @date           : 2024/12/19
  ******************************************************************************
  */
#ifndef SEARCHENGINE_UTILS_BASE_CONFIGURE_H_
#define SEARCHENGINE_UTILS_BASE_CONFIGURE_H_
#include <unordered_map>
#include <fstream>
#include <string>
#include <optional>
#include <mutex>
#include "json.hpp"
#include "noncopyable.h"
#include "Singleton.h"
#define CONFIG_JSON_PATH "conf/config.json"

class Configure : public Singleton<Configure> {
 public:
  std::optional<std::string> get(const std::string &key);
 public:
  Configure();
  ~Configure() = default;
 private:
  std::unordered_map<std::string, std::string> m_configureMap;
};

#endif //SEARCHENGINE_UTILS_BASE_CONFIGURE_H_

/***************** usage ****************
  auto re = Configure::getInstance()->get("stop_word");
  if (re == std::nullopt) {
    std::cout << "null" << std::endl;
  } else {
    std::cout << *re << std::endl;
  }
 */