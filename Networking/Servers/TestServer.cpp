#include "TestServer.hpp"

WebServer::TestServer::TestServer()
    : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
  launch();
}

void WebServer::TestServer::accepter() {
  struct sockaddr_in address = get_socket()->get_address();
  int addrlen = sizeof(address);
  new_socket = accept(get_socket()->get_sock(), (struct sockaddr *)&address,
                      (socklen_t *)&addrlen);
  read(new_socket, buffer, 30000);
}

void WebServer::TestServer::handler() { std::cout << buffer << std::endl; }

void WebServer::TestServer::responder() {
  char *hello = "Hello from server!";
  write(new_socket, hello, strlen(hello));
}

void WebServer::TestServer::launch() {
  while (true) {
    std::cout << "===== WAITING =====" << std::endl;
    accepter();
    handler();
    responder();
    std::cout << "===== DONE =====" << std::endl;
  }
}