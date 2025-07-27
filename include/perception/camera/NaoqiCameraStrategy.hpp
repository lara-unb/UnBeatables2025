#pragma once

#include "CameraStrategy.hpp"
#include <alproxies/alvideodeviceproxy.h>
#include <memory>
#include <string>

class NaoqiCameraStrategy : public CameraStrategy {
private:
    std::unique_ptr<AL::ALVideoDeviceProxy> videoProxy;
    const std::string topClient = "cpp_client_top";
    const std::string bottomClient = "cpp_client_bottom";

    cv::Mat getCameraFrame(const std::string& clientId) const;

public:
    NaoqiCameraStrategy();
    ~NaoqiCameraStrategy() override;

    void open() override;
    void close() override;
    cv::Mat getTopCamera() override;
    cv::Mat getBotCamera() override;
};