#include "ParameterControllerComponent.h"

ParameterControllerComponent::ParameterControllerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& activeParamID)
    : treeState(treeState), 
    titleBar(treeState, activeParamID)
{
    addAndMakeVisible(titleBar);
}

ParameterControllerComponent::~ParameterControllerComponent()
{
}

void ParameterControllerComponent::setControllerName(const juce::String& name)
{
    titleBar.setTitle(name);
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

    layoutMainContent(bounds);
}

 