#include "DistortionComponent.h"

#include <iostream>

DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& state)
    : EffectComponent(state)
{
    setEffectName("Distortion");
    createParameterControls();
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::createParameterControls()
{
    driveKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    driveKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    driveKnob.setRange(0.0, 100.0, 0.1);
    addAndMakeVisible(driveKnob);
    
    postGainKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    postGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    postGainKnob.setRange(0.0, 100.0, 0.1);
    addAndMakeVisible(postGainKnob);

    mixKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    mixKnob.setRange(0.0, 100.0, 0.1);
    addAndMakeVisible(mixKnob);

    linkAttachments();
}

void DistortionComponent::linkAttachments()
{
    if (!activeAttachment) 
    {
        activeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            treeState, ParamIDs::Distortion::Active, activeButton
        );
    }
    if (!driveAttachment)
    {
        driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, ParamIDs::Distortion::Drive, driveKnob
        );
    }
    if (!postGainAttachment)
    {
        postGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, ParamIDs::Distortion::PostGain, postGainKnob
        );
    }
    if (!mixAttachment)
    {
        mixAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, ParamIDs::Distortion::Mix, mixKnob
        );
    }
}

void DistortionComponent::layoutMainContent()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(TITLE_BAR_HEIGHT);

    // Layout for three knobs in the main content area
    int knobWidth = bounds.getWidth() / 3;
    driveKnob.setBounds(bounds.removeFromLeft(knobWidth).reduced(5));
    postGainKnob.setBounds(bounds.removeFromLeft(knobWidth).reduced(5));
    mixKnob.setBounds(bounds.reduced(5));
}
