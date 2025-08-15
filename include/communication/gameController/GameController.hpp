#pragma once

#include <cstdint>
#include <vector>
#include "RoboCupGameControlData.h"
#include "UnBoard.hpp"

class GameController {
private:
	RoboCupGameControlData roboCupData{};
	RoboCupGameControlReturnData roboCupReturnData{};
public:
    GameController();
	RoboCupGameControlData adapterControlData(std::vector<uint8_t> data);
	std::vector<uint8_t> adapterReturnData(const UnBeatablesReturnBoard& data);
};