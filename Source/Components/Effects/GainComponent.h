#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../../Model/EffectsTreeState.h"
#include "EffectComponent.h"

class GainComponent : public EffectComponent
{
public:
    GainComponent (juce::AudioProcessorValueTreeState& state);
    ~GainComponent ();

    void createParameterControls() override;
    void layoutMainContent() override;
    void linkAttachments() override;

private:

    juce::Slider gainKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};