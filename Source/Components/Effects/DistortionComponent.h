#pragma once

#include <JuceHeader.h>

class DistortionComponent : public juce::Component
{
public:
    DistortionComponent ();
    ~DistortionComponent ();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::Label label;
    // juce::LookAndFeel_V4 otherLookAndFeel; // [1]
    // dropdown type? soft hard etc
    // juce::Slider driveKnob;
    // juce::Slider dryKnob or mixKnob;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};