#include <perception/NaoqiCameraStrategy.hpp>
#include "EasyLogging.h"

NaoqiCameraStrategy::NaoqiCameraStrategy() {
    LOG(INFO) << "\x1B[35m[PERCEPTION] Using the NAOqi camera\x1B[0m";
}

NaoqiCameraStrategy::~NaoqiCameraStrategy() {
    delete camera;
    LOG(INFO) << "\x1B[35m[PERCEPTION] Destroying NAOqi camera\x1B[0m";
}

bool NaoqiCameraStrategy::open() {
    LOG(INFO) << "\x1B[35m[PERCEPTION] Opening NAOqi camera\x1B[0m";
    return true;
}

void NaoqiCameraStrategy::close() {
    LOG(INFO) << "\x1B[35m[PERCEPTION] Closing NAOqi camera\x1B[0m";
}

cv::Mat NaoqiCameraStrategy::getTopCamera() {
    LOG(INFO) << "\x1B[35m[PERCEPTION] Getting top camera (NAOqi)\x1B[0m";
    return cv::Mat();
}

cv::Mat NaoqiCameraStrategy::getBotCamera() {
    LOG(INFO) << "\x1B[35m[PERCEPTION] Getting bottom camera (NAOqi)\x1B[0m";
    return cv::Mat();
}
