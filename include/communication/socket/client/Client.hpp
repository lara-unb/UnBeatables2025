#pragma once

#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <string>
#include <vector>

class Client {
public:
    virtual ~Client() = default;
    virtual void sendUnicast(const std::vector<uint8_t>& data) = 0;
    virtual void sendBroadcast(const std::vector<uint8_t>& data) = 0;
};

