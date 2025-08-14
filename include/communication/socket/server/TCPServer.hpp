#pragma once

#include <string>
#include <netinet/in.h>
#include "Server.hpp"

class TCPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;

public:
    TCPServer(const std::string& host, int port);
    ~TCPServer() override;

    std::vector<uint8_t> receiveData() override;
};

