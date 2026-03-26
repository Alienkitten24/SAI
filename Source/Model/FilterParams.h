#pragma once

#include <JuceHeader.h>
#include <atomic>

struct FilterParams {
    bool active;
    float mix;
    float cutoff;
    float resonance;
    float drive;
    int slopeType;
    int passType;
};

struct FilterParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
    std::atomic<float>* cutoffParam = nullptr;
    std::atomic<float>* resonanceParam = nullptr;
    std::atomic<float>* driveParam = nullptr;
    std::atomic<float>* slopeTypeParam = nullptr;
    std::atomic<float>* passTypeParam = nullptr;
};

enum SlopeType {
    DB12 = 0,
    DB24 = 1
};

enum PassType {
    LOWPASS = 0,
    HIGHPASS = 1,
    BANDPASS = 2
};