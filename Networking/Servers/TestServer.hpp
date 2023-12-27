#ifndef TestServer_hpp
#define TestServer_hpp
#include <stdio.h>
#include <unistd.h>
#include <cstring>

#include "SimpleServer.hpp"

namespace WebServer {
class TestServer : public SimpleServer {
 private:
  void accepter();
  void handler();
  void responder();
  char buffer[30000] = {0};
  int new_socket;

 public:
  TestServer();
  void launch();
};
}  // namespace WebServer

#endif