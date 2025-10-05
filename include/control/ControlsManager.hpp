#pragma once

#include <atomic>
#include "ControlBoard.h"
#include "controls/ControlStrategy.hpp"

class ControlsManager {
private:
    std::atomic<bool>  isRunning{};
    ControlStrategy* controlStrategy;
public:
    ControlsManager(ControlStrategy* strategy);
    void close();
    void process();
};
