#include "ui.hpp"
#include <opencv2/opencv.hpp>

void displayGesture(cv::Mat& frame, const std::string& gesture_label) {
    int font = cv::FONT_HERSHEY_SIMPLEX;
    double scale = 1.0;
    int thickness = 2;
    cv::Scalar color(0, 255, 0);
    cv::putText(frame, "Gesture: " + gesture_label, cv::Point(30, 50), font, scale, color, thickness);
    cv::imshow("Video-to-Gesture", frame);
}
