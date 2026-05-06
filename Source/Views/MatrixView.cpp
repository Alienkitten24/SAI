#include "MatrixView.h"

// TODO implement everything
// idea is to list connections like "Parameter Controller -- Gain - Gain"
// might be obsolete due to labels within the controllers

MatrixView::MatrixView (AudimoAudioProcessor& p)
    : audioProcessor (p)
{   
    addAndMakeVisible(label);
    label.setText("No current connections", juce::dontSendNotification);
}

MatrixView::~MatrixView()
{
}

void MatrixView::paint(juce::Graphics& g)
{
    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (15.0f));
}

void MatrixView::resized()
{
    label.setBounds(10, 10, getWidth() - 20, 30);
}