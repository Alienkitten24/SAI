#include "ParameterLinkerComponent.h"

ParameterLinkerComponent::ParameterLinkerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& propertyName)
    : treeState(treeState), propertyName(propertyName)
{
    setSize(SIZE, SIZE + LABEL_HEIGHT);
    
    addAndMakeVisible(ellipse);
    addAndMakeVisible(label);
    
    label.setJustificationType(juce::Justification::centred);
    label.setFont(15.0f);
}

ParameterLinkerComponent::~ParameterLinkerComponent()
{
}

void ParameterLinkerComponent::resized()
{
    auto bounds = getLocalBounds();
    
    // Position ellipse at the top
    int ellipseX = (bounds.getWidth() - SIZE) / 2;
    ellipse.setBounds(ellipseX, 0, SIZE, SIZE);
    
    // Position label below the ellipse
    const int labelY = SIZE + 4;
    label.setBounds(bounds.withTop(labelY));
}

void ParameterLinkerComponent::setTarget(KnobComponent* knob)
{
    targetKnob = knob;
    if (knob) {
        juce::String id = knob->getParamID();
        treeState.state.setProperty(propertyName, id, nullptr);
        label.setText(id, juce::dontSendNotification);
    }
}

KnobComponent* ParameterLinkerComponent::getTarget() const
{
    return targetKnob;
}