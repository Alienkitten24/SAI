#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"


class FilterComponent : public EffectComponent
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& treeState);
    ~FilterComponent();

    void createParameterControls() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    KnobComponent mixKnob { "Mix", treeState, ParamIDs::Filter::Mix };
    KnobComponent cutoffKnob { "Cutoff", treeState, ParamIDs::Filter::Cutoff };
    KnobComponent resonanceKnob { "Resonance", treeState, ParamIDs::Filter::Resonance };
    KnobComponent driveKnob { "Drive", treeState, ParamIDs::Filter::Drive };

    ComboBoxComponent slopeTypeComboBox { treeState, ParamIDs::Filter::SlopeType };
    ComboBoxComponent passTypeComboBox { treeState, ParamIDs::Filter::PassType };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};