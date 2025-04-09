#include <vector>
#include <opencv2/opencv.hpp>

struct Landmark {
    float x, y, z;
};

std::vector<Landmark> detectPose(const cv::Mat &frame) {
    std::vector<Landmark> landmarks;
    return landmarks;
}
