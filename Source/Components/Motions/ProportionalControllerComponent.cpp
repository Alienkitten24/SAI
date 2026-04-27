#include "ProportionalControllerComponent.h"

ProportionalControllerComponent::ProportionalControllerComponent(juce::AudioProcessorValueTreeState& treeState)
    : ParameterControllerComponent(treeState, ParamIDs::Proportional::Active)
{
    setControllerName("Proportional Controller");
    createWidgets();
}

ProportionalControllerComponent::~ProportionalControllerComponent()
{
}

void ProportionalControllerComponent::createWidgets()
{
    addAndMakeVisible(linker);
    addAndMakeVisible(sensorDataTypeComboBox);
    addAndMakeVisible(minKnob);
    addAndMakeVisible(maxKnob);
}


void ProportionalControllerComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 4;
    linker.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    sensorDataTypeComboBox.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    minKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    maxKnob.setBounds(bounds.reduced(5));
}