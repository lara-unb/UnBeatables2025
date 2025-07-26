#include <perception/Perception.hpp>
#include <EasyLogging.h>

Perception::Perception() {
#ifdef USE_NAOQI
    camera = new NaoqiCameraStrategy();
#else
    camera = nullptr;
    LOG(ERROR) << "\x1B[31m[PERCEPTION] Error: Camera strategy not found\x1B[0m";
    throw std::runtime_error("Failed to set camera strategy (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
#endif
    camera->getBotCamera();
}

Perception::~Perception() {
    delete camera;
}