#pragma once

#include <cstdint>
#include <vector>
#include <string>

class Server {
public:
    virtual ~Server() {}
    virtual std::vector<uint8_t> receiveData() = 0;
};

