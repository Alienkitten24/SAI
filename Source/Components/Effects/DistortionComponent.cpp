#include "DistortionComponent.h"

#include <iostream>

DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& treeState)
    : EffectComponent(treeState, ParamIDs::Distortion::Active)
{
    setEffectName("Distortion");
    createParameterControls();
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::createParameterControls()
{
    addAndMakeVisible(driveKnob);
    addAndMakeVisible(postGainKnob);
    addAndMakeVisible(mixKnob);
    addAndMakeVisible(typeComboBox);
}

void DistortionComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    int itemWidth = bounds.getWidth() / 4;
    driveKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    postGainKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    mixKnob.setBounds(bounds.removeFromLeft(itemWidth).reduced(5));
    typeComboBox.setBounds(bounds.reduced(5));
}
