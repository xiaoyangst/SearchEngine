#include "KeyWordProducer.h"
#include <string>
int main(){

  std::string path = "conf/keyword.json";
  KeyWordProducer key(path);
  key.start();

  return 0;
}
