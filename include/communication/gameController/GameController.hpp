#pragma once

#include "RoboCupGameControlData.h"
#include "UnBoard.hpp"
#include "communication/socket/UDPClient.hpp"
#include "communication/socket/UDPServer.hpp"
#include <cstdint>
#include <vector>
#include <future>

class GameController {
private:
	RoboCupGameControlData incomingData{};
	RoboCupGameControlReturnData outgoingData{};
	UDPClient* client;
	UDPServer* server;
public:
    GameController(UDPClient* client, UDPServer* server);
	~GameController();
	RoboCupGameControlData convertToRoboCupGameData(const std::vector<uint8_t> data);
	std::vector<uint8_t> convertToVector(const RoboCupGameControlReturnData& data);
	bool verifyConnection();
	void process();
};