#ifndef ListeningSocket_hpp
#define ListeningSocket_hpp

#include "BindingSocket.hpp"

namespace WebServer {
class ListeningSocket : public BindingSocket {
 private:
  int backlog;
  int listening;

 public:
  ListeningSocket(int domain, int service, int protocol, int port,
                  unsigned long interface, int bklg);
  void start_listening();
  int get_listening();
  int get_backlog();
};
}  // namespace WebServer

#endif