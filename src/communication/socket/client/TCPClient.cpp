#include "communication/socket/client/TCPClient.hpp"
#include "Logs/EasyLogging.h"

TCPClient::TCPClient(const std::string& ip, int port) {
    LOG(INFO) << "\x1B[93m[TCPSOCKET] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";
}

TCPClient::~TCPClient() {

}

void TCPClient::sendUnicast(const std::vector<uint8_t>& data) {

}

void TCPClient::sendBroadcast(const std::vector<uint8_t>& data) {

}