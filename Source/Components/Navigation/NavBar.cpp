#include "Navbar.h"

NavBar::NavBar()
{
    initButton(effectsViewButton, "Effects", ScreenIDs::EFFECTS);
    initButton(matrixViewButton, "Matrix", ScreenIDs::MATRIX);
    initButton(advancedViewButton, "Advanced", ScreenIDs::ADVANCED);
}

NavBar::~NavBar()
{
}

void NavBar::initButton(juce::TextButton& btn, const juce::String name, int screen_id)
{
    btn.setButtonText(name);
    btn.setConnectedEdges(TextButton::ConnectedOnLeft | TextButton::ConnectedOnRight);
    addAndMakeVisible(btn);

    btn.setRadioGroupId(101);
    btn.setClickingTogglesState(true);

    // Make the button background transparent so we only see text
    btn.setColour(juce::TextButton::buttonColourId, juce::Colours::transparentBlack);
    btn.setColour(juce::TextButton::buttonOnColourId, juce::Colours::transparentBlack);

    btn.onClick = [this, screen_id] {if (changeScreenFn)    changeScreenFn(screen_id); repaint(); };
}

void NavBar::paint(juce::Graphics& g)
{
    // Draw a light gray base line for the whole bar (optional)
    g.setColour(juce::Colours::grey.withAlpha(0.3f));
    g.fillRect(0, getHeight() - 2, getWidth(), 2);

    // Find the active button and draw the highlight underline
    g.setColour(juce::Colours::orange);
    
    // TODO make this reactive and make it so effectsview is highlighted on startup
    if (effectsViewButton.getToggleState()) 
        g.fillRect(effectsViewButton.getBounds().removeFromBottom(3));
    else if (matrixViewButton.getToggleState()) 
        g.fillRect(matrixViewButton.getBounds().removeFromBottom(3));
    else if (advancedViewButton.getToggleState()) 
        g.fillRect(advancedViewButton.getBounds().removeFromBottom(3));
}

void NavBar::resized()
{
    // Consider: making this into a flexbox 
    auto bounds = getLocalBounds();
    auto buttonWidth = bounds.getWidth() / 3; 

    effectsViewButton.setBounds(bounds.removeFromLeft(buttonWidth));
    matrixViewButton.setBounds(bounds.removeFromLeft(buttonWidth));
    advancedViewButton.setBounds(bounds);
}