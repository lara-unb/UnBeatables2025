#pragma once

#include "TeamMessage.hpp"
#include "communication/socket/UDPClient.hpp"
#include "communication/socket/UDPServer.hpp"
#include <cstdint>
#include <vector>
#include <future>

#define MAX_PAYLOAD     128

class TeamController {
private:
    TeamMessage outgoingData{};
    TeamMessage incomingData{};
    UDPClient* client;
    UDPServer* server;
public:
    TeamController(UDPClient* client, UDPServer* server);
    ~TeamController();
    TeamMessage convertToTeamMessage(const std::vector<uint8_t> data);
    std::vector<uint8_t> convertToVector(const TeamMessage& data);
    bool verifyConnection();
    void process();
};