#include "TcpServer.h"
#include "utils/base/Log.h"
#include "utils/base/HvProtocol.h"
#include "utils/public.h"
#include "utils/base/json.hpp"

using json = nlohmann::json;

TcpServer::TcpServer(const std::string &ip, const int port, const int thread_num) {
  int listen_fd = m_server.createsocket(port, ip.c_str());
  if (listen_fd < 0) {
    ERROR_LOG("create socket error");
    return;
  }
  server_unpack_setting = new unpack_setting_t();
  memset(server_unpack_setting, 0, sizeof(unpack_setting_t));
  server_unpack_setting->mode = UNPACK_BY_LENGTH_FIELD;
  server_unpack_setting->package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
  server_unpack_setting->body_offset = SERVER_HEAD_LENGTH;
  server_unpack_setting->length_field_offset = SERVER_HEAD_LENGTH_FIELD_OFFSET;
  server_unpack_setting->length_field_bytes = SERVER_HEAD_LENGTH_FIELD_BYTES;
  server_unpack_setting->length_field_coding = ENCODE_BY_BIG_ENDIAN;
  m_server.setUnpack(server_unpack_setting);
  m_server.setThreadNum(thread_num);
  m_server.onConnection = [this](const hv::SocketChannelPtr &conn) {
    onConnection(conn);
  };
  m_server.onMessage = [this](const hv::SocketChannelPtr &conn, hv::Buffer *buf) {
    onMessage(conn, buf);
  };

  m_keyword_server = std::make_shared<KeyWordServer>();
  if (!m_keyword_server->init()) {
    ERROR_LOG("keyword server init failed");
    return;
  }

  m_web_page_server = std::make_shared<WebPageServer>();
  if (!m_web_page_server->init()) {
    ERROR_LOG("webpage server init failed");
    return;
  }
}

void TcpServer::start() {
  m_server.start();
  INFO_LOG("server start");
  while (getchar() != '\n');
}

TcpServer::~TcpServer() {
  delete server_unpack_setting;
  m_server.stop();
}

void TcpServer::onConnection(const hv::SocketChannelPtr &conn) {
  std::string peerAddr = conn->peeraddr();
  if (conn->isConnected()) {
    INFO_LOG("new connection: %s , connfd = %d", peerAddr.c_str(), conn->fd());
  } else {
    INFO_LOG("connection closed: %s , connfd = %d", peerAddr.c_str(), conn->fd());
  }
}

void TcpServer::onMessage(const hv::SocketChannelPtr &conn, hv::Buffer *buf) {
  std::string data = std::string((char *) buf->data(), buf->size());
  auto tmp = HvProtocol::unpackMessage(data);
  std::cout << tmp << std::endl;
  json Message = json::parse(tmp);
  auto type = Message["type"].get<FUNCTYPE>();
  auto message = Message["message"].get<std::string>();
  json reply;
  switch (type) {
    case FUNCTYPE::KEYWORD: {
      auto re = m_keyword_server->getKeyWord(message);
      reply["message"] = re;
      break;
    }
    case FUNCTYPE::WEBPAGE: {
      auto re = m_web_page_server->getWebPage(message);
      reply["message"] = re;
      break;
    }
    default:break;
  }
  conn->write(HvProtocol::packMessageAsString(reply.dump()));
}
