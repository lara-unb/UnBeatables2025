#pragma once
#include <vector>
#include <string>

struct Keyframe {
    double value;
    std::vector<double> inSlope;
    std::vector<double> outSlope;
};

struct JointMotion {
    std::string name;
    std::vector<double> times;
    std::vector<std::vector<Keyframe>> keys;
};

struct Animation {
    std::string name;
    std::vector<JointMotion> motions;
};