#include <action/motion/Motion.h>
#include <alcommon/alproxy.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"

#define HEAD_YAW_MIN   -2.0857f
#define HEAD_YAW_MAX    2.0857f
#define HEAD_PITCH_MIN_GLOBAL  -0.6720f
#define HEAD_PITCH_MAX_GLOBAL  0.5149f

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

void Motion::move(float x, float y) {
    LOG(INFO) << "\x1B[37m[MOTION] Moving (" << x << " | " << y << ")\x1B[0m";
    motionService.move(x, y, 0.0f);
}

void Motion::rotate(bool side) {
    float direction = side ? 1.0f : -1.0f;
    LOG(INFO) << "\x1B[37m[MOTION] Rotating " << (side ? "Right (1)" : "Left (-1)") << "\x1B[0m";
    motionService.move(0.0f, 0.0f, direction);
}

void Motion::moveHead(float x, float y) {
    LOG(INFO) << "\x1B[37m[MOTION] Moving Head (" << x << " | " << y << ")\x1B[0m";

    float inverted_x = -x;
    float inverted_y = -y;

    float clamped_x = std::max(std::min(inverted_x, HEAD_YAW_MAX), HEAD_YAW_MIN);
    float pitch_min, pitch_max;

    if (std::abs(clamped_x) < 0.1f) {
        pitch_min = HEAD_PITCH_MIN_GLOBAL;
        pitch_max = HEAD_PITCH_MAX_GLOBAL;
    } else {
        pitch_min = -0.5f;
        pitch_max = 0.3f;
    }

    float clamped_y = std::max(std::min(inverted_y, pitch_max), pitch_min);

    motionService.setAngles("HeadYaw", clamped_y, 0.1f);
    motionService.setAngles("HeadPitch", clamped_x, 0.1f);
}

void Motion::stopRotate() {
    motionService.move(0.0f, 0.0f, 0.0f);
}

void Motion::stopMove() {
    motionService.move(0.0f, 0.0f, 0.0f);
}

void Motion::stopMoveHead() {
    motionService.setAngles("HeadYaw", 0.0f, 0.1f);
    motionService.setAngles("HeadPitch", 0.0f, 0.1f);
}