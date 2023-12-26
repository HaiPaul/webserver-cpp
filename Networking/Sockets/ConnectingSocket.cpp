#include "ConnectingSocket.hpp"

/**
 * @brief Construct a new Web Server:: Binding Socket:: Binding Socket object
 *
 * @param domain
 * @param service
 * @param protocol
 * @param port
 * @param interface
 */
WebServer::ConnectingSocket::ConnectingSocket(int domain, int service,
                                              int protocol, int port,
                                              unsigned long interface)
    : SimpleSocket(domain, service, protocol, port, interface) {
  set_connection(connect_to_network(get_sock(), get_address()));
  test_connection(get_connection());
}

/**
 * @brief connects a specific socket to a given address
 *
 * @param sock
 * @param address
 * @return int
 */
int WebServer::ConnectingSocket::connect_to_network(
    int sock, struct sockaddr_in address) {
  return connect(sock, (struct sockaddr *)&address, sizeof(address));
}