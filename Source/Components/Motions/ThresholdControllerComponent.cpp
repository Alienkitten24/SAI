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
}


void ThresholdControllerComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 2;
    sensorDataTypeComboBox.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    thresholdKnob.setBounds(bounds.reduced(5));
}