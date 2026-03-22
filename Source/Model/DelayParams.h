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
    MONO = 0,
    STEREO = 1,
    PINGPONG = 2
};

// enum TempoType {
//     MILLISECONDS = 0,
//     STRAIGHT = 1,
//     DOTTED = 2,
//     TRIPLET = 3
// }

// enum Division {
//     SIXTYFOURTH = 0,
//     THIRTYSECOND = 1,
//     SIXTEENTH = 2,
//     EIGHTH = 3,
//     QUARTER = 4,
//     HALF = 5,
//     WHOLE = 6
//     // DOUBLEWHOLE
//     // QUADWHOLE
// }
