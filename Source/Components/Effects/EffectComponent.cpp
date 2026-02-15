#include "EffectComponent.h"

EffectComponent::EffectComponent(juce::AudioProcessorValueTreeState& state)
    : treeState (state)
{
    addAndMakeVisible(nameLabel);
    addAndMakeVisible(activeButton);
}

EffectComponent::~EffectComponent()
{
}

void EffectComponent::setEffectName(const juce::String& name)
{
    effectName = name;
    nameLabel.setText(name, juce::dontSendNotification);
}

void EffectComponent::paint(juce::Graphics& g)
{
    // TODO need to make this look prettier

    auto bounds = getLocalBounds().toFloat();

    // Background
    g.setColour(juce::Colours::darkgrey);
    g.fillRoundedRectangle(bounds, 8.0f);

    // Title bar
    g.setColour(juce::Colours::black);
    g.fillRect(0, 0, getWidth(), TITLE_BAR_HEIGHT);
}

void EffectComponent::resized()
{
    // TODO need to make this look prettier

    auto bounds = getLocalBounds();

    // Title bar layout
    auto titleBar = bounds.removeFromTop(TITLE_BAR_HEIGHT);
    
    // Active button on the left
    activeButton.setBounds(titleBar.removeFromLeft(50).reduced(4));
    
    // Name label centered in remaining title bar space
    nameLabel.setBounds(titleBar);
    nameLabel.setJustificationType(juce::Justification::centred);

    // Remaining space for content
    layoutMainContent();
}
 