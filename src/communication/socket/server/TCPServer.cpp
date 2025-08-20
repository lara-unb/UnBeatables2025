#include "communication/socket/server/TCPServer.hpp"
#include "Logs/EasyLogging.h"

TCPServer::TCPServer(const std::string& ip, const int port, const SocketMode mode) {
    LOG(INFO) << "\x1B[93m[TCPSOCKET] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";
}

TCPServer::~TCPServer() {

}

void TCPServer::activateBroadcast() {

}

void TCPServer::activateMulticast() {

}

void TCPServer::activateUnicast() {

}

std::vector<uint8_t> TCPServer::receiveData() {
    return {};
}