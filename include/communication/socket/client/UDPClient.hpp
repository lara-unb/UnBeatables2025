#pragma once

#include "Client.hpp"

class UDPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string clientName;

public:
    UDPClient(const std::string& host, int port);
    ~UDPClient() override;

    void sendData(const std::vector<uint8_t>& data) override;
};

