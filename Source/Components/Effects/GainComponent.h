#pragma once

#include <JuceHeader.h>
#include <memory>

class GainComponent : public juce::Component
{
public:
    GainComponent (juce::AudioProcessorValueTreeState& state);
    ~GainComponent ();

    void paint(juce::Graphics& g) override;
    void resized() override;
    void visibilityChanged() override;

private:
    juce::AudioProcessorValueTreeState& treeState;

    juce::Slider gainKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainComponent)
};