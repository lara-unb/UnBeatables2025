#include "communication/socket/server/UDPServer.hpp"
#include "Logs/EasyLogging.h"

UDPServer::UDPServer(const std::string& ip, int port) {
    LOG(INFO) << "\x1B[93m[UDPServer] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        throw std::runtime_error("Failed to create UDP server");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error("UDP server bind error");
    }
    serverName =  ip + ":" + std::to_string(port);
}

UDPServer::~UDPServer() {
    LOG(INFO) << "\x1B[93m[UDPServer] Closing UDP server\x1B[0m";
    close(sockfd);
}

std::vector<uint8_t> UDPServer::receiveData() {
    char buffer[1024];
    socklen_t clientLen = sizeof(addr);
    ssize_t recvLen = recvfrom(sockfd, buffer, sizeof(buffer), 0, reinterpret_cast<struct sockaddr *>(&addr), &clientLen);
    if (recvLen < 0) {
        LOG(INFO) << "Error receiving UDP data";
        return {};
    }
    LOG(INFO) << "\x1B[93m[UDPServer] Data received from (" << serverName << ") \x1B[0m";
    return std::vector<uint8_t>(buffer, buffer + recvLen);
}
