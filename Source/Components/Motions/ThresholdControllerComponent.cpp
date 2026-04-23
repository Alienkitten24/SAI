#include "ThresholdControllerComponent.h"

ThresholdControllerComponent::ThresholdControllerComponent(juce::AudioProcessorValueTreeState& treeState)
    : ParameterControllerComponent(treeState, ParamIDs::Threshold::Active)
{
    setControllerName("Threshold Controller");
    createWidgets();
}

ThresholdControllerComponent::~ThresholdControllerComponent()
{
}

void ThresholdControllerComponent::createWidgets()
{
    addAndMakeVisible(sensorDataTypeComboBox);
    addAndMakeVisible(thresholdKnob);
    addAndMakeVisible(modifierKnob);
}


void ThresholdControllerComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 3;
    sensorDataTypeComboBox.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    thresholdKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    modifierKnob.setBounds(bounds.reduced(5));
}