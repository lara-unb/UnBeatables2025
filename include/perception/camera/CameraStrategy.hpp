#pragma once

#include <opencv2/opencv.hpp>

class CameraStrategy {
public:
    virtual ~CameraStrategy() = default;

    virtual void open() = 0;
    virtual void close() = 0;
    virtual cv::Mat getTopCamera() = 0;
    virtual cv::Mat getBotCamera() = 0;
};