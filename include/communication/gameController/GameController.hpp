#pragma once

#include <cstdint>
#include <vector>
#include "RoboCupGameControlData.h"

class GameController {
private:
	RoboCupGameControlData roboCupData{};
public:
    GameController();
	RoboCupGameControlData adapterControlData(std::vector<uint8_t> data);
	std::vector<uint8_t> adapterReturnData(const RoboCupGameControlReturnData& data);
};