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
    addAndMakeVisible(delayMsLKnob);
    addAndMakeVisible(delayMsRKnob);
    addAndMakeVisible(feedbackKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(typeComboBox);
}

void DelayComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 5;
    delayMsLKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    delayMsRKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    feedbackKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    mixKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    typeComboBox.setBounds(bounds.reduced(5));
}
