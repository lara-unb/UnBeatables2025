#include "communication/gameController/GameController.hpp"
#include "Logs/EasyLogging.h"
#include <iomanip>

GameController::GameController() {
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Starting Game Controller\x1B[0m";
}

std::vector<uint8_t> GameController::adapterReturnData(const RoboCupGameControlReturnData& data) {
    constexpr size_t structSize = sizeof(RoboCupGameControlReturnData);
    std::vector<uint8_t> bytes(structSize);
    std::memcpy(bytes.data(), &data, structSize);
    return bytes;
}

RoboCupGameControlData GameController::adapterControlData(std::vector<uint8_t> data) {
    if (data.size() < sizeof(RoboCupGameControlData)) {
        LOG(INFO) << "\x1B[35m[GAMECONTROLLER] Smaller package than expected!\x1B[0m";
        return roboCupData;
    }

    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] RoboCupGameControlData received successfully\x1B[0m";
    std::memcpy(&roboCupData, data.data(), sizeof(RoboCupGameControlData));
    return roboCupData;
}