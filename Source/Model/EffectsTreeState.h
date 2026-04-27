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
        inline constexpr auto Active = "gain_active";
        inline constexpr auto Gain = "gain_gain";
    };
    namespace Distortion {
        inline constexpr auto Active = "dist_active";
        inline constexpr auto Drive = "dist_drive";
        inline constexpr auto PostGain = "dist_postGain";
        inline constexpr auto Mix = "dist_mix";
        inline constexpr auto Type = "dist_type";
    };
    namespace Delay {
        inline constexpr auto Active = "delay_active";
        inline constexpr auto Feedback = "delay_feedback";
        inline constexpr auto Mix = "delay_mix";
        inline constexpr auto DelayMsL = "delay_delayMsL";
        inline constexpr auto DelayMsR = "delay_delayMsR";
        inline constexpr auto DelayType = "delay_delayType";
        // inline constexpr auto TempoType = "delay_tempoType";
        // inline constexpr auto Division = "delay_division";
    };
    namespace Filter {
        inline constexpr auto Active = "filter_active";
        inline constexpr auto Mix = "filter_mix";
        inline constexpr auto Cutoff = "filter_cutoff";
        inline constexpr auto Resonance = "filter_resonance";
        inline constexpr auto Drive = "filter_drive"; 
        inline constexpr auto SlopeType = "filter_slopeType"; 
        inline constexpr auto PassType = "filter_passType"; 
        // inline constexpr auto FilterType = "filter_filterType"; // ladder, svf, iir, fir
    }

    namespace Proportional {
        inline constexpr auto Active = "proportional_active";
        inline constexpr auto SensorDataType = "proportional_sensorDataType";
        inline constexpr auto Minimum = "proportional_minimum";
        inline constexpr auto Maximum = "proportional_maximum";
        inline constexpr auto Multiplier = "proportional_multiplier";
    }
    namespace Threshold {
        inline constexpr auto Active = "threshold_active";
        inline constexpr auto SensorDataType = "threshold_sensorDataType";
        inline constexpr auto Threshold = "threshold_threshold";
        inline constexpr auto Modifier = "threshold_modifier";
    }

    namespace Linker {
        inline constexpr auto Proportional = "linker_proportional";
        inline constexpr auto Threshold = "linker_threshold";
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


