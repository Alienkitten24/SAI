#include "DistortionComponent.h"

#include <iostream>

DistortionComponent::DistortionComponent(juce::AudioProcessorValueTreeState& state)
    : treeState (state)
{
    nameLabel.setText("Distortion", juce::dontSendNotification);
    addAndMakeVisible(nameLabel);

    // activeButton.setButtonText("Active");
    addAndMakeVisible(activeButton);

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
}
void DistortionComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);
}

void DistortionComponent::resized()
{
    auto bounds = getLocalBounds();
    // Define the height for the top row (button + label)
    int topRowHeight = juce::jmin(40, bounds.getHeight() / 4); // Thin row, max 1/4 of height or 40px
    auto topRow = bounds.removeFromTop(topRowHeight);
    auto bottomRow = bounds;

    // Layout for top row: button on left, label on right
    int buttonWidth = 60;
    // bro is ai stupid it made this var just to not use it 
    int labelWidth = topRow.getWidth() - buttonWidth;
    activeButton.setBounds(topRow.removeFromLeft(buttonWidth).reduced(5));
    nameLabel.setBounds(topRow.reduced(5));

    // Layout for bottom row: three knobs
    int knobWidth = bottomRow.getWidth() / 3;
    driveKnob.setBounds(bottomRow.removeFromLeft(knobWidth).reduced(5));
    postGainKnob.setBounds(bottomRow.removeFromLeft(knobWidth).reduced(5));
    mixKnob.setBounds(bottomRow.reduced(5));
}