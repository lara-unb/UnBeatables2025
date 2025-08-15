#pragma once

#include "action/motion/Motion.h"
#include "action/speak/Speak.h"

class Behavior {
private:
    Speak* speak;
    Motion* motion;
    std::atomic<bool> isRunning{};

    void gameControllerBehavior();
    void competitionPhase();
    void competitionType();
    void gamePhase();
    void gameState();
    void gamePlay();
public:
    Behavior();
    void close();
    void process();
};
