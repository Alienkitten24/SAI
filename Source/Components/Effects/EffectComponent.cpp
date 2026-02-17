#include "EffectComponent.h"

EffectComponent::EffectComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& activeParamID)
    : treeState(treeState), 
      titleBar(treeState, activeParamID)
{
    addAndMakeVisible(titleBar);
}

EffectComponent::~EffectComponent()
{
}

void EffectComponent::setEffectName(const juce::String& name)
{
    titleBar.setTitle(name);
}

void EffectComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Background
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(bounds, 8.0f);
}

void EffectComponent::resized()
{
    auto bounds = getLocalBounds();

    // Title bar on top
    int titleBarHeight = 40;
    titleBar.setBounds(bounds.removeFromTop(titleBarHeight));

    // Remaining space for content
    layoutMainContent(bounds);
}
 