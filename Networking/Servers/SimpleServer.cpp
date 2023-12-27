#include "SimpleServer.hpp"

WebServer::SimpleServer::SimpleServer(int domain, int service, int protocol,
                                      int port, unsigned long interface,
                                      int bklg) {
  socket =
      new ListeningSocket(domain, service, protocol, port, interface, bklg);
}

WebServer::ListeningSocket* WebServer::SimpleServer::get_socket() {
  return socket;
}