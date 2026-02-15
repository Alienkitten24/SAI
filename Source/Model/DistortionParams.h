#pragma once

#include <JuceHeader.h>

struct DistortionParams {
    bool active;
    float drive;
    float postGain;
    float mix;


    // float asymmetry;
    // int oversamplingFactor;
    // int waveshaperMode;
};
