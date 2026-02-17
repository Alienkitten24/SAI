#pragma once

#include <JuceHeader.h>

class KnobComponent : public juce::Component
{
public:
    KnobComponent(
        const juce::String& text,
        juce::AudioProcessorValueTreeState& treeState,
        const juce::String& paramID
    );
    ~KnobComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label label;
    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobComponent)
};