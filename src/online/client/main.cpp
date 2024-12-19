#include <hv/TcpClient.h>
#include "json.hpp"
#include "utils/public.h"
#include "utils/base/HvProtocol.h"
#include <iostream>
#include <cstring>
#include <istream>
#include <thread>
#include <atomic>

using json = nlohmann::json;

// 获取用户输入的函数
void getInput(std::string &type, std::string &message) {
  std::cout << "请输入命令类型：";
  std::getline(std::cin, type);

  std::cout << "请输入查询数据：";
  std::getline(std::cin, message);
}

// 处理输入并发送消息的函数
void MainWindows(const hv::SocketChannelPtr &channel, const std::string &type, const std::string &message) {
  json data;
  if (type == "keyword") {
    data["type"] = FUNCTYPE::KEYWORD;
  } else if (type == "webpage") {
    data["type"] = FUNCTYPE::WEBPAGE;
  }
  data["message"] = message;
  channel->write(HvProtocol::packMessageAsString(data.dump()));
  std::cout << std::endl;
}

int main() {
  std::string m_ip = "127.0.0.1";
  int m_port = 8080;

  hv::TcpClient tcp_client;
  int m_connfd = tcp_client.createsocket(m_port, m_ip.c_str());
  if (m_connfd < 0) {
    printf("connfd failed\n");
    return -1;
  }
  auto *server_unpack_setting = new unpack_setting_t();
  memset(server_unpack_setting, 0, sizeof(unpack_setting_t));
  server_unpack_setting->mode = UNPACK_BY_LENGTH_FIELD;
  server_unpack_setting->package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
  server_unpack_setting->body_offset = SERVER_HEAD_LENGTH;
  server_unpack_setting->length_field_offset = SERVER_HEAD_LENGTH_FIELD_OFFSET;
  server_unpack_setting->length_field_bytes = SERVER_HEAD_LENGTH_FIELD_BYTES;
  server_unpack_setting->length_field_coding = ENCODE_BY_BIG_ENDIAN;
  tcp_client.setUnpack(server_unpack_setting);

  std::cout << "client connect server ip = " << m_ip << " port = " << m_port << std::endl;

  // 连接建立回调
  tcp_client.onConnection = [&](const hv::SocketChannelPtr &channel) {
    std::string peeraddr = channel->peeraddr();
    if (channel->isConnected()) {
      printf("onConnection connected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());

      // 在独立线程中等待输入
      std::string type, message;
      std::thread input_thread(getInput, std::ref(type), std::ref(message));
      input_thread.join();
      MainWindows(channel, type, message);
    } else {
      printf("onConnection disconnected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());
      printf("连接断开\n");
      return;
    }
  };

  // 业务回调
  tcp_client.onMessage = [&](const hv::SocketChannelPtr &channel, hv::Buffer *buf) {
    std::string peeraddr = channel->peeraddr();
    printf("onMessage connected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());
    std::string data = std::string((char *) buf->data(), buf->size());
    std::cout << "接收到数据:" << HvProtocol::packMessageAsString(data) << std::endl;

    // 在收到数据后再获取输入
    std::string type, message;
    std::thread input_thread(getInput, std::ref(type), std::ref(message));
    input_thread.join();
    MainWindows(channel, type, message);
  };

  tcp_client.start();

  // 防止主线程退出
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 防止主线程退出
  }

  return 0;
}
