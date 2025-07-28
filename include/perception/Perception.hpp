#pragma once

#include "detectors/BallDetector.hpp"
#include "camera/NaoqiCameraStrategy.hpp"

class Perception {
private:
    CameraStrategy *camera;
    BallDetector *ballDetector;
    std::atomic<bool> isRunning;

public:
    Perception();
    ~Perception();

    void process() const;
    void close();
};
