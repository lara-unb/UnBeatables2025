#pragma once

#include "alproxies/almotionproxy.h"
#include <action/animations/CapoeiraLeft.h>


class Kick {
private:
    AL::ALMotionProxy motion;
public:
    Kick();
    ~Kick();
    void capoeiraKickLeft();
    void capoeiraKickRight();
    void playAnimation(const Animation& anim);
};
