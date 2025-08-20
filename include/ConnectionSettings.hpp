#pragma once

#include <string>
#include <qi/session.hpp>

enum SocketMode {
    BROADCAST = 0,
    MULTICAST,
    UNICAST
};

struct NAOqiAddress {
    std::string ip;
    int port;
};

struct GameControllerAddress {
    std::string host;
    int writingPort;
    int readingPort;
};

struct TeamCommunicationAddress {
    std::string multicast;
    std::string broadcast;
    int teamPort;
};

extern NAOqiAddress naoqiAddress;
extern GameControllerAddress gameControllerAddress;
extern TeamCommunicationAddress teamCommunicationAddress;
extern qi::SessionPtr session;