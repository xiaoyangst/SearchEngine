#ifndef SEARCHENGINE_UTILS_BASE_HVPROTOCOL_H_
#define SEARCHENGINE_UTILS_BASE_HVPROTOCOL_H_
#include <string>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#define LEN_XY 1024
class HvProtocol {
 public:
  // 封包函数，将字符串封装成自定义协议格式（头部+数据）
  static std::string packMessageAsString(const char* data) {
    int len = strlen(data);
    char buf[1024] = {0};
    memcpy(buf, &len, 4);
    memcpy(buf + 4, data, len);
    printf("%s\n",buf);
    return std::string(buf,4+len);
  }

// 拆包函数，从接收到的数据中提取消息
  static std::string unpackMessage(const std::string &receivedData) {
    int len = 0;
    memcpy(&len, receivedData.data(), 4);
    return receivedData.substr(4, len);
  }
};
#endif //SEARCHENGINE_UTILS_BASE_HVPROTOCOL_H_
