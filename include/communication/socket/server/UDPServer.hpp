#pragma once

#include <vector>
#include "Server.hpp"
#include <netinet/in.h>

class UDPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string serverName;

public:
    UDPServer(const std::string& host, int port);
    ~UDPServer() override;

    std::vector<uint8_t> receiveData() override;
};