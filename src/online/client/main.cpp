#include <hv/TcpClient.h>
#include "json.hpp"
#include "utils/public.h"
#include "utils/base/HvProtocol.h"
#include <iostream>
#include <cstring>
constexpr size_t SERVER_HEAD_LENGTH = 4;
constexpr size_t SERVER_HEAD_LENGTH_FIELD_OFFSET = 0;
constexpr size_t SERVER_HEAD_LENGTH_FIELD_BYTES = 4;
using json = nlohmann::json;

int main() {

  std::string m_ip = "127.0.0.1";
  int m_port = 8080;

  hv::TcpClient tcp_client;
  int m_connfd = tcp_client.createsocket(m_port, m_ip.c_str());
  if (m_connfd < 0) {
    printf("connfd failed\n");
    return -1;
  }
  /*
  auto *server_unpack_setting = new unpack_setting_t();
  memset(server_unpack_setting, 0, sizeof(unpack_setting_t));
  server_unpack_setting->mode = UNPACK_BY_LENGTH_FIELD;
  server_unpack_setting->package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
  server_unpack_setting->body_offset = 4;
  server_unpack_setting->length_field_offset = 0;
  server_unpack_setting->length_field_bytes = 4;
  server_unpack_setting->length_field_coding = ENCODE_BY_BIG_ENDIAN;
  tcp_client.setUnpack(server_unpack_setting);
*/
  std::cout << "client connect server ip = " << m_ip << " port = " << m_port << std::endl;
  // 连接建立回调
  tcp_client.onConnection = [&](const hv::SocketChannelPtr &channel) {
    std::string peeraddr = channel->peeraddr();
    if (channel->isConnected()) {
      printf("onConnection connected to %s! connfd=%d\n", peeraddr.c_str(), channel->fd());
      json first_json;
      first_json["type"] = FUNCTYPE::WEBPAGE;
      first_json["message"] = "云服务器";
      std::string message = first_json.dump();

      // TODO 粘包拆包问题

      channel->write(message);
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
    std::cout << "接收到数据:" << data << std::endl;
  };
  std::cout << "client start" << std::endl;
  tcp_client.start();

  while (getchar() != '\n');

  std::cout << "client stop" << std::endl;
  return 0;
}