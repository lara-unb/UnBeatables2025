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
    int teamPort;
    std::string broadcast;
};

extern NAOqiAddress naoqiAddress;
extern GameControllerAddress gameControllerAddress;
extern qi::SessionPtr session;