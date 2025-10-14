#include <action/animations/CapoeiraLeft.h>
#include <action/animations/CapoeiraRight.h>
#include <action/kick/Kick.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"
#include <alcommon/alproxy.h>
#include <alvalue/alvalue.h>

#include "action/animations/Idle.h"

Kick::Kick()
    : motion(boost::make_shared<AL::ALProxy>(session, "ALMotion"))
{
    LOG(INFO) << "\x1B[37m[KICK] Started successfully\x1B[0m";
}

Kick::~Kick() {
    LOG(INFO) << "\x1B[37m[KICK] Closing Kick\x1B[0m";
}

void Kick::capoeiraKickLeft() {
    playAnimation(capoeiraLeft);
}

void Kick::capoeiraKickRight() {
        try {
            // 1. Desabilita os comportamentos de postura idle dos braços
            motion.setIdlePostureEnabled("Arms", false);
            motion.setIdlePostureEnabled("LArm", false);
            motion.setIdlePostureEnabled("RArm", false);

            // 2. Configura a stiffeness máxima para travar as juntas
            std::vector<std::string> armJoints = {
                "LShoulderPitch", "LShoulderRoll", "LElbowYaw", "LElbowRoll", "LWristYaw", "LHand",
                "RShoulderPitch", "RShoulderRoll", "RElbowYaw", "RElbowRoll", "RWristYaw", "RHand"
            };

            std::vector<float> maxStiffness(armJoints.size(), 1.0f); // Stiffness máxima
            motion.setStiffnesses(armJoints, maxStiffness);

            // 3. Move para a posição desejada
            motion.setAngles("LShoulderPitch", 2.08032f, 0.15f);
            motion.setAngles("LShoulderRoll", 0.232204f, 0.15f);
            motion.setAngles("LElbowYaw", 0.23115f, 0.15f);
            motion.setAngles("LElbowRoll", -1.00488f, 0.15f);
            motion.setAngles("LWristYaw", -1.81776f, 0.15f);
            motion.setAngles("LHand", 0.00852656f, 0.1f);

            motion.setAngles("RShoulderPitch", 2.07949f, 0.15f);
            motion.setAngles("RShoulderRoll", -0.251327f, 0.15f);
            motion.setAngles("RElbowYaw", -0.0636714f, 0.15f);
            motion.setAngles("RElbowRoll", 1.03516f, 0.15f);
            motion.setAngles("RWristYaw", 1.81566f, 0.15f);
            motion.setAngles("RHand", 0.121521f, 0.1f);

            // 4. Aguarda o movimento terminar
            // std::this_thread::sleep_for(std::chrono::milliseconds(800));

            LOG(INFO) << "\x1B[32m[ARMS] Arms locked in standing pose permanently\x1B[0m";

        } catch (const AL::ALError& e) {
            LOG(ERROR) << "\x1B[31m[ERROR] Failed to lock arms position: " << e.what() << "\x1B[0m";
        }

}

void Kick::playAnimation(const Animation& anim) {
    LOG(INFO) << "\x1B[36m[ANIMATION] Running " << anim.name << "\x1B[0m";
    try {
        AL::ALValue names;
        AL::ALValue times;
        AL::ALValue keys;

        names.arraySetSize(anim.motions.size());
        times.arraySetSize(anim.motions.size());
        keys.arraySetSize(anim.motions.size());

        for (size_t i = 0; i < anim.motions.size(); i++) {
            const auto& joint = anim.motions[i];
            names[i] = joint.name;

            AL::ALValue jointTimes;
            jointTimes.arraySetSize(joint.times.size());
            for (size_t j = 0; j < joint.times.size(); j++) {
                jointTimes[j] = static_cast<float>(joint.times[j]);
            }
            times[i] = jointTimes;

            AL::ALValue jointKeys;
            jointKeys.arraySetSize(joint.keys.size());

            for (size_t k = 0; k < joint.keys.size(); k++) {
                if (joint.keys[k].empty()) {
                    LOG(WARNING) << "Empty keyframe" << joint.name << " i " << k;
                    continue;
                }
                const auto& kf = joint.keys[k][0];

                AL::ALValue keyframe;
                keyframe.arraySetSize(3);

                keyframe[0] = static_cast<float>(kf.value);

                AL::ALValue inParams;
                inParams.arraySetSize(3);
                if (kf.inSlope.size() >= 3) {
                    inParams[0] = static_cast<int>(kf.inSlope[0]);
                    inParams[1] = static_cast<float>(kf.inSlope[1]);
                    inParams[2] = static_cast<float>(kf.inSlope[2]);
                } else {
                    inParams[0] = 3;
                    inParams[1] = -0.5f;
                    inParams[2] = 0.0f;
                }
                keyframe[1] = inParams;

                AL::ALValue outParams;
                outParams.arraySetSize(3);
                if (kf.outSlope.size() >= 3) {
                    outParams[0] = static_cast<int>(kf.outSlope[0]);
                    outParams[1] = static_cast<float>(kf.outSlope[1]);
                    outParams[2] = static_cast<float>(kf.outSlope[2]);
                } else {
                    outParams[0] = 3;
                    outParams[1] = 0.5f;
                    outParams[2] = 0.0f;
                }
                keyframe[2] = outParams;

                jointKeys[k] = keyframe;
            }
            keys[i] = jointKeys;
        }

        motion.angleInterpolationBezier( names, times, keys);

    } catch (const AL::ALError& e) {
        LOG(ERROR) << "\x1B[31m[ERROR] Fail" << anim.name << "': " << e.what() << "\x1B[0m";
    }
}