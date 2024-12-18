/**
  ******************************************************************************
  * @file           : TcpServer.h
  * @author         : xy
  * @brief          : 服务端
  * @attention      : None
  * @date           : 2024/12/13
  ******************************************************************************
  */

#ifndef SEARCHENGINE_SRC_ONLINE_SERVER_TCPSERVER_H_
#define SEARCHENGINE_SRC_ONLINE_SERVER_TCPSERVER_H_
#include <string>
#include <hv/TcpServer.h>
#include <memory>
#include "utils/base/Singleton.h"
#include "KeyWordServer.h"
#include "WebPageServer.h"
constexpr size_t SERVER_HEAD_LENGTH = 5;
constexpr size_t SERVER_HEAD_LENGTH_FIELD_OFFSET = 1;
constexpr size_t SERVER_HEAD_LENGTH_FIELD_BYTES = 4;

class TcpServer : public Singleton<TcpServer> {
  friend class Singleton<TcpServer>;
 public:
  TcpServer(const std::string& ip,int port,int thread_num);
  ~TcpServer();

  void start();
 private:
    void onConnection(const hv::SocketChannelPtr & conn);
    void onMessage(const hv::SocketChannelPtr & conn, hv::Buffer* buf);
 private:
  hv::TcpServer m_server;
  std::shared_ptr<KeyWordServer> m_keyword_server;
  std::shared_ptr<WebPageServer> m_web_page_server;
  unpack_setting_t* server_unpack_setting;
};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_TCPSERVER_H_
