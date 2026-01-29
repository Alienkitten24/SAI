#include "Navbar.h"

NavBar::NavBar()
{
    // theoretically screen_ids should be an enum

    initButton(effectsViewButton, "Effects", 0);
    initButton(matrixViewButton, "Matrix", 1);
    initButton(advancedViewButton, "Advanced", 2);

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
    auto area = getLocalBounds();
    auto buttonWidth = area.getWidth() / 3; // 3 bc theres 3 buttons

    effectsViewButton.setBounds(area.removeFromLeft(buttonWidth));
    matrixViewButton.setBounds(area.removeFromLeft(buttonWidth));
    advancedViewButton.setBounds(area); // Take whatever is left
}