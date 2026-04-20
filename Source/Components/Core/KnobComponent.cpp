#include "KnobComponent.h"

KnobComponent::KnobComponent(
    const juce::String& text,
    juce::AudioProcessorValueTreeState& treeState,
    const juce::String& paramID)
{
    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    // slider.setRange(0.0, 100.0, 0.1); 
    addAndMakeVisible(slider);

    parameter = treeState.getParameter(paramID);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        treeState, paramID, slider
    );

}

KnobComponent::~KnobComponent()
{
}

void KnobComponent::paint(juce::Graphics& g)
{
}

void KnobComponent::resized()
{
    auto bounds = getLocalBounds();

    auto labelHeight = 20;
    label.setBounds(bounds.removeFromTop(labelHeight));

    slider.setBounds(bounds);
}

juce::Slider& KnobComponent::getSlider()
{
    return slider;
}

juce::RangedAudioParameter* KnobComponent::getParameter()
{
    return parameter;
}