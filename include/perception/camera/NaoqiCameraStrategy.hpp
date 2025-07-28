#pragma once

#include "CameraStrategy.hpp"
#include <alproxies/alvideodeviceproxy.h>
#include <memory>
#include <string>

class NaoqiCameraStrategy : public CameraStrategy {
private:
    AL::ALVideoDeviceProxy videoService;
    std::string topClient = "cpp_client_top";
    std::string bottomClient = "cpp_client_bottom";

    cv::Mat getCameraFrame(std::string& clientId);

public:
    NaoqiCameraStrategy();
    ~NaoqiCameraStrategy() override;

    void open() override;
    void close() override;
    cv::Mat getTopCamera() override;
    cv::Mat getBotCamera() override;
};