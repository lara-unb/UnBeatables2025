#include "communication/Communication.hpp"
#include <UnBoard.hpp>
#include "Logs/EasyLogging.h"

Communication::Communication(
    GameController* gamecontroller,
    Client* gameControllerClient,
    Server* gameControllerServer,
    TeamController* teamController,
    Client* teamClient,
    Server* teamServer)
    :gameController(gamecontroller), gameControllerClient(gameControllerClient), gameControllerServer(gameControllerServer),
    teamController(teamController), teamClient(teamClient), teamServer(teamServer)
{
    isRunning = true;
}

void Communication::close() {
    isRunning = false;
    sleep(1);
    delete gameControllerClient;
    delete gameControllerServer;
    delete teamClient;
    delete teamServer;
}

void Communication::processGameController() {
    gameControllerClient->sendData(gameController->convertToVector(unbeatablesReturnBoard));

    std::vector<uint8_t> data = gameControllerServer->receiveData();
    if (data.size() >= sizeof(RoboCupGameControlData))
        std::memcpy(&roboCupControlBoard, data.data(), sizeof(RoboCupGameControlData));
}

void Communication::processTeamController() {
    teamClient->sendData(teamController->convertToVector(selfMessage));

    std::vector<uint8_t> data = teamServer->receiveData();
    if (data.size() >= sizeof(TeamMessage)) {
        uint8_t playerNumber = data[0];
        if (playerNumber >= 0 && playerNumber < MAX_ROBOTS) {
            std::memcpy(&teamMessages[playerNumber], data.data(), sizeof(TeamMessage));
        }
    }
}

void Communication::process() {
    while (isRunning) {
        processGameController();
        processTeamController();
        sleep(0.5);
    }
}
