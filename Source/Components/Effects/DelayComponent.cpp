#include "DelayComponent.h"

#include <iostream>

DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& treeState)
    : EffectComponent(treeState, ParamIDs::Delay::Active)
{
    setEffectName("Delay");
    createParameterControls();
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::createParameterControls()
{
    addAndMakeVisible(delayMsKnob);
    addAndMakeVisible(feedbackKnob);
    addAndMakeVisible(mixKnob);
}

void DelayComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 3;
    delayMsKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    feedbackKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    mixKnob.setBounds(bounds.reduced(5));
}
