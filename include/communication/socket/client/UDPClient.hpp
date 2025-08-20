#pragma once

#include "Client.hpp"

class UDPClient : public Client {
private:
    sockaddr_in addr {};
    int sockfd = -1;

    Mode mode = Mode::NONE;

    std::string host;
    std::string port;

    std::string broadcastAddrOverride = "";
    std::string multicastAddrOverride = "";
public:
    UDPClient(const std::string& host, int port, Mode customizableMode);
    ~UDPClient() override;

    void sendData(const std::vector<uint8_t>& data) override;

    void activeBroadcast() override;
    void activeMulticast() override;
    void activeUnicast() override;

    std::string getBroadcastAddress() const override;
    std::string getMulticastAddress() const override;

    void setBroadcastAddress(const std::string& addr) override;
    void setMulticastAddress(const std::string& addr) override;
};

