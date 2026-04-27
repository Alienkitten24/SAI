#pragma once

#include <JuceHeader.h>

class KnobComponent : public juce::Component,
                      public juce::DragAndDropTarget
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

    bool isInterestedInDragSource(const SourceDetails& details) override;
    void itemDropped(const SourceDetails& details) override;

    juce::String getParamID() const;

private:
    juce::Label label;
    juce::Slider slider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attachment;
    juce::RangedAudioParameter* parameter = nullptr;

    juce::String paramID;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobComponent)
};