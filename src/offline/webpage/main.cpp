#include "WebPageProducer.h"
int main() {
  std::string path = "conf/webpage.json";
    WebPageProducer web_page_producer(path);
    web_page_producer.start();
    return 0;
}