#include <action/animations/CapoeiraLeft.h>
#include <action/animations/CapoeiraRight.h>
#include <action/kick/Kick.h>
#include "Logs/EasyLogging.h"
#include "ConnectionSettings.hpp"
#include <alcommon/alproxy.h>
#include <alvalue/alvalue.h>

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
    playAnimation(capoeiraRight);
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