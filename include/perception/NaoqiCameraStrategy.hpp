#pragma once

#include "CameraStrategy.hpp"
#include <alproxies/alvideodeviceproxy.h>

class NaoqiCameraStrategy : public CameraStrategy {
private:
    AL::ALVideoDeviceProxy*camera = nullptr;

public:
    bool open() override;
    void close() override;
    cv::Mat getTopCamera() override;
    cv::Mat getBotCamera() override;

    NaoqiCameraStrategy();
    ~NaoqiCameraStrategy() override;
};
