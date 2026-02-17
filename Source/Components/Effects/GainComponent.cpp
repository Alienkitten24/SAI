#include "GainComponent.h"

GainComponent::GainComponent(juce::AudioProcessorValueTreeState& treeState)
    : EffectComponent(treeState, ParamIDs::Gain::Active)
{
    setEffectName("Gain");
    createParameterControls();
}

GainComponent::~GainComponent()
{
}

void GainComponent::createParameterControls()
{
    addAndMakeVisible(gainKnob);
}


void GainComponent::layoutMainContent(juce::Rectangle<int> bounds)
{
    gainKnob.setBounds(bounds.reduced(5));
}