#pragma once

#include "action/motion/Motion.h"
#include "action/speak/Speak.h"

class Behavior {
private:
    Speak* speak;
    Motion* motion;
    std::atomic<bool> isRunning{};

    uint8_t competitionPhase = -1;
    uint8_t competitionType = -1;
    uint8_t gamePhase = -1;
    uint8_t state = -1;
    uint8_t setPlay = -1;

    void gameControllerBehavior();
    void controlCompetitionPhase();
    void controlCompetitionType();
    void controlGamePhase();
    void controlState();
    void controlSetPlay();
public:
    Behavior();
    void close();
    void process();
};
