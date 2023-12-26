#include "ListeningSocket.hpp"

/**
 * @brief Construct a new Web Server:: Listening Socket:: Listening Socket
 * object
 *
 * @param domain
 * @param service
 * @param protocol
 * @param port
 * @param interface
 * @param bklg
 */
WebServer::ListeningSocket::ListeningSocket(int domain, int service,
                                            int protocol, int port,
                                            unsigned long interface, int bklg)
    : BindingSocket(domain, service, protocol, port, interface) {
  backlog = bklg;
  start_listening();
  test_connection(listening);
}

/**
 * @brief start listening to the connection
 *
 */
void WebServer::ListeningSocket::start_listening() {
  listening = listen(get_connection(), backlog);
}