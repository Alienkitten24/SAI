#include "FilterComponent.h"


FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& treeState)
    : EffectComponent(treeState, ParamIDs::Filter::Active)
{
    setEffectName("Filter");
    createWidgets();
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::createWidgets()
{
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(cutoffKnob);
    addAndMakeVisible(resonanceKnob);
    addAndMakeVisible(driveKnob);
    addAndMakeVisible(slopeTypeComboBox);
    addAndMakeVisible(passTypeComboBox);
}

void FilterComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 6;
    mixKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    cutoffKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    resonanceKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    driveKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    slopeTypeComboBox.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    passTypeComboBox.setBounds(bounds.reduced(5));
}

