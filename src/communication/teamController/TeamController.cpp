#include "communication/teamController/TeamController.hpp"
#include "Logs/EasyLogging.h"

TeamController::TeamController(UDPClient* client, UDPServer* server)
    : client(client), server(server)
{
    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Starting Team Controller\x1B[0m";
    if (sizeof(TeamMessage) > MAX_PAYLOAD) {
        throw std::length_error("Message too large for Team Controller");
    }
}

TeamController::~TeamController() {
    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Closing sockets\x1B[0m";
    delete client;
    delete server;
}

TeamMessage TeamController::convertToTeamMessage(const std::vector<uint8_t> data) {
    if (data.size() < sizeof(TeamMessage)) {
        LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Smaller package than expected!\x1B[0m";
        return incomingData;
    }

    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] TeamMessage received successfully\x1B[0m";
    std::memcpy(&incomingData, data.data(), sizeof(TeamMessage));
    return incomingData;
}

std::vector<uint8_t> TeamController::convertToVector(const TeamMessage& data) {
    constexpr size_t structSize = sizeof(TeamMessage);

    std::vector<uint8_t> bytes(structSize);
    std::memcpy(bytes.data(), &data, structSize);
    return bytes;
}

bool TeamController::verifyConnection() {
    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Testing connection\x1B[0m";
    try {
        auto future = std::async(std::launch::async, [this] {
            process();
        });

        if (future.wait_for(std::chrono::seconds(2)) == std::future_status::timeout) {
            LOG(INFO) << "\x1B[93m[GAMECONTROLLER] Timeout waiting for message\x1B[0m";
            return false;
        }
    } catch (const std::exception& e) {
        LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Error in testConnection: " << e.what() << "\x1B[0m";
        return false;
    }
    LOG(INFO) << "\x1B[93m[TEAMCONTROLLER] Connection established\x1B[0m";
    return true;
}

void TeamController::process() {
    std::memcpy(&outgoingData, &selfMessage, sizeof(TeamMessage));
    client->sendData(convertToVector(outgoingData));

    std::vector<uint8_t> data = server->receiveData();
    if (data.size() >= sizeof(TeamMessage)) {
        uint8_t playerNumber = data[0];
        if (playerNumber < MAX_ROBOTS) {
            TeamMessage message = convertToTeamMessage(data);
            std::memcpy(&teamMessages[playerNumber], &message, sizeof(TeamMessage));
        }
    }
}