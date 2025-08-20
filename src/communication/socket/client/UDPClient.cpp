#include "communication/socket/client/UDPClient.hpp"
#include "Logs/EasyLogging.h"
#include <stdexcept>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

UDPClient::UDPClient(const std::string& host, int port, Mode customizableMode)
    : host(host), port(std::to_string(port)), mode(customizableMode)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create UDP socket");
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    switch(mode) {
        case Mode::UNICAST:
            UDPClient::activeUnicast();
            break;
        case Mode::MULTICAST:
            UDPClient::activeMulticast();
            break;
        case Mode::BROADCAST:
            UDPClient::activeBroadcast();
            break;
        default:
            throw std::runtime_error("Failed to create UDP packet");
    }
}

UDPClient::~UDPClient() {
    if (sockfd >= 0) {
        close(sockfd);
        sockfd = -1;
    }
}

void UDPClient::sendData(const std::vector<uint8_t>& data) {
    ssize_t sent = sendto(sockfd, data.data(), data.size(), 0, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (sent < 0) {
        throw std::runtime_error("Failed to send UDP packet");
    }
}

void UDPClient::activeUnicast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using UNICAST (" << host << ":" << port <<")\x1B[0m";
    mode = Mode::UNICAST;
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address: " + host);
    }
}

void UDPClient::activeBroadcast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using BROADCAST (" << host << ":" << port <<")\x1B[0m";
    mode = Mode::BROADCAST;

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable)) < 0) {
        throw std::runtime_error("Failed to enable broadcast");
    }

    in_addr_t bcast = inet_addr(getBroadcastAddress().c_str());
    if (bcast == INADDR_NONE) {
        throw std::runtime_error("Invalid broadcast address");
    }

    addr.sin_addr.s_addr = bcast;
}

void UDPClient::activeMulticast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using MULTICAST (" << host << ":" << port <<")\x1B[0m";
    mode = Mode::MULTICAST;
    if (inet_pton(AF_INET, getMulticastAddress().c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid multicast address");
    }
}

std::string UDPClient::getBroadcastAddress() const {
    if (!broadcastAddrOverride.empty()) {
        return broadcastAddrOverride;
    }
    // calcular o broadcast
    return "192.168.24.255";
}

std::string UDPClient::getMulticastAddress() const {
    if (!multicastAddrOverride.empty()) {
        return multicastAddrOverride;
    }
    // calcular o multicast
    return "239.0.0.1";
}

void UDPClient::setBroadcastAddress(const std::string &addr) {
    this->broadcastAddrOverride = addr;
}

void UDPClient::setMulticastAddress(const std::string &addr) {
    this->multicastAddrOverride = addr;
}