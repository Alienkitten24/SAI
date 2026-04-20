#pragma once

#include <JuceHeader.h>
#include "../../Model/EffectsTreeState.h"
#include "../Core/TitleBarComponent.h"
#include "../Core/KnobComponent.h"

class ParameterControllerComponent : public juce::Component
{
public:
    ParameterControllerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& activeParamID);
    virtual ~ParameterControllerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    virtual void createWidgets() = 0;
    virtual void layoutMainContent(juce::Rectangle<int> bounds) = 0;

protected:
    void setControllerName(const juce::String& name);

    juce::AudioProcessorValueTreeState& treeState;
    TitleBarComponent titleBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterControllerComponent)
};