#pragma once

#include "Camera.hpp"

class V4L2Camera : public Camera {
private:

public:
    V4L2Camera();
    ~V4L2Camera() override;

    void open() override;
    void close() override;
    cv::Mat getTopCamera() override;
    cv::Mat getBotCamera() override;
};