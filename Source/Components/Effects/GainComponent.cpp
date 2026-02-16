#include "GainComponent.h"

GainComponent::GainComponent(juce::AudioProcessorValueTreeState& state)
    : EffectComponent(state)
{
    setEffectName("Gain");
    createParameterControls();
}

GainComponent::~GainComponent()
{
}

void GainComponent::createParameterControls()
{
    gainKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary); // Changed to Rotary style
    gainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainKnob.setRange(0.0, 100.0, 0.1); // Set range from 0 to 100
    addAndMakeVisible(gainKnob);
    
    linkAttachments();
}

void GainComponent::linkAttachments()
{
    if (!activeAttachment) 
    {
        activeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(
            treeState, ParamIDs::Gain::Active, activeButton
        );
    }
    if (!gainAttachment)
    {
        gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, ParamIDs::Gain::Gain, gainKnob
        );
    }
}

void GainComponent::layoutMainContent()
{
    auto bounds = getLocalBounds();
    bounds.removeFromTop(TITLE_BAR_HEIGHT);
    gainKnob.setBounds(bounds.reduced(5));
}