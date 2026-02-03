#include "GainComponent.h"

GainComponent::GainComponent(juce::AudioProcessorValueTreeState& state)
    : treeState (state)
{
    gainKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary); // Changed to Rotary style
    gainKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    gainKnob.setRange(0.0, 100.0, 0.1); // Set range from 0 to 100
    addAndMakeVisible(gainKnob);
}

GainComponent::~GainComponent()
{
}

void GainComponent::visibilityChanged()
{
    // Create attachment only once when component becomes visible
    if (isVisible() && !gainAttachment)
    {
        gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, "gain", gainKnob
        );
    }
}

void GainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::grey);
}

void GainComponent::resized()
{
    gainKnob.setBounds(getLocalBounds()); // Adjust bounds for the knob
}