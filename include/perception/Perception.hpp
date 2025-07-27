#pragma once

#include "camera/NaoqiCameraStrategy.hpp"

class Perception {
private:
    CameraStrategy *camera;
    std::atomic<bool> isRunning;

public:
    Perception();
    ~Perception();

    void process();
    void close();
};
