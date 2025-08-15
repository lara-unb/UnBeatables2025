#pragma once

#include "Client.hpp"

class UDPClient : public Client {
private:
    sockaddr_in unicastAddr {};
    sockaddr_in broadcastAddr {};
    int sockfd = -1;
    std::string clientName;

public:
    UDPClient(const std::string& host, int port, const std::string& broadcast);
    ~UDPClient() override;

    void sendUnicast(const std::vector<uint8_t>& data) override;
    void sendBroadcast(const std::vector<uint8_t>& data) override;
};

