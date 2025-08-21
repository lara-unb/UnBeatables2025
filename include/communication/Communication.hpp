#pragma once

#include <atomic>
#include "socket/server/Server.hpp"
#include "socket/client/Client.hpp"
#include "gameController/GameController.hpp"
#include "teamController/TeamController.hpp"

class Communication {
private:
    GameController* gameController;
    Client* gameControllerClient;
    Server* gameControllerServer;
    TeamController* teamController;
    Client* teamClient;
    Server* teamServer;;
    std::atomic<bool> isRunning{};

    void processGameController();
    void processTeamController();
public:
    Communication(GameController* gamecontroller, Client* gameControllerClient, Server* gameControllerServer, TeamController* teamController, Client* teamClient, Server* teamServer);
    void process();
    void close();
};

