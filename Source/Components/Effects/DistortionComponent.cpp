#include "DistortionComponent.h"

#include <iostream>

DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& state)
    : treeState (state)
{
    driveKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary); // Changed to Rotary style
    driveKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    driveKnob.setRange(0.0, 100.0, 0.1); // Set range from 0 to 100
    addAndMakeVisible(driveKnob);
    
    postGainKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    postGainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    postGainKnob.setRange(0.0, 100.0, 0.1);
    addAndMakeVisible(postGainKnob);

    // Mix Knob
    mixKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    mixKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    mixKnob.setRange(0.0, 100.0, 0.1);
    addAndMakeVisible(mixKnob);
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::visibilityChanged()
{
    if (isVisible())
    {
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
}
void DistortionComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);
}

void DistortionComponent::resized()
{
    auto bounds = getLocalBounds();
    auto knobWidth = bounds.getWidth() / 3;

    driveKnob.setBounds(bounds.removeFromLeft(knobWidth));
    postGainKnob.setBounds(bounds.removeFromLeft(knobWidth));
    mixKnob.setBounds(bounds);
}