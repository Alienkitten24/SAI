#pragma once

#include <JuceHeader.h>
#include "ParameterControllerComponent.h"
#include "../Core/KnobComponent.h"
#include "../Core/ComboBoxComponent.h"

class ThresholdControllerComponent : public ParameterControllerComponent
{
public: 
    ThresholdControllerComponent(juce::AudioProcessorValueTreeState& treeState);
    ~ThresholdControllerComponent();

    void createWidgets() override;
    void layoutMainContent(juce::Rectangle<int> bounds) override;

private:
    ComboBoxComponent sensorDataTypeComboBox { treeState, ParamIDs::Threshold::SensorDataType };
    KnobComponent thresholdKnob { "Threshold", treeState, ParamIDs::Threshold::Threshold };
    KnobComponent modifierKnob { "Modifier", treeState, ParamIDs::Threshold::Modifier };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThresholdControllerComponent)
};