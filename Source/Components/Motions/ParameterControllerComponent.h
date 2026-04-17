#pragma once

#include <JuceHeader.h>
#include "../../Model/EffectsTreeState.h"
#include "../Core/TitleBarComponent.h"
#include "../Core/KnobComponent.h"
#include "../../Controllers/ParameterController.h"

class ParameterControllerComponent : public juce::Component
{
public:
    ParameterControllerComponent(juce::AudioProcessorValueTreeState& treeState, ParameterController& controller, const juce::String& activeParamID);
    ~ParameterControllerComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

protected:
    juce::AudioProcessorValueTreeState& treeState;
    TitleBarComponent titleBar;
    ParameterController& controller;  // Reference to the logic layer

private:
    KnobComponent minKnob { "Minimum", treeState, ParamIDs::Controller::Minimum };
    KnobComponent maxKnob { "Maximum", treeState, ParamIDs::Controller::Maximum };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterControllerComponent)
};