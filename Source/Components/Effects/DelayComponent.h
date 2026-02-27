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

    KnobComponent delayMsLKnob { "Delay Ms L", treeState, ParamIDs::Delay::DelayMsL };
    KnobComponent delayMsRKnob { "Delay Ms R", treeState, ParamIDs::Delay::DelayMsR };
    KnobComponent feedbackKnob { "Feedback", treeState, ParamIDs::Delay::Feedback };
    KnobComponent mixKnob { "Mix", treeState, ParamIDs::Delay::Mix };

    ComboBoxComponent typeComboBox { treeState, ParamIDs::Delay::Type };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};