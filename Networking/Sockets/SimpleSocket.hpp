#ifndef SimpleSocket_hpp
#define SimpleSocket_hpp

#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

#include <iostream>

namespace WebServer {
class SimpleSocket {
 private:
  struct sockaddr_in address;
  int sock;
  int connection;

 public:
  // Constructor
  SimpleSocket(int domain, int service, int protocol, int port,
               unsigned long interface);
  // virtual function to connect to a network
  virtual int connect_to_network(int sock, struct sockaddr_in address) = 0;
  void test_connection(int);
  struct sockaddr_in get_address();
  int get_sock();
  void set_sock(int new_sock);
  int get_connection();
  void set_connection(int new_conn);
};
}  // namespace WebServer

#endif