#include "communication/socket/client/TCPClient.hpp"
#include "Logs/EasyLogging.h"

TCPClient::TCPClient(const std::string& host, const int port, const SocketMode mode) {
    LOG(INFO) << "\x1B[93m[TCPSOCKET] Connecting to " << host << ":" << std::to_string(port) << "\x1B[0m";
}

TCPClient::~TCPClient() {

}

void TCPClient::activateBroadcast() {

}

void TCPClient::activateMulticast() {

}

void TCPClient::activateUnicast() {

}

void TCPClient::sendData(const std::vector<uint8_t>& data) {

}