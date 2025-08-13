#pragma once

#include <string>

class Server {
public:
    virtual ~Server() {}
    virtual std::string receiveData() = 0;
};

