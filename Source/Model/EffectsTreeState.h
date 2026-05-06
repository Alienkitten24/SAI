#pragma once

#include <JuceHeader.h>


juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); 

namespace GroupIDs {
    inline constexpr auto Gain = "gain";
    inline constexpr auto Distortion = "dist";
    inline constexpr auto Delay = "delay";
    inline constexpr auto Filter = "filter";
    inline constexpr auto Proportional = "proportional";
    inline constexpr auto Threshold = "threshold";
};

namespace ParamIDs {
    namespace Gain {
        inline constexpr auto Active = "Gain - Active";
        inline constexpr auto Gain = "Gain - Gain";
    }
    namespace Distortion {
        inline constexpr auto Active = "Distortion - Active";
        inline constexpr auto Drive = "Distortion - Drive";
        inline constexpr auto PostGain = "Distortion - Post Gain";
        inline constexpr auto Mix = "Distortion - Mix";
        inline constexpr auto Type = "Distortion - Type";
    }
    namespace Delay {
        inline constexpr auto Active = "Delay - Active";
        inline constexpr auto Feedback = "Delay - Feedback";
        inline constexpr auto Mix = "Delay - Mix";
        inline constexpr auto DelayMsL = "Delay - Delay Ms L";
        inline constexpr auto DelayMsR = "Delay - Delay Ms R";
        inline constexpr auto DelayType = "Delay - Delay Type";
        // inline constexpr auto TempoType = "Delay - Tempo Type";
        // inline constexpr auto Division = "Delay - Division";
    }
    namespace Filter {
        inline constexpr auto Active = "Filter - Active";
        inline constexpr auto Mix = "Filter - Mix";
        inline constexpr auto Cutoff = "Filter - Cutoff";
        inline constexpr auto Resonance = "Filter - Resonance";
        inline constexpr auto Drive = "Filter - Drive"; 
        inline constexpr auto SlopeType = "Filter - Slope Type"; 
        inline constexpr auto PassType = "Filter - Pass Type"; 
        // inline constexpr auto FilterType = "Filter - Filter Type"; // ladder, svf, iir, fir
    }

    namespace Proportional {
        inline constexpr auto Active = "Proportional - Active";
        inline constexpr auto SensorDataType = "Proportional - Sensor Data Type";
        inline constexpr auto Minimum = "Proportional - Minimum";
        inline constexpr auto Maximum = "Proportional - Maximum";
        inline constexpr auto Multiplier = "Proportional - Multiplier";
    }
    namespace Threshold {
        inline constexpr auto Active = "Threshold - Active";
        inline constexpr auto SensorDataType = "Threshold - Sensor Data Type";
        inline constexpr auto Threshold = "Threshold - Threshold";
        inline constexpr auto Modifier = "Threshold - Modifier";
    }

    namespace Linker {
        inline constexpr auto Proportional = "Linker - Proportional";
        inline constexpr auto Threshold = "Linker - Threshold";
    }

    namespace Sensor {
        inline const juce::StringArray SensorDataStrings { 
            "Proximity", 
            "Acceleration X", "Acceleration Y", "Acceleration Z", 
            "Gyro X", "Gyro Y", "Gyro Z", 
            "Euler X", "Euler Y", "Euler Z", 
            "Microphone"
        };
    }
};


