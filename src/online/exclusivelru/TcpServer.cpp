#include "TcpServer.h"
#include "utils/base/Log.h"
#include "utils/base/HvProtocol.h"
#include "utils/base/Configure.h"
#include "utils/public.h"
#include "json.hpp"

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

  m_server.loop()->setInterval(60000, [this](auto timer) {
    std::cout << "timer callback" << std::endl;
    synKeyword();
    synWebPage();
  });

  std::string keyword_num = Configure::getInstance()->get("keyword_server_num").value();
  std::string webpage_num = Configure::getInstance()->get("webpage_server_num").value();
  m_k_num = std::stoi(keyword_num);
  m_w_num = std::stoi(webpage_num);
  std::string lru_capacity = Configure::getInstance()->get("lru_capacity").value();
  int lru_capacity_int = std::stoi(lru_capacity);
  m_Wlru = std::make_unique<LRU>(lru_capacity_int);
  m_Klru = std::make_unique<LRU>(lru_capacity_int);
  for (int i = 0; i < m_k_num; ++i) {
    auto keyword_server = std::make_shared<KeyWordServer>();
    m_keyword_server.push_back(keyword_server);
  }
  for (int i = 0; i < m_w_num; ++i) {
    auto webpage_server = std::make_shared<WebPageServer>();
    m_web_page_server.push_back(webpage_server);
  }

  m_server.onConnection = [this](const hv::SocketChannelPtr &conn) {
    onConnection(conn);
  };
  m_server.onMessage = [this](const hv::SocketChannelPtr &conn, hv::Buffer *buf) {
    onMessage(conn, buf);
  };

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

// one loop one thread
void TcpServer::onMessage(const hv::SocketChannelPtr &conn, hv::Buffer *buf) {
  std::cout << "id = " << conn->id() << std::endl;
  std::string data = std::string((char *) buf->data(), buf->size());
  auto tmp = HvProtocol::unpackMessage(data);
  std::cout << tmp << std::endl;
  FUNCTYPE type;
  std::string message;
  json reply;
  try {
    json Message = json::parse(tmp);
    type = Message["type"].get<FUNCTYPE>();
    message = Message["message"].get<std::string>();
  } catch (std::exception &e) {
    std::cout << "json parse error" << std::endl;
    reply["message"] = "json parse error";
    conn->write(HvProtocol::packMessageAsString(reply.dump()));
    return;
  }
  switch (type) {
    case FUNCTYPE::KEYWORD: {
      auto re = getKeywordServer()->getKeyWord(message);
      reply["message"] = re;
      break;
    }
    case FUNCTYPE::WEBPAGE: {
      auto re = getWebPageServer()->getWebPage(message);
      reply["message"] = re;
      break;
    }
    default:break;
  }
  conn->write(HvProtocol::packMessageAsString(reply.dump()));
}

std::shared_ptr<KeyWordServer> TcpServer::getKeywordServer() {
  std::lock_guard<std::mutex> lock(m_KMtx);
  static unsigned int s_index = 0;
  unsigned int index = s_index++ % m_k_num;
  return m_keyword_server[index];
}

std::shared_ptr<WebPageServer> TcpServer::getWebPageServer() {
  std::lock_guard<std::mutex> lock(m_WMtx);
  static unsigned int s_index = 0;
  unsigned int index = s_index++ % m_w_num;
  return m_web_page_server[index];
}

void TcpServer::synWebPage() {
  std::lock_guard<std::mutex> lock(m_WMtx);
  m_Wlru->clearAll();
  // 收集 pending
  for (const auto &webpage : m_web_page_server) {
    std::cout << "开始收集" << std::endl;
    for (const auto &item : webpage->getPending()) {
      for (const auto &page_set : item) {
        m_Wlru->put(page_set.first, page_set.second);
      }
    }
    webpage->m_lru->clearPending();
  }

  // 同步 LRU
  for (const auto &webpage : m_web_page_server) {
    std::cout << "开始同步" << std::endl;
    for (const auto &item : m_Wlru->getCache()) {
      for (const auto &word_set : item) {
        webpage->m_lru->put(word_set.first, word_set.second);
      }
    }
  }
}

void TcpServer::synKeyword() {
  std::lock_guard<std::mutex> lock(m_KMtx);
  std::cout << "tid = " << std::this_thread::get_id() << std::endl;

  m_Klru->clearAll();

  // 收集 pending
  for (const auto &keyword : m_keyword_server) {
    std::cout << "开始收集" << std::endl;
    for (const auto &item : keyword->getPending()) {
      for (const auto &word_set : item) {
        m_Klru->put(word_set.first, word_set.second);
      }
    }
    keyword->m_lru->clearPending();
  }

  // 同步 LRU
  for (const auto &keyword : m_keyword_server) {
    std::cout << "开始同步" << std::endl;
    for (const auto &item : m_Klru->getCache()) {
      for (const auto &word_set : item) {
        keyword->m_lru->put(word_set.first, word_set.second);
      }
    }
  }
}