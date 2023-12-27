#include "SimpleSocket.hpp"

/**
 * @brief Construct a new Web Server:: Simple Socket:: Simple Socket object
 *
 * @param domain
 * @param service
 * @param protocol
 * @param port
 * @param interface
 */
WebServer::SimpleSocket::SimpleSocket(int domain, int service, int protocol,
                                      int port, unsigned long interface) {
  // Define address structure
  address.sin_family = domain;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(interface);
  // Establish socket
  sock = socket(domain, service, protocol);
  // Test socket
  test_connection(sock);
}

/**
 * @brief function to test if some item has been properly created
 *
 * @param item_to_test
 */
void WebServer::SimpleSocket::test_connection(int item_to_test) {
  // Confirmas that the connection has been properly established
  if (item_to_test < 0) {
    perror("Failed to connect...");
    exit(EXIT_FAILURE);
  }
}

/**
 * @brief get the sockaddr_in struct
 *
 * @return struct sockaddr_in
 */
struct sockaddr_in WebServer::SimpleSocket::get_address() { return address; }

/**
 * @brief get the connection attribute
 *
 * @return int
 */
int WebServer::SimpleSocket::get_connection() { return connection; }

/**
 * @brief sets the connection attribute to a new value
 *
 * @param new_conn
 */
void WebServer::SimpleSocket::set_connection(int new_conn) {
  connection = new_conn;
}

/**
 * @brief get the socket attribute
 *
 * @return int
 */
int WebServer::SimpleSocket::get_sock() { return sock; }

/**
 * @brief sets the socket attribute to a new value
 *
 * @param new_sock
 */
void WebServer::SimpleSocket::set_sock(int new_sock) { sock = new_sock; }