#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"

class GainComponent : public EffectComponent
{
public:
    GainComponent(juce::AudioProcessorValueTreeState& treeState);
    ~GainComponent();

    void createWidgets() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    KnobComponent gainKnob { "Gain", treeState, ParamIDs::Gain::Gain };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};