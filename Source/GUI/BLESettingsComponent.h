#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

class BLESettingsComponent : public juce::Component, public juce::ChangeListener
{
public:
    BLESettingsComponent (TestAudioProcessor&);
    ~BLESettingsComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void visibilityChanged() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

private:
    TestAudioProcessor& audioProcessor;
    juce::Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BLESettingsComponent)
};