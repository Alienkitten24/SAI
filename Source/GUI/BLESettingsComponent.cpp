#include "BLESettingsComponent.h"

#include <iostream>

BLESettingsComponent::BLESettingsComponent(TestAudioProcessor& p)
    : audioProcessor(p)
{
    addAndMakeVisible(label);
    label.setFont(juce::Font(20.0f));
}

BLESettingsComponent::~BLESettingsComponent()
{
}

void BLESettingsComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::green);

    g.setColour(juce::Colours::white);
    g.setFont(juce::Font (15.0f));
    // g.drawFittedText("Hello World!", getLocalBounds(), juce::Justification::centred, 1);

}

void BLESettingsComponent::resized()
{
    label.setBounds(10, 10, getWidth() - 20, 30);
}

void BLESettingsComponent::visibilityChanged()
{
    if (isVisible())
        label.setText("Scanning for Bluetooth Devices...", juce::dontSendNotification);
}


void BLESettingsComponent::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    juce::String msg = audioProcessor.getBLEManager().getLastErrorMessage();
    std::cout << "callback " << msg << std::endl;
    label.setText(msg, juce::dontSendNotification);
    repaint();
}