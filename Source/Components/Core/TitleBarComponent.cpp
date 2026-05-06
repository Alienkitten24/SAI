#include "TitleBarComponent.h"

TitleBarComponent::TitleBarComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& activeParamID)
{
    addAndMakeVisible(label);
    addAndMakeVisible(activeButton);
    
    activeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
        treeState, activeParamID, activeButton
    );
}

TitleBarComponent::~TitleBarComponent()
{
}

void TitleBarComponent::setTitle(const juce::String& text)
{
    label.setText(text, juce::dontSendNotification);
}

void TitleBarComponent::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::black);
    g.fillRect(getLocalBounds());
}

void TitleBarComponent::resized()
{
    auto bounds = getLocalBounds();
    
    activeButton.setBounds(bounds.removeFromLeft(50).reduced(5));
    
    // TODO probably should remove the hardcoded numbers
    auto labelWidth = 200;
    auto labelHeight = 40;
    label.setBounds(
        (getWidth() - labelWidth) / 2,   // x position
        (getHeight() - labelHeight) / 2, // y position
        labelWidth,
        labelHeight
    );
    label.setJustificationType(juce::Justification::centred);
}