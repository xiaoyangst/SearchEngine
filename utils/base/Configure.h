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

#define CONFIG_JSON_PATH "conf/config.json"

class Configure : public noncopyable {
 public:
  static Configure *getInstance();
  std::optional<std::string> get(const std::string &key);
 public:
  Configure();
  ~Configure() = default;
  static void destroy();
 private:
  void PrintTest(); // 测试打印
 private:
  static Configure *m_instance;
  static std::unordered_map<std::string, std::string> m_configureMap;
};

#endif //SEARCHENGINE_UTILS_BASE_CONFIGURE_H_
