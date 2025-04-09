#include "gesture_model.hpp"
#include <onnxruntime_cxx_api.h>
#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>

Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "gesture-model");
Ort::SessionOptions session_options;
std::unique_ptr<Ort::Session> session;
std::vector<const char*> input_node_names;
std::vector<const char*> output_node_names;

void loadGestureModel(const std::string& model_path) {
    session_options.SetIntraOpNumThreads(1);
    session = std::make_unique<Ort::Session>(env, model_path.c_str(), session_options);
    Ort::AllocatorWithDefaultOptions allocator;
    input_node_names.push_back(session->GetInputName(0, allocator));
    output_node_names.push_back(session->GetOutputName(0, allocator));
}

std::string predictGesture(const std::vector<float>& features) {
    Ort::MemoryInfo memory_info = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);
    std::array<int64_t, 2> input_shape{1, static_cast<int64_t>(features.size())};
    Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, const_cast<float*>(features.data()), features.size(), input_shape.data(), input_shape.size());

    auto output_tensors = session->Run(Ort::RunOptions{nullptr}, input_node_names.data(), &input_tensor, 1, output_node_names.data(), 1);
    float* output_data = output_tensors.front().GetTensorMutableData<float>();

    int max_index = 0;
    float max_value = output_data[0];
    for (size_t i = 1; i < output_tensors.front().GetTensorTypeAndShapeInfo().GetShape()[1]; ++i) {
        if (output_data[i] > max_value) {
            max_value = output_data[i];
            max_index = static_cast<int>(i);
        }
    }

    std::ifstream file("labels.txt");
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        if (count == max_index) return line;
        count++;
    }
    return "Unknown";
}
