#pragma once

#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class BLESettingsComponent : public juce::DialogWindow
{
public:
    BLESettingsComponent();
    ~BLESettingsComponent();

    void resized() override;
    void visibilityChanged() override;
    void setErrorMessage(const juce::String& msg);

private:
    juce::Label label;

    void closeButtonPressed() override; // Override closeButtonPressed to handle close button action

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BLESettingsComponent)
};