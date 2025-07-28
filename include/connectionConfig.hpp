#pragma once

#include <string>
#include <qi/session.hpp>

struct ConnectionConfig {
    std::string ip = "127.0.0.2";
    int port = 9559;
};

extern ConnectionConfig connectionConfig;
extern qi::SessionPtr session;