#pragma once

#include "ConnectionSettings.hpp"
#include <cstdint>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

class UDPServer {
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string host;
    std::string port;
    SocketMode mode;
public:
    UDPServer(const std::string& host, const int port, const SocketMode mode);
    ~UDPServer();
    void activateUnicast();
    void activateMulticast();
    void activateBroadcast();
    std::vector<uint8_t> receiveData();
};