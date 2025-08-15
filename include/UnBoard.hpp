#pragma once

#include <atomic>
#include <communication/gameController/RoboCupGameControlData.h>

using namespace std;

#define UNBEATABLES_NUMBER      31
#define ROBOT_STATUS_FALLEN     1
#define ROBOT_STATUS_UPRIGHT    0

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

struct UnBeatablesReturnBoard {
    char header[4] = {'R', 'G', 'r', 't'};
    uint8_t version = GAMECONTROLLER_RETURN_STRUCT_VERSION;
    uint8_t playerNum = 1;
    uint8_t teamNum = UNBEATABLES_NUMBER;
    uint8_t fallen = ROBOT_STATUS_UPRIGHT;
    float pose[3] = {0.0f, 0.0f, 0.0f};
    float ballAge = 0;
    float ball[2] = { 0.0f, 0.0f };
};

extern PerceptionBoard perceptionBoard;
extern RoboCupGameControlData roboCupControlBoard;
extern UnBeatablesReturnBoard unbeatablesReturnBoard;