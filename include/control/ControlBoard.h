#pragma once

#include <cstdint>
#include <string>

struct ControlState {
    std::string device;

    bool select = false;
    bool start = false;
    bool up = false;
    bool right = false;
    bool down = false;
    bool left = false;

    bool l3 = false;
    bool l2 = false;
    bool l1 = false;
    bool r3 = false;
    bool r2 = false;
    bool r1 = false;

    bool triangle = false;
    bool circle = false;
    bool cross = false;
    bool square = false;

    int16_t leftStickX = 0;
    int16_t leftStickY = 0;
    int16_t rightStickX = 0;
    int16_t rightStickY = 0;
};

extern ControlState controlState;
