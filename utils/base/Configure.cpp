#include <iostream>
#include "Configure.h"

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

std::optional<std::string> Configure::get(const std::string &key) {
  auto it = m_configureMap.find(key);
  if (it != m_configureMap.end()) {
    return it->second;
  }
  return std::nullopt;
}