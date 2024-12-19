#include <iostream>
#include "Configure.h"

Configure *Configure::m_instance = nullptr;
std::unordered_map<std::string, std::string> Configure::m_configureMap;

Configure::Configure() {
  std::ifstream ifs(CONFIG_JSON_PATH);
  if (!ifs.is_open()) {
    std::cout << "open file failed!" << std::endl;
    return;
  }
  nlohmann::json j;
  ifs >> j;
  for (auto &element : j.items()) {
    m_configureMap[element.key()] = element.value().get<std::string>();
  }
}

Configure *Configure::getInstance() {
  static std::once_flag flag_;
  std::call_once(flag_, [&]() {
    m_instance = new Configure();
    atexit(&destroy);
  });
  return m_instance;
}

std::optional<std::string> Configure::get(const std::string &key) {
  auto it = m_configureMap.find(key);
  if (it != m_configureMap.end()) {
    return it->second;
  }
  return std::nullopt;
}

void Configure::PrintTest() {
  for (auto &element : m_configureMap) {
    std::cout << element.first << " : " << element.second << std::endl;
  }
}
void Configure::destroy() {
  if (m_instance) {
    delete m_instance;
    m_instance = nullptr;
  }
}
