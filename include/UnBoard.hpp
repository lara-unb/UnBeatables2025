#pragma once

#include <cstdint>
#include <mutex>

struct PerceptionBoard {
    std::mutex mutex;

    uint16_t height = 240;
    uint16_t width = 320;

    bool seeBallTop = false;
    bool seeBallBot = false;

    int16_t ballXBot = -1;
    int16_t ballYBot = -1;

    int16_t ballXTop = -1;
    int16_t ballYTop = -1;
};
extern PerceptionBoard perceptionBoard;

struct CommunicationBoard {
    std::mutex mutex;

    uint8_t playerNumber = 3;
    uint8_t teamNumber = 0;

    int8_t gamePhase = -1;
    int8_t gameState = -1;
    int8_t setPlay = -1;
    int8_t firstHalf = -1;
    int8_t kickingTeam = -1;
    int16_t secsRemaining = -1;

    int16_t score = -1;

    uint8_t penalty = 0;
    int16_t secsTillUnpenalised = 0;
};
extern CommunicationBoard communicationBoard;