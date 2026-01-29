#include "EffectsView.h"

EffectsView::EffectsView (TestAudioProcessor& p)
    : audioProcessor (p), gainComponent (p.getTreeState())
{   
    // addAndMakeVisible(label);
    // label.setText("Effects view", juce::dontSendNotification);

    addAndMakeVisible(gainComponent);
}

EffectsView::~EffectsView()
{
}

void EffectsView::paint(juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (15.0f));
}

void EffectsView::resized()
{
    // label.setBounds(10, 10, getWidth() - 20, 30);
    gainComponent.setBounds(getLocalBounds().reduced(40));
}