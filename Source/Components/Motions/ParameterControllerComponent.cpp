#include "ParameterControllerComponent.h"

ParameterControllerComponent::ParameterControllerComponent(juce::AudioProcessorValueTreeState& treeState, ParameterController& controller, const juce::String& activeParamID)
    : treeState(treeState), 
    controller(controller),
    titleBar(treeState, activeParamID)
{
    addAndMakeVisible(titleBar);
    addAndMakeVisible(minKnob);
    addAndMakeVisible(maxKnob);
}

ParameterControllerComponent::~ParameterControllerComponent()
{
}

void ParameterControllerComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Background
    g.setColour(juce::Colours::grey);
    g.fillRoundedRectangle(bounds, 8.0f);
}

void ParameterControllerComponent::resized()
{
    auto bounds = getLocalBounds();

    int titleBarHeight = 40;
    titleBar.setBounds(bounds.removeFromTop(titleBarHeight));

    int itemWidth = bounds.getWidth() / 2;
    minKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    maxKnob.setBounds(bounds.reduced(5));
}

 