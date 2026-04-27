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
    addAndMakeVisible(sensorDataTypeComboBox);
    addAndMakeVisible(minKnob);
    addAndMakeVisible(maxKnob);
    addAndMakeVisible(linker);
}


void ProportionalControllerComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 4;
    sensorDataTypeComboBox.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    minKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    maxKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    linker.setBounds(bounds.reduced(5));
}