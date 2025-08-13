#pragma once

#include "action/motion/Motion.h"
#include "action/speak/Speak.h"

class Behavior {
private:
    Speak* speak;
    Motion* motion;
public:
    Behavior();
    void close();
    void process() const;
};
