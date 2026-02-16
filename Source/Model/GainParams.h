#pragma once

#include <JuceHeader.h>
#include <atomic>

struct GainParams {
    bool active;
    float gain;
};

struct GainParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* gainParam = nullptr;
};