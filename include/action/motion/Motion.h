#pragma once

#include "alproxies/almotionproxy.h"

class Motion{
private:
    AL::ALMotionProxy motionService;

public:
    Motion();
    ~Motion();

    void wakeUp();
    void rest();

    void move(float x, float y);
    void rotate(bool side);
    void moveHead(float x, float y);

    void stopMove();
    void stopRotate();
    void stopMoveHead();
};
