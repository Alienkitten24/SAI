#pragma once

#include <JuceHeader.h>
#include <memory>

class EffectComponent : public juce::Component
{
public:
    EffectComponent(juce::AudioProcessorValueTreeState& state);
    virtual ~EffectComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    virtual void createParameterControls() = 0;
    virtual void linkAttachments() = 0;
    virtual void layoutMainContent() = 0;

    void setEffectName(const juce::String& name);

protected:
    static constexpr int TITLE_BAR_HEIGHT = 40;

    juce::AudioProcessorValueTreeState& treeState;

    juce::String effectName;
    juce::Label nameLabel;

    juce::ToggleButton activeButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> activeAttachment;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectComponent)
};