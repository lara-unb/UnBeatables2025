#pragma once

#include <string>
#include <qi/session.hpp>

struct NAOqiAddress {
    std::string ip;
    int port;
};

struct GameControllerAddress {
    std::string ip;
    int writingPort;
    int readingPort;
};

extern NAOqiAddress naoqiAddress;
extern GameControllerAddress gameControllerAddress;
extern qi::SessionPtr session;