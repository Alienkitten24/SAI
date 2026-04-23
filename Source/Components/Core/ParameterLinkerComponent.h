#pragma once

#include <JuceHeader.h>

class KnobComponent; // Forward declaration

class ParameterLinkerComponent : public juce::Component
{
public:
    ParameterLinkerComponent();
    ~ParameterLinkerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    void mouseDrag(const juce::MouseEvent& e) override;

    void setTarget(KnobComponent* knob);
    KnobComponent* getTarget() const;

private:
    static constexpr int SIZE = 30;
    static constexpr int STROKE_WIDTH = 2;

    KnobComponent* targetKnob = nullptr;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterLinkerComponent)
};