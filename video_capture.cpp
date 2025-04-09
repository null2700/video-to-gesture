#include <opencv2/opencv.hpp>
#include <iostream>

cv::VideoCapture initializeCamera(int deviceIndex) {
    cv::VideoCapture cap(deviceIndex);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
    return cap;
}

cv::Mat captureFrame(cv::VideoCapture &cap) {
    cv::Mat frame;
    cap >> frame;
    return frame;
}
