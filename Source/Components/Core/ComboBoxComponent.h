#pragma once

#include <JuceHeader.h>

class ComboBoxComponent : public juce::Component
{
public:
    ComboBoxComponent(
        juce::AudioProcessorValueTreeState& treeState,
        const juce::String& paramID
    );
    ~ComboBoxComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::ComboBox comboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComboBoxComponent)
};