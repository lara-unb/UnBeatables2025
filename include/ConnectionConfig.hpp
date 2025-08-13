#pragma once

#include <string>
#include <qi/session.hpp>

struct ConnectionConfig {
    const std::string ip = "127.0.0.1";
    const int port = 9559;
};

struct GameControllerAddress {
    const std::string ip = "192.168.42.128";
    const int port = 3838;
};

extern ConnectionConfig connectionConfig;
extern GameControllerAddress gameControllerAddress;

extern qi::SessionPtr session;