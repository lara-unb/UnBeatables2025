#include "communication/socket/client/UDPClient.hpp"
#include "Logs/EasyLogging.h"

UDPClient::UDPClient(const std::string& ip, int port, const std::string& broadcast) {
    LOG(INFO) << "\x1B[93m[UDPClient] Connecting to " << ip << ":" << std::to_string(port) << "\x1B[0m";

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
        throw std::runtime_error("Failed to create UDP client");

    // --- Unicast addr ---
    memset(&unicastAddr, 0, sizeof(unicastAddr));
    unicastAddr.sin_family = AF_INET;
    unicastAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip.c_str(), &unicastAddr.sin_addr) <= 0)
        throw std::runtime_error("Invalid IP address");
    clientName = ip + ":" + std::to_string(port);

    // --- Broadcast addr ---
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));
    broadcastAddr.sin_family = AF_INET;
    broadcastAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, broadcast.c_str(), &broadcastAddr.sin_addr) <= 0)
        throw std::runtime_error("Invalid broadcast address");

    clientName =  ip + ":" + std::to_string(port);
}

UDPClient::~UDPClient() {
    LOG(INFO) << "\x1B[93m[UDPClient] Closing UDP client\x1B[0m";
    close(sockfd);
}

void UDPClient::sendUnicast(const std::vector<uint8_t>& data) {
    ssize_t sent = sendto(sockfd, data.data(), data.size(), 0,
                          reinterpret_cast<struct sockaddr*>(&unicastAddr), sizeof(unicastAddr));
    if (sent != static_cast<ssize_t>(data.size()))
        throw std::runtime_error("Fail to send unicast message");

    LOG(INFO) << "\x1B[93m[UDPClient] Sent unicast to " << clientName << "\x1B[0m";
}

void UDPClient::sendBroadcast(const std::vector<uint8_t>& data) {
    int broadcastEnable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable)) < 0)
        throw std::runtime_error("Failed to enable broadcast");

    ssize_t sent = sendto(sockfd, data.data(), data.size(), 0,
                          reinterpret_cast<struct sockaddr*>(&broadcastAddr), sizeof(broadcastAddr));
    if (sent != static_cast<ssize_t>(data.size()))
        throw std::runtime_error("Fail to send broadcast message");

    LOG(INFO) << "\x1B[93m[UDPClient] Broadcast sent on port " << ntohs(broadcastAddr.sin_port) << "\x1B[0m";
}
