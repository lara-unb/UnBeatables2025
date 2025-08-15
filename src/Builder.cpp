#include "Builder.hpp"
#include "Logs/EasyLogging.h"
#include "perception/camera/NaoqiCamera.hpp"
#include "perception/camera/V4L2Camera.hpp"
#include "perception/detectors/BallDetector.hpp"

Behavior* Builder::buildBehavior() {
    return new Behavior();
}

Perception* Builder::buildPerception() {
    LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using cascade (" << systemSettings.cascade <<")\x1B[0m";
    std::unique_ptr<BallDetector> ballDetector(new BallDetector(systemSettings.cascade));

    std::unique_ptr<Camera> camera;
    switch (systemSettings.camera) {
        case NAOQI_CAMERA:
            LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using NAOqiCamera\x1B[0m";
            camera.reset(new NaoqiCamera());
            break;
        case V4L2_CAMERA:
            LOG(INFO) << "\x1B[32m[BUILDER] Perception - Using V4L2Camera\x1B[0m";
            camera.reset(new V4L2Camera());
            break;
        default:
            throw std::runtime_error("Camera strategy not found");
    }

    return new Perception(camera.release(), ballDetector.release());
}


Communication* Builder::buildCommunication(){
    return new Communication();
}