#include "EffectsView.h"

EffectsView::EffectsView (TestAudioProcessor& p)
    : audioProcessor    (p), 
    gainComponent       (p.getTreeState()),
    distortionComponent (p.getTreeState()),
    delayComponent      (p.getTreeState()),
    filterComponent     (p.getTreeState())
{   
    // addAndMakeVisible(label);
    // label.setText("Effects view", juce::dontSendNotification);

    addAndMakeVisible(gainComponent);
    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(delayComponent);
    addAndMakeVisible(filterComponent);
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
    auto bounds = getLocalBounds();
    auto componentHeight = bounds.getHeight() / 4;

    gainComponent.setBounds(bounds.removeFromTop(componentHeight));
    distortionComponent.setBounds(bounds.removeFromTop(componentHeight));
    delayComponent.setBounds(bounds.removeFromTop(componentHeight));
    filterComponent.setBounds(bounds);
}