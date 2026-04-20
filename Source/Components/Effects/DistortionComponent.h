#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"


class DistortionComponent : public EffectComponent
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& treeState);
    ~DistortionComponent();

    void createWidgets() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    KnobComponent driveKnob { "Drive", treeState, ParamIDs::Distortion::Drive };
    KnobComponent postGainKnob { "Post Gain", treeState, ParamIDs::Distortion::PostGain };
    KnobComponent mixKnob { "Mix", treeState, ParamIDs::Distortion::Mix };

    ComboBoxComponent typeComboBox { treeState, ParamIDs::Distortion::Type };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};