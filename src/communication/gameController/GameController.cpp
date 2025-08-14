#include "communication/gameController/GameController.hpp"
#include "Logs/EasyLogging.h"

GameController::GameController() {
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Starting Game Controller\x1B[0m";
}

RoboCupGameControlData GameController::adapterData(std::vector<uint8_t> data) {
    // LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Recived: " << data << " \x1B[0m";
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Recived: \x1B[0m";
    return {};
}