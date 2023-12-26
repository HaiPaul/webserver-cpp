#ifndef ConnectingSocket_hpp
#define ConnectingSocket_hpp

#include "SimpleSocket.hpp"

namespace WebServer {
class ConnectingSocket : public SimpleSocket {
 public:
  ConnectingSocket(int domain, int service, int protocol, int port,
                unsigned long interface);
  int connect_to_network(int sock, struct sockaddr_in address);
};

}  // namespace WebServer

#endif