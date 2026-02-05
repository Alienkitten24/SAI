#pragma once

#include <JuceHeader.h>

// TODO rename this class
// class EffectsTreeState {
// public:
//     EffectsTreeState();
//     ~EffectsTreeState();

//    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); 

// private:
//     // on/off state ?
    
//     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsTreeState)
// }

namespace EffectsTreeState
{
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout(); 

    // maybe should be paramId ?
    namespace paramNames {
        inline const juce::String Gain { "gain" };
    };
};
