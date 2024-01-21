#ifndef http_tcpserver
#define http_tcpserver

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace http {

enum REQUEST_TYPE { ICON, HTML, STYLE };

class TcpServer {
 private:
  std::string m_ip_address;
  int m_port;
  int m_socket;
  int m_new_socket;
  long m_incomingMessage;
  struct sockaddr_in m_socketAddress;
  uint m_socketAddress_len;
  std::string m_serverMessage;

  int startServer();
  void closeServer();
  void acceptConnection(int& new_socket);
  void buildResponse(std::ostringstream& ss, REQUEST_TYPE type,
                     std::string requestline);
  void sendResponse();

 public:
  TcpServer(std::string ip_address, int port);
  ~TcpServer();
  void startListen();
};
}  // namespace http
#endif