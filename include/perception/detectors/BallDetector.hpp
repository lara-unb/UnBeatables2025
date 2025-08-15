#pragma once

#include <string>
#include <opencv2/opencv.hpp>
#include "UnBoard.hpp"

class BallDetector {
private:
    cv::CascadeClassifier cascade;
    std::vector<cv::Rect> detectedBallTop;
    std::vector<cv::Rect> detectedBallBot;

public:
    BallDetector(std::string& cascadePath);
    ~BallDetector() = default;

    BallPositionData detectBallTop(const cv::Mat& cameraFrame);
    BallPositionData detectBallBot(const cv::Mat& cameraFrame);
};
