#pragma once

#include "action/speak/Speak.h"

class Behavior {
private:
    Speak* speak;
public:
    Behavior();
    ~Behavior();

    void close();
    void process();
};
