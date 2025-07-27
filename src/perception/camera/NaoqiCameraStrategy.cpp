#include <alcommon/alproxy.h>
#include <alvision/alimage.h>
#include <perception/camera/NaoqiCameraStrategy.hpp>
#include <opencv2/opencv.hpp>

#include "EasyLogging.h"
#include "NaoConnectionConfig.hpp"

NaoqiCameraStrategy::NaoqiCameraStrategy()
    : videoProxy(new AL::ALVideoDeviceProxy(naoConfig.ip, naoConfig.port)) {
    LOG(INFO) << "\x1B[35m[CAMERA] Using the NAOqi camera\x1B[0m";
}

NaoqiCameraStrategy::~NaoqiCameraStrategy() {
    NaoqiCameraStrategy::close();
}

void NaoqiCameraStrategy::open() {
    LOG(INFO) << "\x1B[35m[CAMERA] Opening NAOqi cameras\x1B[0m";
    try {
        videoProxy->subscribeCamera(topClient, 0, AL::kQVGA, AL::kBGRColorSpace, 5);
        videoProxy->subscribeCamera(bottomClient, 1, AL::kQVGA, AL::kBGRColorSpace, 5);
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to open cameras (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
    }
}

void NaoqiCameraStrategy::close() {
    LOG(INFO) << "\x1B[35m[CAMERA] Closing NAOqi cameras\x1B[0m";
    try {
        videoProxy->unsubscribe(topClient);
        videoProxy->unsubscribe(bottomClient);
    } catch (const std::exception& e) {
        LOG(ERROR) << "Failed to close cameras properly: " << e.what();
    }
}

cv::Mat NaoqiCameraStrategy::getCameraFrame(const std::string& clientId) const {
    try {
        AL::ALValue img = videoProxy->getImageRemote(clientId);
        if (img.getType() == AL::ALValue::TypeInvalid || img.getSize() <= 6) {
            LOG(WARNING) << "\x1B[35m[CAMERA] Invalid image data from client: " << clientId << "\x1B[0m";
            return {};
        }

        return [&] {
            cv::Mat colorImage(
                static_cast<int>(img[1]),
                static_cast<int>(img[0]),
                CV_8UC3,
                const_cast<unsigned char*>(static_cast<const unsigned char*>(img[6].GetBinary()))
            );

            cv::Mat grayImage;
            cv::cvtColor(colorImage, grayImage, cv::COLOR_BGR2GRAY);
            return grayImage.clone();
        }();
    } catch (const std::exception& e) {
        LOG(ERROR) << "\x1B[35m[CAMERA] Failed to get image from " << clientId << ": " << e.what() << "\x1B[0m";
        throw std::runtime_error("Failed to get image (File: " + std::string(__FILE__) + ", Line: " + std::to_string(__LINE__) + ")");
    }
}

cv::Mat NaoqiCameraStrategy::getTopCamera() {
    LOG(INFO) << "\x1B[35m[CAMERA] Getting top camera (NAOqi)\x1B[0m";
    return getCameraFrame(topClient);
}

cv::Mat NaoqiCameraStrategy::getBotCamera() {
    LOG(INFO) << "\x1B[35m[CAMERA] Getting bottom camera (NAOqi)\x1B[0m";
    return getCameraFrame(bottomClient);
}