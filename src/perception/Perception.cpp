#include <perception/Perception.hpp>
#include <UnBoard.hpp>
#include <unistd.h>
#include <perception/camera/NaoqiCamera.hpp>
#include "Logs/EasyLogging.h"

Perception::Perception(Camera *camera, BallDetector *ballDetector):
camera(camera), ballDetector(ballDetector)
{
    isRunning = true;
}

void Perception::close() {
    isRunning = false;
    sleep(1);
    camera->close();
}

void Perception::process() const {
    while (isRunning) {
        perceptionBoard.topCamera = ballDetector->detectBallTop(camera->getTopCamera());
        perceptionBoard.botCamera = ballDetector->detectBallBot(camera->getBotCamera());
    }
}