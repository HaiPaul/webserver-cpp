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
  // Establish socket
  connection = connect_to_network(sock, address);
  test_connection(connection);
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
 * @brief get the connection
 *
 * @return int
 */
int WebServer::SimpleSocket::get_connection() { return connection; }

/**
 * @brief get the socket
 *
 * @return int
 */
int WebServer::SimpleSocket::get_sock() { return sock; }