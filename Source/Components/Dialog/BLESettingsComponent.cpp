#include "BLESettingsComponent.h"

#include <iostream>

BLESettingsComponent::BLESettingsComponent()
    : juce::DialogWindow("BLE Settings", juce::Colours::lightgrey, true)
{
    addAndMakeVisible(label);
    label.setFont(juce::Font(20.0f));
    
    setSize(400, 150);
    setResizable(true, true);
}

BLESettingsComponent::~BLESettingsComponent()
{
}

void BLESettingsComponent::resized()
{
    label.setBounds(10, 40, getWidth() - 20, 30);
}

void BLESettingsComponent::visibilityChanged()
{
    if (isVisible())
        label.setText("Scanning for Bluetooth Devices...", juce::dontSendNotification);
}

void BLESettingsComponent::setErrorMessage(const juce::String& msg)
{
    std::cout << "callback " << msg << std::endl;
    label.setText(msg, juce::dontSendNotification);
}

void BLESettingsComponent::closeButtonPressed()
{
    setVisible(false); // Hides the window when the close button is pressed
}
