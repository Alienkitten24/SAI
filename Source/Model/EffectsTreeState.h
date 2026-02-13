#pragma once

#include <JuceHeader.h>


juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); 

namespace GroupIDs {
    // inline const juce::String Gain { "gain" };
    inline constexpr auto Gain = "gain";
    inline constexpr auto Distortion = "dist";
};

namespace ParamIDs {
    namespace Gain {
        inline constexpr auto Gain = "gain_gain";
    };
    namespace Distortion {
        inline constexpr auto Drive = "dist_drive";
        inline constexpr auto PostGain = "dist_postGain";
        inline constexpr auto Mix = "dist_Mix";
    };
};


