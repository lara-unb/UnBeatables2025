#include <fstream>
#include <string>
#include "ConnectionConfig.hpp"
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
        else if (key == "gameControllerIP") gameControllerAddress.ip = value;
        else if (key == "writingPort") gameControllerAddress.writingPort = std::stoi(value);
        else if (key == "readingPort") gameControllerAddress.readingPort = std::stoi(value);
        else if (key == "unbeatablesNumber") unbeatablesReturnBoard.teamNum = std::stoi(value);
        else if (key == "playerNumber") unbeatablesReturnBoard.playerNum  = std::stoi(value);
    }
}