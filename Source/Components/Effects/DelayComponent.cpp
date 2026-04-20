#include "DelayComponent.h"

DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& treeState)
    : EffectComponent(treeState, ParamIDs::Delay::Active)
{
    setEffectName("Delay");
    createWidgets();
}

DelayComponent::~DelayComponent()
{
}

void DelayComponent::createWidgets()
{
    addAndMakeVisible(delayMsLKnob);
    addAndMakeVisible(delayMsRKnob);
    addAndMakeVisible(feedbackKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(delayTypeComboBox);
    // addAndMakeVisible(tempoTypeComboBox);
}

void DelayComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 5;
    delayMsLKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    delayMsRKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    feedbackKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    mixKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    delayTypeComboBox.setBounds(bounds.reduced(5));
    // tempoTypeComboBox.setBounds(bounds.reduced(5));
}
