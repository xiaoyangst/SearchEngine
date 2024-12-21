#include "WebPageProducer.h"
#include <filesystem>
int main() {

  std::string data = "data";
  std::string config = "conf";
  if (!std::filesystem::exists(data)) {
    std::filesystem::create_directory(data);
  }
  if (!std::filesystem::exists(config)) {
    std::filesystem::create_directory(config);
  }

  WebPageProducer web_page_producer;
  web_page_producer.start();
  return 0;
}