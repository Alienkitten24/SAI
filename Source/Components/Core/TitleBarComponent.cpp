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
    // TODO spacing needs to be fixed
    auto bounds = getLocalBounds();
    
    // Active button on the left
    activeButton.setBounds(bounds.removeFromLeft(50).reduced(4));
    
    // Name label centered in remaining title bar space
    label.setBounds(bounds);
    label.setJustificationType(juce::Justification::centred);
}