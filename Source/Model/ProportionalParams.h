#pragma once

#include <JuceHeader.h>
#include <atomic>

struct ProportionalParams {
    bool active;
    int sensorDataType;
    float minimum;    
    float maximum;
    float multiplier;
};

struct ProportionalParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* sensorDataTypeParam = nullptr;
    std::atomic<float>* minimumParam = nullptr;
    std::atomic<float>* maximumParam = nullptr;
    std::atomic<float>* multiplierParam = nullptr;
};