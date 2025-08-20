#pragma once

#include "ConnectionSettings.hpp"
#include <cstdint>
#include <vector>
#include <string>

class Server {
public:
    virtual ~Server() {}
    virtual void activateUnicast() = 0;
    virtual void activateMulticast() = 0;
    virtual void activateBroadcast() = 0;
    virtual std::vector<uint8_t> receiveData() = 0;
};