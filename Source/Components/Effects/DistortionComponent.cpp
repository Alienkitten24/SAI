#include "DistortionComponent.h"

#include <iostream>

DistortionComponent::DistortionComponent()
{
    addAndMakeVisible(label);
    label.setFont(juce::Font(20.0f));
}

DistortionComponent::~DistortionComponent()
{
}

void DistortionComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font (15.0f));
    g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

}

void DistortionComponent::resized()
{
    label.setBounds(10, 10, getWidth() - 20, 30);
}