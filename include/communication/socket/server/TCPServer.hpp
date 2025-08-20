#pragma once

#include "Server.hpp"
#include <netinet/in.h>

class TCPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;
public:
    TCPServer(const std::string& host, const int port, SocketMode mode);
    ~TCPServer() override;
    void activateUnicast() override;
    void activateMulticast() override;
    void activateBroadcast() override;
    std::vector<uint8_t> receiveData() override;
};