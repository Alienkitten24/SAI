#include "EffectsTreeState.h"

// EffectsTreeState::EffectsTreeState()
// {
// }

// EffectsTreeState::~EffectsTreeState()
// {
// }

namespace EffectsTreeState {
    juce::AudioProcessorValueTreeState::ParameterLayout EffectsTreeState::createParameterLayout()
    {
        std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;


        // TODO figure out a good Db range (maybe use normalizablerange<> ?)
        params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "gain", "Gain", -60.0f, 0.0f, -6.0f
        ));

        return { params.begin(), params.end() };
    }
}
