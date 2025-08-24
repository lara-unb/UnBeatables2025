#include "communication/gameController/GameController.hpp"
#include "Logs/EasyLogging.h"

GameController::GameController(UDPClient* client, UDPServer* server)
    : client(client), server(server)
{
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Starting Game Controller\x1B[0m";
}

RoboCupGameControlData GameController::convertToRoboCupGameData(const std::vector<uint8_t> data) {
    if (data.size() < sizeof(RoboCupGameControlData)) {
        LOG(INFO) << "\x1B[35m[GAMECONTROLLER] Smaller package than expected!\x1B[0m";
        return incomingData;
    }
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] RoboCupGameControlData received successfully\x1B[0m";
    std::memcpy(&incomingData, data.data(), sizeof(RoboCupGameControlData));
    return incomingData;
}

GameController::~GameController() {
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Closing sockets\x1B[0m";
    delete client;
    delete server;
}

std::vector<uint8_t> GameController::convertToVector(const RoboCupGameControlReturnData& data) {
    constexpr size_t structSize = sizeof(RoboCupGameControlReturnData);

    std::vector<uint8_t> bytes(structSize);
    std::memcpy(bytes.data(), &data, structSize);
    return bytes;
}

bool GameController::verifyConnection() {
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Testing connection\x1B[0m";
    try {
        auto future = std::async(std::launch::async, [this] {
            process();
        });

        if (future.wait_for(std::chrono::seconds(2)) == std::future_status::timeout) {
            LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Timeout waiting for message\x1B[0m";
            return false;
        }
    } catch (const std::exception& e) {
        LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Error in testConnection: " << e.what() << "\x1B[0m";
        return false;
    }
    LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Connection established\x1B[0m";
    return true;
}

void GameController::process() {
    std::memcpy(&outgoingData, &unbeatablesReturnBoard, sizeof(RoboCupGameControlReturnData));
    client->sendData(convertToVector(outgoingData));

    std::vector<uint8_t> data = server->receiveData();
    if (data.size() >= sizeof(RoboCupGameControlData)) {
        RoboCupGameControlData message = convertToRoboCupGameData(data);
        std::memcpy(&roboCupControlBoard, &message, sizeof(RoboCupGameControlData));
    }
}