#include "communication/Communication.hpp"

#include <UnBoard.hpp>
#include <unistd.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"
#include "communication/socket/client/UDPClient.hpp"
#include "communication/socket/server/UDPServer.hpp"

Communication::Communication(GameController* gamecontroller, Client* gameControllerClient, Server* gameControllerServer):
gameController(gamecontroller), gameControllerClient(gameControllerClient), gameControllerServer(gameControllerServer)
{
    isRunning = true;
}

void Communication::close() {
    isRunning = false;
    sleep(1);
    delete gameControllerClient;
    delete gameControllerServer;
}

void Communication::process() const {
    while (isRunning) {
        gameControllerClient->sendUnicast(gameController->adapterReturnData(unbeatablesReturnBoard));

        std::vector<uint8_t> data = gameControllerServer->receiveData();
        if (data.size() >= sizeof(RoboCupGameControlData))
            std::memcpy(&roboCupControlBoard, data.data(), sizeof(RoboCupGameControlData));

        sleep(0.5);
    }
}
