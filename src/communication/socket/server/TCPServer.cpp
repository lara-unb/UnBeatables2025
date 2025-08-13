#include "communication/socket/server/TCPServer.hpp"

#include "Logs/EasyLogging.h"

TCPServer::TCPServer(const std::string& ip, int port) {
    LOG(INFO) << "\x1B[93m[TCPSOCKET] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";
}

TCPServer::~TCPServer() {

}

std::string TCPServer::receiveData() {
    return "oi";
}