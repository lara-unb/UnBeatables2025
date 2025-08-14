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
    virtual void sendData(const std::vector<uint8_t>& data) = 0;
};

