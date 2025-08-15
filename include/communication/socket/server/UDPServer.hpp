#pragma once

#include <vector>
#include "Server.hpp"
#include <netinet/in.h>

class UDPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    bool hasSecurityIP = false;
    std::string allowedIP;

public:
    UDPServer(const std::string& host, int port, const std::string& securityIP = "");
    ~UDPServer() override;

    std::vector<uint8_t> receiveData() override;
};