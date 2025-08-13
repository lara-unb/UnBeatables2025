#pragma once

#include <opencv2/opencv.hpp>

class Camera {
public:
    virtual ~Camera() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual cv::Mat getTopCamera() = 0;
    virtual cv::Mat getBotCamera() = 0;
};