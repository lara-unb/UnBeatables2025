#pragma once

#include <atomic>
#include "socket/server/Server.hpp"
#include "socket/client/Client.hpp"
#include "gameController/GameController.hpp"

class Communication {
private:
    Client *client;
    Server *server;
    GameController *gameController;
    std::atomic<bool> isRunning{};
public:
    Communication();
    void process() const;
    void close();
};

