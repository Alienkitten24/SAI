#include "EffectsView.h"

EffectsView::EffectsView (TestAudioProcessor& p)
    : audioProcessor    (p), 
    gainComponent       (p.getTreeState()),
    distortionComponent (p.getTreeState()),
    delayComponent      (p.getTreeState()),
    filterComponent     (p.getTreeState()),
    parameterControllerComponent (p.getTreeState(), p.getParameterController(), ParamIDs::Controller::Active)
{   
    // addAndMakeVisible(label);
    // label.setText("Effects view", juce::dontSendNotification);

    addAndMakeVisible(gainComponent);
    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(delayComponent);
    addAndMakeVisible(filterComponent);
    addAndMakeVisible(parameterControllerComponent);
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
    
    auto columnWidth = bounds.getWidth() / 2;
    auto leftColumn = bounds.removeFromLeft(columnWidth);
    auto rightColumn = bounds;
    
    auto leftRowHeight = leftColumn.getHeight() / 4;
    
    gainComponent.setBounds(leftColumn.removeFromTop(leftRowHeight));
    distortionComponent.setBounds(leftColumn.removeFromTop(leftRowHeight));
    delayComponent.setBounds(leftColumn.removeFromTop(leftRowHeight));
    filterComponent.setBounds(leftColumn); 
    
    parameterControllerComponent.setBounds(rightColumn.removeFromTop(leftRowHeight));
}