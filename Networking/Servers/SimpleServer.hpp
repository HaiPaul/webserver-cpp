#ifndef SimpleServer_hpp
#define SimpleServer_hpp

#include "../lib-networking.hpp"

namespace WebServer {
class SimpleServer {
 private:
  ListeningSocket *socket;
  virtual void accepter() = 0;
  virtual void handler() = 0;
  virtual void responder() = 0;

 public:
  SimpleServer(int domain, int service, int protocol, int port,
               unsigned long interface, int bklg);
    virtual void launch() = 0;
    ListeningSocket *get_socket();
};
}  // namespace WebServer

#endif