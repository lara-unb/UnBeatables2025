#pragma once

#include "detectors/BallDetector.hpp"
#include "camera/Camera.hpp"

class Perception {
private:
    Camera *camera;
    BallDetector *ballDetector;
    std::atomic<bool> isRunning;

public:
    Perception();
    void close();
    void process() const;
};
