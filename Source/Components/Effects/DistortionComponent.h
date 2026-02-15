#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../../Model/EffectsTreeState.h"

class DistortionComponent : public juce::Component
{
public:
    DistortionComponent (juce::AudioProcessorValueTreeState& state);
    ~DistortionComponent ();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void visibilityChanged() override;

private:
    // juce::LookAndFeel_V4 otherLookAndFeel; // [1]
    // dropdown type? soft hard etc
    // juce::ComboBox typeMenu;
    // juce::Slider driveKnob;
    // juce::Slider dryKnob or mixKnob;

    juce::Label nameLabel;
    
    juce::AudioProcessorValueTreeState& treeState;

    juce::ToggleButton activeButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> activeAttachment;

    juce::Slider driveKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;

    juce::Slider postGainKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postGainAttachment;

    juce::Slider mixKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};