#pragma once

#include "TeamMessage.hpp"
#include <cstdint>
#include <vector>

#define MAX_PAYLOAD     128

class TeamController {
private:
    TeamMessage outgoingData{};
    TeamMessage incomingData{};
public:
    TeamController();
    TeamMessage convertToTeamMessage(std::vector<uint8_t> data);
    std::vector<uint8_t> convertToVector(const TeamMessage& data);
};