#pragma once

#include "ConnectionSettings.hpp"
#include <cstdint>
#include <vector>
#include <string>

class Client {
public:
    virtual ~Client() = default;
    virtual void activateUnicast() = 0;
    virtual void activateMulticast() = 0;
    virtual void activateBroadcast() = 0;
    virtual void sendData(const std::vector<uint8_t>& data) = 0;
};