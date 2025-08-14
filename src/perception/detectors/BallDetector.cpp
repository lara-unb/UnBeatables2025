#include <perception/detectors/BallDetector.hpp>
#include "Logs/EasyLogging.h"

BallDetector::BallDetector(const std::string& cascadePath) {
    if (!cascade.load(cascadePath)) {
        LOG(ERROR) << "Failed to load cascade from: " << cascadePath;
        throw std::runtime_error("Failed to load cascade (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
    }
}

BallPositionData BallDetector::detectBallTop(const cv::Mat& cameraFrame) {
    detectedBallTop.clear();
    cascade.detectMultiScale(cameraFrame, detectedBallTop, 1.2, 2, 0, cv::Size(20, 20), cv::Size(90, 90));

    if (!detectedBallTop.empty()) {
        const cv::Rect& ball = detectedBallTop[0];
        return BallPositionData{
            true,
            ((ball.x + ball.width / 2) / perceptionBoard.cameraWidth),
            ((ball.y + ball.height / 2) / perceptionBoard.cameraHeight)
        };
    }
    // LOG(INFO) << "\x1B[31m[BALLDETECTORTOP] Ball not found\x1B[0m";
    return BallPositionData{false, 0, 0};
}

BallPositionData BallDetector::detectBallBot(const cv::Mat& cameraFrame) {
    detectedBallBot.clear();
    cascade.detectMultiScale(cameraFrame, detectedBallBot, 1.3, 5, 0, cv::Size(10, 10));

    if (!detectedBallBot.empty()) {
        const cv::Rect& ball = detectedBallBot[0];
        return BallPositionData{
            true,
            ((ball.x + ball.width / 2) / perceptionBoard.cameraWidth),
            ((ball.y + ball.height / 2) / perceptionBoard.cameraHeight)
        };
    }
    // LOG(INFO) << "\x1B[31m[BALLDETECTORBOT] Ball not found\x1B[0m";
    return BallPositionData{false, 0, 0};
}