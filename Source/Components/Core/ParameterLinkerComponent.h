#pragma once

#include <JuceHeader.h>
#include "KnobComponent.h"
#include "EllipseComponent.h"

class ParameterLinkerComponent : public juce::Component
{
public:
    ParameterLinkerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& propertyName);
    ~ParameterLinkerComponent();

    void resized() override;

    void setTarget(KnobComponent* knob);
    KnobComponent* getTarget() const;

private:
    static constexpr int SIZE = 50;
    static constexpr int LABEL_HEIGHT = 25;

    KnobComponent* targetKnob = nullptr;

    // Components
    EllipseComponent ellipse;
    juce::Label label;
    
    juce::AudioProcessorValueTreeState& treeState;
    juce::String propertyName;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterLinkerComponent)
};