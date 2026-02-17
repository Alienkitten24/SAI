#pragma once

#include <JuceHeader.h>

class TitleBarComponent : public juce::Component
{
public:
    TitleBarComponent(
        juce::AudioProcessorValueTreeState& treeState,
        const juce::String& activeParamID
    );
    ~TitleBarComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;
    
    void setTitle(const juce::String& text);

private: 
    juce::Label label;

    juce::ToggleButton activeButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> activeAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TitleBarComponent)
};