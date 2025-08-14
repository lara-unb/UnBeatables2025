#pragma once

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

extern RoboCupGameControlData roboCupBoard;