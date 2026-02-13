#include "EffectsView.h"

EffectsView::EffectsView (TestAudioProcessor& p)
    : audioProcessor (p), 
    gainComponent (p.getTreeState()),
    distortionComponent (p.getTreeState())
{   
    // addAndMakeVisible(label);
    // label.setText("Effects view", juce::dontSendNotification);

    addAndMakeVisible(gainComponent);
    addAndMakeVisible(distortionComponent);
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
    int componentHeight = getHeight() / 2;
    gainComponent.setBounds(10, 10, getWidth() - 20, componentHeight - 20);
    distortionComponent.setBounds(10, componentHeight + 10, getWidth() - 20, componentHeight - 20);
}