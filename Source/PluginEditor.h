/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "Components/Navigation/NavBar.h"
#include "Views/EffectsView.h"
#include "Views/MatrixView.h"
#include "Views/AdvancedView.h"

class AudimoAudioProcessorEditor  : public juce::AudioProcessorEditor 
{
public:
    AudimoAudioProcessorEditor (AudimoAudioProcessor&);
    ~AudimoAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudimoAudioProcessor& audioProcessor;

    NavBar m_navBar;
    EffectsView m_effectsView;
    MatrixView m_matrixView;
    AdvancedView m_advancedView;

    void changeScreen(int screen_id);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudimoAudioProcessorEditor)
};
