#pragma once

#include "Client.hpp"

class UDPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;

public:
    UDPClient(const std::string& host, int port);
    ~UDPClient() override;

    void sendData(const std::string& data) override;
};

