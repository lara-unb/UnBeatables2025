#include "communication/socket/server/UDPServer.hpp"

#include <arpa/inet.h>

#include "Logs/EasyLogging.h"

UDPServer::UDPServer(int port, Mode2 mode, const std::string& host)
    :host(host), port(std::to_string(port)), mode(mode)
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        throw std::runtime_error("Failed to create UDP server");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    switch (mode) {
        case UNICAST:
            setUnicast();
            break;
        case BROADCAST:
            setBroadcast();
            break;
        case MULTICAST:
            setMulticast();
            break;
        default:
            throw std::runtime_error("Invalid UDP server mode");
    }

}

UDPServer::~UDPServer() {
    LOG(INFO) << "\x1B[93m[UDPServer] Closing UDP server\x1B[0m";
    close(sockfd);
}

void UDPServer::setUnicast() {
    LOG(INFO) << "\x1B[93m[UDPServer] Using UNICAST on host (" << host << ":" << port << ")\x1B[0m";

    int opt = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
    }

    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error("UDP server bind error");
    }
}

void UDPServer::setBroadcast() {
    LOG(INFO) << "\x1B[93m[UDPServer] Using BROADCAST on port: "<< port << "\x1B[0m";

    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &enable, sizeof(enable)) < 0) {
        throw std::runtime_error("Failed to enable broadcast");
    }
    addr.sin_addr.s_addr = INADDR_ANY;
}

void UDPServer::setMulticast() {
    LOG(INFO) << "\x1B[93m[UDPServer] Using MULTICAST on group ("
              << host << ") port (" << port << ")\x1B[0m";

    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error("UDP server bind error");
    }

    struct ip_mreq mreq{};
    if (inet_pton(AF_INET, host.c_str(), &mreq.imr_multiaddr.s_addr) <= 0) {
        throw std::runtime_error("Invalid multicast address: " + host);
    }
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);

    if (setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0) {
        throw std::runtime_error("Failed to join multicast group");
    }
}

std::vector<uint8_t> UDPServer::receiveData() {
    char buffer[1024];

    struct sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    ssize_t recvLen = recvfrom(
        sockfd,
        buffer,
        sizeof(buffer),
        0,
        reinterpret_cast<struct sockaddr *>(&clientAddr),
        &clientLen
    );

    if (recvLen < 0) {
        LOG(INFO) << "Error receiving UDP data";
        return {};
    }

    if (mode == UNICAST) {
        char senderIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, senderIp, sizeof(senderIp));
        if (host != senderIp) {
            LOG(INFO) << "\x1B[93m[UDPServer] Data received from different IP addresses (" << senderIp <<") \x1B[0m";
            return {};
        }
    }

    LOG(INFO) << "\x1B[93m[UDPServer] Data received from (" << host << ":" << port <<") \x1B[0m";
    return std::vector<uint8_t>(buffer, buffer + recvLen);
}