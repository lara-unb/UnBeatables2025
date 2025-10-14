#include <thread>
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
    LOG(INFO) << "\x1B[37m[MOTION] Moving (" << x << " | " << y << ") - short stable steps\x1B[0m";

    float safeX = std::max(std::min(x * 0.4f, 0.4f), -0.4f);  // Máximo 40% velocidade
    float safeY = std::max(std::min(y * 0.25f, 0.25f), -0.25f); // Máximo 25% lateral

    AL::ALValue config = AL::ALValue::array(
        AL::ALValue::array("MaxStepX", 0.013f),        // Passos muito curtos
        AL::ALValue::array("MaxStepY", 0.04f),        // Lateral mínimo
        AL::ALValue::array("StepHeight", 0.03f),     // Elevação baixíssima
        AL::ALValue::array("MaxStepFrequency", 0.8f), // Ritmo rápido mas seguro
        AL::ALValue::array("MinStepFrequency", 0.4f), // Frequência mínima controlada
        AL::ALValue::array("StepHeight", 0.1f),     // Passo rasteiro
        AL::ALValue::array("TorsoWx", 0.0f),          // Torso totalmente estável
        AL::ALValue::array("TorsoWy", 0.02f)     // Balanço mínimo
    );

    motionService.setMotionConfig(config);
    motionService.moveToward(safeX * -1, safeY * -1, 0.0f);
}

// void Motion::move(float x, float y) {
//     LOG(INFO) << "\x1B[37m[MOTION] Moving (" << x << " | " << y << ") with alternating feet\x1B[0m";
//
//     float targetX = std::abs(x);
//     float direction = (x > 0) ? 1.0f : -1.0f;
//
//     AL::ALValue config = AL::ALValue::array(
//         AL::ALValue::array("MaxStepX", 0.06f),
//         AL::ALValue::array("MaxStepY", 0.1f),
//         AL::ALValue::array("StepHeight", 0.022f),
//         AL::ALValue::array("MaxStepFrequency", 0.75f)
//     );
//
//     motionService.setMotionConfig(config);
//
//     float remainingDistance = targetX;
//     const float stepSize = 0.055f;
//     bool leftFootFirst = true;
//
//     while (remainingDistance > 0) {
//         try {
//             float currentStep = std::min(stepSize, remainingDistance);
//
//             std::vector<std::string> legs;
//             AL::ALValue footSteps;
//
//             if (leftFootFirst) {
//                 legs = {"LLeg", "RLeg"};
//                 footSteps = AL::ALValue::array(
//                     AL::ALValue::array(direction * currentStep, 0.0f, 0.0f),
//                     AL::ALValue::array(direction * currentStep, 0.0f, 0.0f)
//                 );
//             } else {
//                 legs = {"RLeg", "LLeg"};
//                 footSteps = AL::ALValue::array(
//                     AL::ALValue::array(direction * currentStep, 0.0f, 0.0f),
//                     AL::ALValue::array(direction * currentStep, 0.0f, 0.0f)
//                 );
//             }
//
//             std::vector<float> timeList = {1.0f, 2.0f};
//             motionService.setFootSteps(legs, footSteps, timeList, true);
//
//             remainingDistance -= currentStep;
//             leftFootFirst = !leftFootFirst; // Alterna o pé
//
//             LOG(INFO) << "\x1B[37m[MOTION] Step with " << legs[0]
//                       << " first, Remaining: " << remainingDistance << "m\x1B[0m";
//
//             std::this_thread::sleep_for(std::chrono::milliseconds(1400));
//
//         } catch (const AL::ALError& e) {
//             LOG(ERROR) << "\x1B[31m[ERROR] Foot step failed: " << e.what() << "\x1B[0m";
//             break;
//         }
//     }
// }

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
    motionService.setAngles("HeadPitch", clamped_x *-1, 0.1f);
}

void Motion::stopRotate() {
    motionService.move(0.0001f, 0.0f, 0.0f);
}

void Motion::stopMove() {
    motionService.move(0.0f, 0.0f, 0.0f);
}

void Motion::stopMoveHead() {
    motionService.setAngles("HeadYaw", 0.0f, 0.1f);
    motionService.setAngles("HeadPitch", 0.0f, 0.1f);
}