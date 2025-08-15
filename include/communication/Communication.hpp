#pragma once

#include <atomic>
#include "socket/server/Server.hpp"
#include "socket/client/Client.hpp"
#include "gameController/GameController.hpp"

class Communication {
private:
    Client *gameControllerClient;
    Server *gameControllerServer;
    GameController *gameController;
    std::atomic<bool> isRunning{};
public:
    Communication(GameController* gamecontroller, Client* gameControllerClient, Server* gameControllerServer);
    void process() const;
    void close();
};

