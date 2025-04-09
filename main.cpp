#include <opencv2/opencv.hpp>
#include <iostream>
#include "video_input.hpp"
#include "mediapipe_wrapper.hpp"
#include "feature_utils.hpp"
#include "gesture_model.hpp"
#include "ui.hpp"
#include "speech.hpp"

int main() {
    // Initialize video capture
    cv::VideoCapture cap = initializeCamera(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Cannot open camera." << std::endl;
        return -1;
    }

    // Load gesture recognition model
    auto model = loadGestureModel("gesture_model.onnx");

    while (true) {
        // Step 1: Capture frame
        cv::Mat frame = captureFrame(cap);
        if (frame.empty()) break;

        // Step 2: Pose Detection using MediaPipe
        auto landmarks = detectPose(frame);
        if (landmarks.empty()) continue;

        // Step 3: Feature Vector Creation
        std::vector<float> featureVector = extractFeatures(landmarks);

        // Step 4: Gesture Prediction
        std::string gestureLabel = predictGesture(model, featureVector);

        // Step 5: Display Output
        displayGesture(frame, gestureLabel);

        // Step 6: Optional - Speak gesture
        speakGesture(gestureLabel);

        // Show the frame
        cv::imshow("Gesture Recognition", frame);
        if (cv::waitKey(1) == 27) break; // ESC to quit
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
