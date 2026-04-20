#pragma once

#include <JuceHeader.h>
#include "ParameterControllerComponent.h"
#include "../Core/KnobComponent.h"
#include "../Core/ComboBoxComponent.h"

class ProportionalControllerComponent : public ParameterControllerComponent
{
public: 
    ProportionalControllerComponent(juce::AudioProcessorValueTreeState& treeState);
    ~ProportionalControllerComponent();

    void createWidgets() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    ComboBoxComponent sensorDataTypeComboBox { treeState, ParamIDs::Proportional::SensorDataType };
    KnobComponent minKnob { "Minimum", treeState, ParamIDs::Proportional::Minimum };
    KnobComponent maxKnob { "Maximum", treeState, ParamIDs::Proportional::Maximum };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProportionalControllerComponent)
};