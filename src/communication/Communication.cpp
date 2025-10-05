#include "communication/Communication.hpp"
#include "Logs/EasyLogging.h"

Communication::Communication(GameController* gamecontroller, TeamController* teamController)
    : gameController(gamecontroller), teamController(teamController)
{
    isRunning = true;
    gameControllerIsConnected = gameController->verifyConnection();
    teamControllerIsConnected = teamController->verifyConnection();
    teamControllerIsConnected = false;
    if (!gameControllerIsConnected) delete gameController;
    if (!teamControllerIsConnected) delete teamController;
}

void Communication::close() {
    LOG(INFO) << "\x1B[93m[COMMUNICATION] Closing controllers\x1B[0m";
    isRunning = false;
    sleep(1);
    if (gameControllerIsConnected) delete gameController;
    if (teamControllerIsConnected) delete teamController;
}

void Communication::process() {
    if (!gameControllerIsConnected && !teamControllerIsConnected) return;
    while (isRunning) {
        sleep(FREQUENCY);
        if (gameControllerIsConnected) gameController->process();
        if (teamControllerIsConnected) teamController->process();
    }
}