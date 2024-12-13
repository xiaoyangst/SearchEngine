#include "utils/base/Log.h"

int main(){

  Log::getInstance()->setLogLevel(DEBUG);
  Log::getInstance()->debug("debug");
  Log::getInstance()->info("info");
  Log::getInstance()->warn("warn");
  Log::getInstance()->error("error");
  Log::getInstance()->fatal("fatal");

  return 0;
}
