#pragma once

#include <JuceHeader.h>

class KnobComponent; // Forward declaration

class ParameterLinkerComponent : public juce::Component
{
public:
    ParameterLinkerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& propertyName);
    ~ParameterLinkerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& e) override;
    void mouseDrag(const juce::MouseEvent& e) override;
    void mouseUp(const juce::MouseEvent& e) override;

    void setTarget(KnobComponent* knob);
    KnobComponent* getTarget() const;

private:
    static constexpr int SIZE = 50;

    bool isDragging = false;
    KnobComponent* targetKnob = nullptr;

    // for displaying the linked param name
    juce::Label label;
    juce::AudioProcessorValueTreeState& treeState;
    juce::String propertyName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterLinkerComponent)
};