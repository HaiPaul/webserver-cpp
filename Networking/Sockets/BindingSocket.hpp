#ifndef BindingSocket_hpp
#define BindingSocket_hpp

#include "SimpleSocket.hpp"

namespace WebServer {
class BindingSocket : public SimpleSocket {
 public:
  BindingSocket(int domain, int service, int protocol, int port,
                unsigned long interface);
  int connect_to_network(int sock, struct sockaddr_in address);
};

}  // namespace WebServer

#endif