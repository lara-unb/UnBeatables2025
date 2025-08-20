#pragma once

#include "Server.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>

class UDPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string host;
    std::string port;
    SocketMode mode;
public:
    UDPServer(const std::string& host, const int port, const SocketMode mode);
    ~UDPServer() override;
    void activateUnicast() override;
    void activateMulticast() override;
    void activateBroadcast() override;
    std::vector<uint8_t> receiveData() override;
};