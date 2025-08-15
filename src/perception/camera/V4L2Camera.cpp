#include <perception/camera/V4L2Camera.hpp>
#include <opencv2/opencv.hpp>

#include "Logs/EasyLogging.h"

V4L2Camera::V4L2Camera(){
    LOG(INFO) << "\x1B[35m[CAMERA] Using the V4L2 camera\x1B[0m";
}

V4L2Camera::~V4L2Camera() {
    V4L2Camera::close();
}

void V4L2Camera::open() {

}

void V4L2Camera::close() {

}

cv::Mat V4L2Camera::getTopCamera() {
    return {};
}

cv::Mat V4L2Camera::getBotCamera() {
    return {};
}