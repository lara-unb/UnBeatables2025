#pragma once

#include "ballDetector/BallDetector.hpp"
#include "camera/NaoqiCameraStrategy.hpp"
#include "ballDetector/BallDetector.hpp"

class Perception {
private:
    CameraStrategy *camera;
    BallDetector *ballDetector;
    std::atomic<bool> isRunning;
    void updatePerceptionBoardTop() const;
    void updatePerceptionBoardBot() const;


public:
    Perception();
    ~Perception();

    void process();
    void close();
};
