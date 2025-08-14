#include "communication/Communication.hpp"

#include <UnBoard.hpp>
#include <unistd.h>
#include "Logs/EasyLogging.h"
#include "ConnectionConfig.hpp"
#include "communication/socket/client/UDPClient.hpp"
#include "communication/socket/server/UDPServer.hpp"

Communication::Communication() {
#ifdef USE_UDP
    client = new UDPClient(gameControllerAddress.ip, gameControllerAddress.writingPort);
    server = new UDPServer("0.0.0.0", gameControllerAddress.readingPort);
#else
    socket = new TCPSocket("", 1);
#endif
    isRunning = true;
    gameController = new GameController();
}

void Communication::close() {
    isRunning = false;
    sleep(1);
    delete client;
    delete server;
}

void Communication::process() const {
    while (isRunning) {
        roboCupControlBoard = gameController->adapterControlData(server->receiveData());
        client->sendData(gameController->adapterReturnData(*reinterpret_cast<RoboCupGameControlReturnData*>(&unbeatablesReturnBoard)));
        sleep(1);
    }
}
