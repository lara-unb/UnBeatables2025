#include "communication/socket/UDPClient.hpp"
#include "Logs/EasyLogging.h"

UDPClient::UDPClient(const std::string& host, const int port, const SocketMode mode)
    : host(host), port(std::to_string(port)), mode(mode)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        throw std::runtime_error("Failed to create UDP socket");
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    switch(mode) {
        case UNICAST:
            UDPClient::activateUnicast();
            break;
        case MULTICAST:
            UDPClient::activateMulticast();
            break;
        case BROADCAST:
            UDPClient::activateBroadcast();
            break;
        default:
            throw std::runtime_error("Failed to create UDP packet");
    }
}

UDPClient::~UDPClient() {
    LOG(INFO) << "\x1B[93m[UDPClient] Closing UDP client\x1B[0m";
    close(sockfd);
}

void UDPClient::activateUnicast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using UNICAST (" << host << ":" << port <<")\x1B[0m";
    mode = UNICAST;
    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid address: " + host);
    }
}

void UDPClient::activateMulticast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using MULTICAST (" << host << ":" << port << ")\x1B[0m";
    mode = MULTICAST;

    if (inet_pton(AF_INET, host.c_str(), &addr.sin_addr) <= 0) {
        throw std::runtime_error("Invalid multicast address: " + host);
    }

    // Interface de saída (0.0.0.0 = qualquer disponível)
    in_addr localInterface{};
    localInterface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF,
                   (char*)&localInterface, sizeof(localInterface)) < 0) {
        throw std::runtime_error("Failed to set multicast interface");
                   }

    // TTL = 1 (somente LAN)
    unsigned char ttl = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl)) < 0) {
        throw std::runtime_error("Failed to set multicast TTL");
    }

    // Ativa loopback (para testes)
    unsigned char loop = 1;
    if (setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_LOOP, &loop, sizeof(loop)) < 0) {
        throw std::runtime_error("Failed to enable multicast loopback");
    }
}

void UDPClient::activateBroadcast() {
    LOG(INFO) << "\x1B[93m[UDPClient] Using BROADCAST (" << host << ":" << port <<")\x1B[0m";
    mode = BROADCAST;
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable)) < 0) {
        throw std::runtime_error("Failed to enable broadcast");
    }
    in_addr_t bcast = inet_addr(host.c_str());
    if (bcast == INADDR_NONE) {
        throw std::runtime_error("Invalid broadcast address");
    }
    addr.sin_addr.s_addr = bcast;
}

void UDPClient::sendData(const std::vector<uint8_t>& data) {
    ssize_t sent = sendto(sockfd, data.data(), data.size(),
                          MSG_DONTWAIT,
                          reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
    if (sent < 0) {
        throw std::runtime_error("Failed to send UDP packet");
    }

    LOG(INFO) << "\x1B[93m[UDPClient] Sending message to host (" << host << ":" << port <<")\x1B[0m";
}