#pragma once

#include <cstdint>
#include <vector>
#include "RoboCupGameControlData.h"

class GameController {
private:
public:
    GameController();
	RoboCupGameControlData adapterData(std::vector<uint8_t> data);
};