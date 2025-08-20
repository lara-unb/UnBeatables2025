#pragma once

#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <string>
#include <vector>

enum class Mode { NONE, UNICAST, BROADCAST, MULTICAST};

class Client {
public:
    virtual ~Client() = default;
    virtual void sendData(const std::vector<uint8_t>& data) = 0;

    virtual void activeBroadcast() = 0;
    virtual void activeMulticast() = 0;
    virtual void activeUnicast() = 0;

    virtual std::string getBroadcastAddress() const = 0;
    virtual std::string getMulticastAddress() const = 0;

    virtual void setBroadcastAddress(const std::string& addr) = 0;
    virtual void setMulticastAddress(const std::string& addr) = 0;
};


