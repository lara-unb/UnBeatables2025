#include "communication/Communication.hpp"

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
}

void Communication::close() {
    isRunning = false;
    delete client;
    delete server;
}

void Communication::process() const {
    // while (isRunning) {
        client->sendData("teste");
        server->receiveData();
    // }
}
