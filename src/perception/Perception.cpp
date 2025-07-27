#include <perception/Perception.hpp>
#include <UnBoard.hpp>
#include "EasyLogging.h"

Perception::Perception() {
#ifdef USE_NAOQI
    camera = new NaoqiCameraStrategy();
#else
    camera = nullptr;
    LOG(ERROR) << "\x1B[31m[PERCEPTION] Error: Camera strategy not found\x1B[0m";
    throw std::runtime_error("Failed to set camera strategy (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
#endif
    isRunning = true;
}

Perception::~Perception() {
    close();
    delete camera;
}

void Perception::process() {
    while (isRunning) {
        camera->getTopCamera();
        camera->getBotCamera();
        LOG(INFO) << "\x1B[31m[PERCEPTION] Teste perception: pegando a altura:  \x1B[0m" << perceptionBoard.height;
    }
}

void Perception::close() {
    if (!isRunning) return;
    isRunning = false;
    if (camera) camera->close();
}