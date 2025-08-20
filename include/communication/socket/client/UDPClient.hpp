#pragma once

#include "Client.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class UDPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string host;
    std::string port;
    SocketMode mode;
public:
    UDPClient(const std::string& host, const int port, const SocketMode mode);
    ~UDPClient() override;
    void activateUnicast() override;
    void activateMulticast() override;
    void activateBroadcast() override;
    void sendData(const std::vector<uint8_t>& data) override;
};