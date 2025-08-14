#pragma once

#include <cstdint>
#include <atomic>
#include <communication/gameController/RoboCupGameControlData.h>

using namespace std;

struct BallPositionData {
    bool seen = false;
    int x = 0;
    int y = 0;

    BallPositionData() = default;
    BallPositionData(bool ss, int xx, int yy) : seen(ss), x(xx), y(yy) {}
};

struct PerceptionBoard {
    uint16_t cameraHeight = 240;
    uint16_t cameraWidth = 320;
    BallPositionData topCamera;
    BallPositionData botCamera;
};
extern PerceptionBoard perceptionBoard;

struct CommunicationBoard {
    atomic<int8_t> gamePhase;
    atomic<int8_t> gameState;
    atomic<int8_t> setPlay;
    atomic<int8_t> firstHalf;
    atomic<int8_t> kickingTeam;
    atomic<uint8_t> playerNumber;
    atomic<uint8_t> penalty;
    atomic<uint8_t> teamNumber;
    atomic<int16_t> secsRemaining;
    atomic<int16_t> score;
    atomic<int16_t> secsTillUnpenalised;
};
extern CommunicationBoard communicationBoard;

extern RoboCupGameControlData roboCupBoard;