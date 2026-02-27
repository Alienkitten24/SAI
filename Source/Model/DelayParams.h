#pragma once

#include <JuceHeader.h>
#include <atomic>

struct DelayParams {
    bool active;
    float delayMsL;
    float delayMsR;
    float feedback;
    float mix;
    int type; 
    // bool bpmSync;
};

struct DelayParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* delayMsLParam = nullptr;
    std::atomic<float>* delayMsRParam = nullptr;
    std::atomic<float>* feedbackParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
    std::atomic<float>* typeParam = nullptr;
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
