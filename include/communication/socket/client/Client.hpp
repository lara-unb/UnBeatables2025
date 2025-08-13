#pragma once

#include <string>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>

class Client {
public:
    virtual ~Client() = default;
    virtual void sendData(const std::string& data) = 0;
};

