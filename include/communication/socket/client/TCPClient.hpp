#pragma once

#include "Client.hpp"
#include <netinet/in.h>

class TCPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;
public:
    TCPClient(const std::string& host, const int port, const SocketMode mode);
    ~TCPClient() override;
    void activateBroadcast() override;
    void activateMulticast() override;
    void activateUnicast() override;
    void sendData(const std::vector<uint8_t>& data) override;
};

