#include "communication/socket/client/UDPClient.hpp"
#include "Logs/EasyLogging.h"

UDPClient::UDPClient(const std::string& ip, int port) {
    LOG(INFO) << "\x1B[93m[UDPClient] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        throw std::runtime_error("Failed to create UDP client");

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip.c_str(), &addr.sin_addr) <= 0)
        throw std::runtime_error("Invalid ip address");
    clientName =  ip + ":" + std::to_string(port);
}

UDPClient::~UDPClient() {
    LOG(INFO) << "\x1B[93m[UDPClient] Closing UDP client\x1B[0m";
    close(sockfd);
}

void UDPClient::sendData(const std::vector<uint8_t>& data) {
    ssize_t sent = sendto(sockfd, data.data(), data.size(), 0, reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
    if (sent != static_cast<ssize_t>(data.size()))
        throw std::runtime_error("Fail to send message");
    LOG(INFO) << "\x1B[93m[UDPClient] Sending UnBeatablesReturnBoard to (" << clientName <<")\x1B[0m";
}