#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../../Model/EffectsTreeState.h"
#include "../Core/TitleBarComponent.h"
#include "../Core/KnobComponent.h"
#include "../Core/ComboBoxComponent.h"

class EffectComponent : public juce::Component
{
public:
    EffectComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& activeParamID);
    virtual ~EffectComponent();

    void paint(juce::Graphics& g) override;
    void resized() override;

    virtual void createParameterControls() = 0;
    virtual void layoutMainContent(juce::Rectangle<int> bounds) = 0;


protected:
    void setEffectName(const juce::String& name);

    juce::AudioProcessorValueTreeState& treeState;
    TitleBarComponent titleBar;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectComponent)
};