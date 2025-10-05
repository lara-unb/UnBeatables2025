#pragma once

#include "control/ControlBoard.h"

class ControlStrategy {
public:
    virtual ~ControlStrategy() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual void update() = 0;
};