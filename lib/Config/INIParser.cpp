#include <fstream>
#include <string>
#include "ConnectionConfig.hpp"

void loadConfig(NAOqiAddress& conn, GameControllerAddress& gc) {
    std::ifstream file("config.ini");
    if (!file)
        throw std::runtime_error("Fail to open config.ini");

    std::string line;
    while (std::getline(file, line)) {
        auto pos = line.find('=');
        if (pos == std::string::npos) continue;

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        if (key == "NAOqiIP") conn.ip = value;
        else if (key == "NAOqiPort") conn.port = std::stoi(value);
        else if (key == "gameControllerIP") gc.ip = value;
        else if (key == "writingPort") gc.writingPort = std::stoi(value);
        else if (key == "readingPort") gc.readingPort = std::stoi(value);
    }
}