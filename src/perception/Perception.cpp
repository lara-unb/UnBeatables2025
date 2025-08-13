#include <perception/Perception.hpp>
#include <UnBoard.hpp>
#include "Logs/EasyLogging.h"

Perception::Perception() {
    isRunning = false;
#ifdef USE_NAOQI
    camera = new NaoqiCameraStrategy();
    isRunning = true;
#else
    camera = nullptr;
    LOG(ERROR) << "\x1B[31m[PERCEPTION] Error: Camera strategy not found\x1B[0m";
    throw std::runtime_error("Failed to set camera strategy (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
#endif

    ballDetector = new BallDetector("include/perception/cascade/cascade-2024-10.xml");
}

void Perception::close() {
    isRunning = false;
    camera->close();
}

void Perception::process() const {
    while (isRunning) {
        perceptionBoard.topCamera = ballDetector->detectBallTop(camera->getTopCamera());
        perceptionBoard.botCamera = ballDetector->detectBallBot(camera->getBotCamera());
    }
}