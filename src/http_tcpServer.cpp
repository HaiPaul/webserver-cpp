#include "../include/http_tcpServer.h"

std::vector<std::string> split(const std::string &s, char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
};

namespace {
const int BUFFER_SIZE = 30720;

void log(const std::string &message) { std::cout << message << std::endl; }

void exitWithError(const std::string &errorMessage) {
  log("ERROR: " + errorMessage);
  exit(1);
}
}  // namespace

namespace http {

TcpServer::TcpServer(std::string ip_address, int port)
    : m_ip_address(ip_address),
      m_port(port),
      m_socket(),
      m_new_socket(),
      m_incomingMessage(),
      m_socketAddress(),
      m_socketAddress_len(sizeof(m_socketAddress)),
      m_serverMessage("") {
  m_socketAddress.sin_family = AF_INET;
  m_socketAddress.sin_port = htons(m_port);
  m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());

  if (startServer() != 0) {
    std::ostringstream ss;
    ss << "Failed to start server with PORT: "
       << ntohs(m_socketAddress.sin_port);
    log(ss.str());
  }
}

TcpServer::~TcpServer() { closeServer(); }

int TcpServer::startServer() {
  m_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (m_socket < 0) {
    exitWithError("Cannot create socket");
    return 1;
  }

  if (bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
    exitWithError("Cannot connect socket to address");
    return 1;
  }

  return 0;
}

void TcpServer::closeServer() {
  close(m_socket);
  close(m_new_socket);
  exit(0);
}

void TcpServer::startListen() {
  if (listen(m_socket, 20) < 0) {
    exitWithError("Socket listen failed");
  }

  std::ostringstream ss;
  ss << "\n*** Listening on ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr)
     << " PORT: " << ntohs(m_socketAddress.sin_port) << " ***\n\n";
  log(ss.str());

  int bytesReceived;

  while (true) {
    log("====== Waiting for a new connection ======\n\n\n");
    acceptConnection(m_new_socket);

    char buffer[BUFFER_SIZE];
    bytesReceived = read(m_new_socket, &buffer, BUFFER_SIZE);
    if (bytesReceived < 0) {
      exitWithError("Failed to read bytes from client socket connection");
    }

    std::ostringstream strs;
    strs << "------ Received Request from client ------\n\n";
    log(strs.str());

    log(buffer);
    // TODO: better request handling
    auto split_vect = split(buffer, ' ');
    std::string file = split_vect[1].substr(1);
    REQUEST_TYPE type;
    if (file == "favicon.ico") {
      type = ICON;
    } else if (file.size() > 5 && file.substr(5, 8) == "css") {
      type = STYLE;
    } else {
      type = HTML;
    }

    std::ostringstream ss;
    buildResponse(ss, type, split_vect);
    m_serverMessage = ss.str();
    sendResponse();

    close(m_new_socket);
  }
}

void TcpServer::acceptConnection(int &new_socket) {
  new_socket =
      accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
  if (new_socket < 0) {
    std::ostringstream ss;
    ss << "Server failed to accept incoming connection from ADDRESS: "
       << inet_ntoa(m_socketAddress.sin_addr)
       << "; PORT: " << ntohs(m_socketAddress.sin_port);
    exitWithError(ss.str());
  }
}

void TcpServer::buildResponse(std::ostringstream &ss, REQUEST_TYPE type,
                              std::vector<std::string> split_vect) {
  std::ifstream file;
  std::stringstream stream;
  std::string responseFile;
  switch (type) {
    case ICON:
      file.open("favicon.ico");
      stream << file.rdbuf();
      responseFile = stream.str();
      ss << "HTTP/1.1 200 OK\nContent-Type: image/x-icon\nContent-Length: "
         << responseFile.size() << "\n\n"
         << responseFile;
      break;

    case HTML:
      if (split_vect[1].length() < 2) {
        file.open("html/index.html");
        stream << file.rdbuf();
        responseFile = stream.str();
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
           << responseFile.size() << "\n\n"
           << responseFile;
        break;
      }

      file.open("html" + split_vect[1] + ".html");
      if (file.fail()) {
        std::string resp =
            "<head><title>Error</title></head><body><h1>Page not found!</h1></body>";
        ss << "HTTP/1.1 404 NOT FOUND\nContent-Type: text/html\nContent-Length: "
           << resp.size() << "\n\n"
           << resp;
        break;
      }
      stream << file.rdbuf();
      responseFile = stream.str();
      ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "
         << responseFile.size() << "\n\n"
         << responseFile;
      break;

    case STYLE:
      file.open("css/style.css");
      stream << file.rdbuf();
      responseFile = stream.str();
      ss << "HTTP/1.1 200 OK\nContent-Type: text/css\nContent-Length: "
         << responseFile.size() << "\n\n"
         << responseFile;
      break;
  }
}

void TcpServer::sendResponse() {
  std::size_t bytesSent;

  bytesSent =
      write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());

  if (bytesSent == m_serverMessage.size()) {
    log("------ Server Response sent to client ------\n\n");
  } else {
    log("Error sending response to client");
  }
}

}  // namespace http