#include "ParameterLinkerComponent.h"
#include "KnobComponent.h"

ParameterLinkerComponent::ParameterLinkerComponent(juce::AudioProcessorValueTreeState& treeState, const juce::String& propertyName)
    : treeState(treeState), propertyName(propertyName)
{
    setSize(SIZE, SIZE);
    addAndMakeVisible(label);
    label.setJustificationType(juce::Justification::centred);
    label.setFont(10.0f);
}

ParameterLinkerComponent::~ParameterLinkerComponent()
{
}

void ParameterLinkerComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().toFloat();

    // Background circle
    g.setColour(isDragging ? juce::Colours::deepskyblue : juce::Colours::cornflowerblue);
    g.fillEllipse(bounds);
}

void ParameterLinkerComponent::resized()
{
}

void ParameterLinkerComponent::mouseDown(const juce::MouseEvent& e)
{
    isDragging = false;
}

void ParameterLinkerComponent::mouseDrag(const juce::MouseEvent& e)
{
    if (!isDragging) {
        isDragging = true;

        if (e.getDistanceFromDragStart() > 5) {
            if (auto* container = juce::DragAndDropContainer::findParentDragContainerFor(this)) {
                container->startDragging("ParameterLink", this);  // description + source component
            }
        }
    }
}

void ParameterLinkerComponent::mouseUp(const juce::MouseEvent& e)
{
    isDragging = false;
    repaint();
}

void ParameterLinkerComponent::setTarget(KnobComponent* knob)
{
    targetKnob = knob;
    if (knob) {
        juce::String id = knob->getParamID();
        treeState.state.setProperty(propertyName, id, nullptr);
        label.setText(id, juce::dontSendNotification);
    }
    repaint();
}

KnobComponent* ParameterLinkerComponent::getTarget() const
{
    return targetKnob;
}