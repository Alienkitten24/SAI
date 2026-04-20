#pragma once

#include <JuceHeader.h>
#include <atomic>

struct ThresholdParams {
    bool active;
    int sensorDataType;
    float threshold;    
};

struct ThresholdParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* sensorDataTypeParam = nullptr;
    std::atomic<float>* thresholdParam = nullptr;
};