/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

#include "GUI/BLESettingsComponent.h"

//==============================================================================
/**
*/
struct sensorData {
  float time = 0.0f;
  int proximity = 0;
  juce::String gesture = "";
  float ax = 0.0f;
  float ay = 0.0f;
  float az = 0.0f;
  float gx = 0.0f;
  float gy = 0.0f;
  float gz = 0.0f;
  float ex = 0.0f;
  float ey = 0.0f;
  float ez = 0.0f;
  float mic_rms = 0.0f;
};

class TestAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer
{
public:
    TestAudioProcessorEditor (TestAudioProcessor&);
    ~TestAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TestAudioProcessor& audioProcessor;

    BLESettingsComponent bleSettingsComponent;
    juce::TextButton bleButton;

    sensorData data;
    std::array<juce::Label, 13> labels;
    // Protect access to 'data' between OSC thread and GUI thread
    juce::CriticalSection dataLock;
    void timerCallback() override;

    void onOSCBundleReceived(const juce::OSCBundle& bundle);
    void onOSCMessageReceived(const juce::OSCMessage& message);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessorEditor)
};
