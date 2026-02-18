#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"


class DelayComponent : public EffectComponent
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& treeState);
    ~DelayComponent();

    void createParameterControls() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:

    KnobComponent delayMsKnob { "Delay Ms", treeState, ParamIDs::Delay::DelayMs };
    KnobComponent feedbackKnob { "Feedback", treeState, ParamIDs::Delay::Feedback };
    KnobComponent mixKnob { "Mix", treeState, ParamIDs::Delay::Mix };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};