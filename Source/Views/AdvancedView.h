#pragma once

#include <JuceHeader.h>

#include "../PluginProcessor.h"
#include "../Components/Dialog/BLESettingsComponent.h"

class AdvancedView : public juce::Component, public juce::Timer, public juce::ChangeListener
{
public:
    AdvancedView (AudimoAudioProcessor&);
    ~AdvancedView();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
private:
    AudimoAudioProcessor& audioProcessor;

    BLESettingsComponent bleSettingsComponent;
    juce::TextButton bleButton;
    std::array<juce::Label, 13> rawDataLabels;

    void timerCallback() override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdvancedView)
};