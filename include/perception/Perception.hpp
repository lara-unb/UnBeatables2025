#pragma once

#include "detectors/BallDetector.hpp"
#include "camera/Camera.hpp"

class Perception {
private:
    Camera *camera;
    BallDetector *ballDetector;
    std::atomic<bool> isRunning;

public:
    Perception(Camera *camera, BallDetector *ballDetector);
    void close();
    void process() const;
};
