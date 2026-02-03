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

        params.push_back(std::make_unique<juce::AudioParameterFloat>(
            "gain", "Gain", 0.0f, 1.0f, 0.5f
        ));

        return { params.begin(), params.end() };
    }
}
