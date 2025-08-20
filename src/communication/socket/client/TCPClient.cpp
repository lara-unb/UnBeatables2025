#include "communication/socket/client/TCPClient.hpp"
#include "Logs/EasyLogging.h"

TCPClient::TCPClient(const std::string& host, int port, Mode customizableMode) {
    LOG(INFO) << "\x1B[93m[TCPSOCKET] Connecting to " << host << ":" << std::to_string(port) << "\x1B[0m";
}

TCPClient::~TCPClient() {

}

void TCPClient::sendData(const std::vector<uint8_t>& data) {

}

void TCPClient::activeBroadcast() {

}

void TCPClient::activeMulticast() {

}

void TCPClient::activeUnicast() {

}

std::string TCPClient::getBroadcastAddress() const {
    return "";
}

std::string TCPClient::getMulticastAddress() const {
    return "";
}

void TCPClient::setBroadcastAddress(const std::string& addr) {

}

void TCPClient::setMulticastAddress(const std::string& addr) {

}