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
};
