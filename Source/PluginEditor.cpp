/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
AudimoAudioProcessorEditor::AudimoAudioProcessorEditor (AudimoAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), m_effectsView (p), m_matrixView (p), m_advancedView (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 600);
    setResizable (true, false);

    addAndMakeVisible(m_navBar);
    addAndMakeVisible(m_effectsView);
    addAndMakeVisible(m_matrixView);
    addAndMakeVisible(m_advancedView);

    changeScreen(0);

    m_navBar.changeScreenFn = [this](const int id) { changeScreen(id); };
}

AudimoAudioProcessorEditor::~AudimoAudioProcessorEditor()
{
}

//==============================================================================
void AudimoAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (15.0f));
}

void AudimoAudioProcessorEditor::resized()
{
    auto bounds = getLocalBounds();
        
    // Navigation bar takes 10% of the top
    m_navBar.setBounds(bounds.removeFromTop(bounds.getHeight() * 0.1f));
    
    // Remaining area is for the screens (they all occupy the same space)
    m_effectsView.setBounds(bounds);
    m_matrixView.setBounds(bounds);
    m_advancedView.setBounds(bounds);
}

void AudimoAudioProcessorEditor::changeScreen(int screen_id)
{
    m_effectsView.setVisible(screen_id == 0);
    m_matrixView.setVisible(screen_id == 1);
    m_advancedView.setVisible(screen_id == 2);
}