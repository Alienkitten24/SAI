#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

class BLESettingsComponent : public juce::Component
{
public:
    BLESettingsComponent();
    ~BLESettingsComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void visibilityChanged() override;
    void setErrorMessage(const juce::String& msg);

private:
    juce::Label label;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BLESettingsComponent)
};