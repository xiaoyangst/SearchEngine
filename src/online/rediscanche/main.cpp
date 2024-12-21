#include "TcpServer.h"
#include <filesystem>
int main() {
  std::string data = "data";
  std::string config = "conf";
  std::string log = "log";
  if (!std::filesystem::exists(data)) {
    std::filesystem::create_directory(data);
  }
  if (!std::filesystem::exists(config)) {
    std::filesystem::create_directory(config);
  }
  if (!std::filesystem::exists(log)) {
    std::filesystem::create_directory(log);
  }

  TcpServer tcp_server("127.0.0.1", 8080, 4);
  tcp_server.start();
  return 0;
}
