#include <control/ControlsManager.hpp>
#include "Logs/EasyLogging.h"

ControlsManager::ControlsManager(ControlStrategy* strategy)
    : controlStrategy(strategy){
    isRunning = true;
}

void ControlsManager::close() {
    LOG(INFO) << "\x1B[33m[CONTROLS MANAGER] Closing control\x1B[0m";
    isRunning = false;
    controlStrategy->close();
}

void ControlsManager::process() {
    while (isRunning) {
        controlStrategy->update();
    }
}
