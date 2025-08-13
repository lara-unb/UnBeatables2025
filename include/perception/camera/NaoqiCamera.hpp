#pragma once

#include "Camera.hpp"
#include <alproxies/alvideodeviceproxy.h>
#include <string>

class NaoqiCamera : public Camera {
private:
    AL::ALVideoDeviceProxy videoService;
    std::string topClient = "cpp_client_top";
    std::string bottomClient = "cpp_client_bottom";

    cv::Mat getCameraFrame(std::string& clientId);

public:
    NaoqiCamera();
    ~NaoqiCamera() override;

    void open() override;
    void close() override;
    cv::Mat getTopCamera() override;
    cv::Mat getBotCamera() override;
};