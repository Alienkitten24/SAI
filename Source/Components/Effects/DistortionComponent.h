#pragma once

#include <JuceHeader.h>
#include <memory>
#include "EffectComponent.h"
#include "../../Model/EffectsTreeState.h"

class DistortionComponent : public EffectComponent
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& state);
    ~DistortionComponent();

    void createParameterControls() override;
    void layoutMainContent() override;

private:
    void linkAttachments();

    juce::Slider driveKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;

    juce::Slider postGainKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> postGainAttachment;

    juce::Slider mixKnob;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixAttachment;

    juce::ComboBox typeComboBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> typeAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};