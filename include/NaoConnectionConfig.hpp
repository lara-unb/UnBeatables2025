#pragma once
#include <string>

struct NaoConnectionConfig {
    std::string ip = "127.0.0.2";
    int port = 9559;
};
extern NaoConnectionConfig naoConfig;
