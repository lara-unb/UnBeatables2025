#pragma once

#include "gameController/GameController.hpp"
#include "teamController/TeamController.hpp"
#include <atomic>

#define FREQUENCY      1

class Communication {
private:
    GameController* gameController;
    TeamController* teamController;
    std::atomic<bool> gameControllerIsConnected{};
    std::atomic<bool> teamControllerIsConnected{};
    std::atomic<bool> isRunning{};
public:
    Communication(GameController* gamecontroller, TeamController* teamController);
    void process();
    void close();
};

