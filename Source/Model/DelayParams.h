#pragma once

#include <JuceHeader.h>
#include <atomic>

struct DelayParams {
    bool active;
    float delayMs;
    float feedback;
    float mix;
    // bool bpmSync;
};

struct DelayParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* delayMsParam = nullptr;
    std::atomic<float>* feedbackParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
};

enum DelayType {
    MONO = 0,
    STEREO = 1,
    PINGPONG = 2
};

// enum DelayLength {
//     WHOLE
//     HALF
//     QUARTER
//     EIGHTH
//     SIXTEENTH
//     DOTTED ?
// }
