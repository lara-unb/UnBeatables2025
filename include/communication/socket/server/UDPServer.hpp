#pragma once

#include <string>
#include "Server.hpp"
#include <netinet/in.h>

class UDPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;

public:
    UDPServer(const std::string& host, int port);
    ~UDPServer() override;

    std::string receiveData() override;
};