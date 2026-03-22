#pragma once

#include <JuceHeader.h>
#include <atomic>

struct DistortionParams {
    bool active;
    float drive;
    float postGain;
    float mix;
    int type; 


    // float asymmetry;
    // int oversamplingFactor;
};

struct DistortionParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* driveParam = nullptr;
    std::atomic<float>* postGainParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
    std::atomic<float>* typeParam = nullptr;
};

enum DistortionType {
    SOFTCLIP = 0,
    HARDCLIP = 1,
    BITCRUSH = 2
};
