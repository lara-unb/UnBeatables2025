#include "communication/teamController/TeamController.hpp"
#include "Logs/EasyLogging.h"

TeamController::TeamController() {
    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Starting Team Controller\x1B[0m";
    if (sizeof(TeamMessage) > MAX_PAYLOAD) {
        throw std::length_error("Message too large for Team Controller");
    }
}

TeamMessage TeamController::convertToTeamMessage(std::vector<uint8_t> data) {
    if (data.size() < sizeof(TeamMessage)) {
        LOG(INFO) << "\x1B[35m[TEAMCONTROLLER] Smaller package than expected!\x1B[0m";
        return incomingData;
    }

    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] TeamMessage received successfully\x1B[0m";
    std::memcpy(&incomingData, data.data(), sizeof(TeamMessage));
    return incomingData;
}

std::vector<uint8_t> TeamController::convertToVector(const TeamMessage& data) {
    std::memcpy(&outgoingData, &data, sizeof(TeamMessage));
    constexpr size_t structSize = sizeof(TeamMessage);
    std::vector<uint8_t> bytes(structSize);
    std::memcpy(bytes.data(), &outgoingData, structSize);
    return bytes;
}