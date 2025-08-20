#pragma once

#include <string>
#include <netinet/in.h>
#include "Client.hpp"

class TCPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;

public:
    TCPClient(const std::string& host, int port, Mode customizableMode);
    ~TCPClient() override;

    void sendData(const std::vector<uint8_t>& data) override;

    void activeBroadcast() override;
    void activeMulticast() override;
    void activeUnicast() override;

    std::string getBroadcastAddress() const override;
    std::string getMulticastAddress() const override;

    void setBroadcastAddress(const std::string& addr) override;
    void setMulticastAddress(const std::string& addr) override;

};

