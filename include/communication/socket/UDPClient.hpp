#pragma once

#include <ConnectionSettings.hpp>
#include <cstdint>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class UDPClient{
private:
    sockaddr_in addr {};
    int sockfd = -1;
    std::string host;
    std::string port;
    SocketMode mode;
public:
    UDPClient(const std::string& host, const int port, const SocketMode mode);
    ~UDPClient();
    void activateUnicast();
    void activateMulticast();
    void activateBroadcast();
    void sendData(const std::vector<uint8_t>& data);
};