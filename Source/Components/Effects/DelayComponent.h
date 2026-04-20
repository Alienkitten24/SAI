#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"


class DelayComponent : public EffectComponent
{
public:
    DelayComponent(juce::AudioProcessorValueTreeState& treeState);
    ~DelayComponent();

    void createWidgets() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    KnobComponent delayMsLKnob { "Delay L", treeState, ParamIDs::Delay::DelayMsL }; 
    KnobComponent delayMsRKnob { "Delay R", treeState, ParamIDs::Delay::DelayMsR };

    KnobComponent feedbackKnob { "Feedback", treeState, ParamIDs::Delay::Feedback };
    KnobComponent mixKnob { "Mix", treeState, ParamIDs::Delay::Mix };

    ComboBoxComponent delayTypeComboBox { treeState, ParamIDs::Delay::DelayType };
    // ComboBoxComponent tempoTypeComboBox { treeState, ParamIDs::Delay::TempoType };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};