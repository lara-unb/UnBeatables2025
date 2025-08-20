#pragma once

#include <vector>
#include "Server.hpp"
#include <netinet/in.h>

enum Mode2 {
    BROADCAST = 0,
    MULTICAST,
    UNICAST
};

class UDPServer : public Server {
private:
    sockaddr_in addr {};
    int sockfd = -1;

    std::string host;
    std::string port;

    Mode2 mode = MULTICAST;

public:
    UDPServer(int port, Mode2 mode, const std::string& host = "0.0.0.0");
    ~UDPServer() override;

    std::vector<uint8_t> receiveData() override;

    void setUnicast();
    void setMulticast();
    void setBroadcast();
};