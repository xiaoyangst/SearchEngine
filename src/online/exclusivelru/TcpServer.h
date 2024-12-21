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
#include "LRU.h"

class TcpServer : public Singleton<TcpServer> {
  friend class Singleton<TcpServer>;
  using KSerVec = std::vector<std::shared_ptr<KeyWordServer>>;
  using WSerVec = std::vector<std::shared_ptr<WebPageServer>>;
 public:
  TcpServer(const std::string &ip, int port, int thread_num);
  ~TcpServer();

  void start();
 private:
  void onConnection(const hv::SocketChannelPtr &conn);
  void onMessage(const hv::SocketChannelPtr &conn, hv::Buffer *buf);
  std::shared_ptr<KeyWordServer> getKeywordServer();
  std::shared_ptr<WebPageServer> getWebPageServer();
  void synKeyword();
  void synWebPage();
 private:
  hv::TcpServer m_server;
  unsigned int m_k_num;
  unsigned int m_w_num;
  KSerVec m_keyword_server;
  WSerVec m_web_page_server;
  unpack_setting_t *server_unpack_setting;
  std::mutex m_KMtx;
  std::mutex m_WMtx;
  std::unique_ptr<LRU> m_Klru;
  std::unique_ptr<LRU> m_Wlru;
};

#endif //SEARCHENGINE_SRC_ONLINE_SERVER_TCPSERVER_H_
