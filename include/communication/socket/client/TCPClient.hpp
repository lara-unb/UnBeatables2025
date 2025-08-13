#pragma once

#include <string>
#include <netinet/in.h>
#include "Client.hpp"

class TCPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;

public:
    TCPClient(const std::string& host, int port);
    ~TCPClient() override;

    void sendData(const std::string& data) override;
};

