#pragma once

#include <JuceHeader.h>
#include <atomic>

struct DelayParams {
    bool active;
    float feedback;
    float mix;
    float delayMsL;
    float delayMsR;
    int delayType; 
    int tempoType;
    int division;
};

struct DelayParamPointers {
    std::atomic<float>* activeParam = nullptr;
    std::atomic<float>* feedbackParam = nullptr;
    std::atomic<float>* mixParam = nullptr;
    std::atomic<float>* delayMsLParam = nullptr;
    std::atomic<float>* delayMsRParam = nullptr;
    std::atomic<float>* delayTypeParam = nullptr;
    std::atomic<float>* tempoTypeParam = nullptr;
    std::atomic<float>* divisionParam = nullptr;
};

enum DelayType {
    MONO,
    STEREO,
    PINGPONG
};

// enum TempoType {
//     MILLISECONDS,
//     STRAIGHT,
//     DOTTED,
//     TRIPLET
// }

// enum Division {
//     SIXTYFOURTH,
//     THIRTYSECOND,
//     SIXTEENTH,
//     EIGHTH,
//     QUARTER,
//     HALF,
//     WHOLE
//     // DOUBLEWHOLE
//     // QUADWHOLE
// }
