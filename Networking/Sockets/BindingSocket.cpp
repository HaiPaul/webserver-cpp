#include "BindingSocket.hpp"

/**
 * @brief Construct a new Web Server:: Binding Socket:: Binding Socket object
 *
 * @param domain
 * @param service
 * @param protocol
 * @param port
 * @param interface
 */
WebServer::BindingSocket::BindingSocket(int domain, int service, int protocol,
                                        int port, unsigned long interface)
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
int WebServer::BindingSocket::connect_to_network(int sock,
                                                 struct sockaddr_in address) {
  return bind(sock, (struct sockaddr *)&address, sizeof(address));
}