#include <fstream>
#include <string>
#include "ConnectionSettings.hpp"
#include "UnBoard.hpp"

void loadConfig() {
    std::ifstream file("config.ini");
    if (!file)
        throw std::runtime_error("Fail to open config.ini");

    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "NAOqiIP") naoqiAddress.ip = value;
        else if (key == "NAOqiPort") naoqiAddress.port = std::stoi(value);
        else if (key == "gameControllerIP") gameControllerAddress.host = value;
        else if (key == "writingPort") gameControllerAddress.writingPort = std::stoi(value);
        else if (key == "readingPort") gameControllerAddress.readingPort = std::stoi(value);
        else if (key == "broadcast") teamCommunicationAddress.broadcast = value;
        else if (key == "multicast") teamCommunicationAddress.multicast = value;
        else if (key == "teamPort") teamCommunicationAddress.teamPort = std::stoi(value);
        else if (key == "unbeatablesNumber") unbeatablesReturnBoard.teamNum = std::stoi(value);
        else if (key == "playerNumber") {
            unbeatablesReturnBoard.playerNum  = std::stoi(value);
            selfMessage.playerNumber = std::stoi(value);
        }
        else if (key == "camera") systemSettings.camera = std::stoi(value);
        else if (key == "cascade") systemSettings.cascade = value;
        else if (key == "controlDevice") controlState.device = value;
    }
}