#include "ParameterLinkerComponent.h"

ParameterLinkerComponent::ParameterLinkerComponent()
{
    setSize(SIZE, SIZE);
}

ParameterLinkerComponent::~ParameterLinkerComponent()
{
}

void ParameterLinkerComponent::paint(juce::Graphics& g)
{
    // Draw square background
    g.setColour(juce::Colours::darkgrey);
    g.drawRect(getLocalBounds(), STROKE_WIDTH);

    // Draw plus sign (+) centered in the square
    auto bounds = getLocalBounds().reduced(STROKE_WIDTH + 2);

    g.setColour(juce::Colours::white);
    g.setFont(18.0f);
    g.drawText("+", bounds, juce::Justification::centred, true);
}

void ParameterLinkerComponent::resized()
{
}

void ParameterLinkerComponent::mouseDrag(const juce::MouseEvent& e)
{
    // if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this)) {
    //     container->startDragging("ParameterLink", this);  // description + source component
    // }
}

void ParameterLinkerComponent::setTarget(KnobComponent* knob)
{
    targetKnob = knob;
    repaint();
}

KnobComponent* ParameterLinkerComponent::getTarget() const
{
    return targetKnob;
}