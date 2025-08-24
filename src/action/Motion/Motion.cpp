#include <action/motion/Motion.h>
#include <alcommon/alproxy.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"

Motion::Motion()
    : motionService(boost::make_shared<AL::ALProxy>(session, "ALMotion")) {
    LOG(INFO) << "\x1B[37m[MOTION] Using the NAOqi motionService\x1B[0m";
}

Motion::~Motion() {
    LOG(INFO) << "\x1B[37m[MOTION] Stopping motionService\x1B[0m";
    motionService.exit();
}

void Motion::wakeUp() {
    LOG(INFO) << "\x1B[37m[MOTION] Getting up\x1B[0m";
    motionService.wakeUp();
}

void Motion::rest() {
    LOG(INFO) << "\x1B[37m[MOTION] Sitting\x1B[0m";
    motionService.rest();
}