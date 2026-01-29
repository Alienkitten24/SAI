#pragma once

#include <JuceHeader.h>

struct SensorData {
    float time = 0.0f;
    int proximity = 0;
    juce::String gesture = "";
    float ax = 0.0f;
    float ay = 0.0f;
    float az = 0.0f;
    float gx = 0.0f;
    float gy = 0.0f;
    float gz = 0.0f;
    float ex = 0.0f;
    float ey = 0.0f;
    float ez = 0.0f;
    float mic_rms = 0.0f;
};
