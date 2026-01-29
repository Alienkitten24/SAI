#include "GainComponent.h"

GainComponent::GainComponent(juce::AudioProcessorValueTreeState& state)
    : treeState (state)
{
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(gainSlider);

    // gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
    //     treeState, "gain", gainSlider
    // ); 
}

GainComponent::~GainComponent()
{
}

void GainComponent::visibilityChanged()
{
    // Create attachment only once when component becomes visible
    // idk if this actually makes any difference
    if (isVisible() && !gainAttachment)
    {
        gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
            treeState, "gain", gainSlider
        );
    }
}


void GainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::blue);
}

void GainComponent::resized()
{
    gainSlider.setBounds(getLocalBounds());
}