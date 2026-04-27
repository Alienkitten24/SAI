#include "KnobComponent.h"
#include "EllipseComponent.h"
#include "ParameterLinkerComponent.h"

KnobComponent::KnobComponent(
    const juce::String& text,
    juce::AudioProcessorValueTreeState& treeState,
    const juce::String& paramID_)
    : paramID(paramID_), parameter(treeState.getParameter(paramID_))
{
    label.setText(text, juce::dontSendNotification);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);

    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    addAndMakeVisible(slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        treeState, paramID_, slider
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

bool KnobComponent::isInterestedInDragSource(const SourceDetails& details)
{
    return details.description == "ParameterLink";
}

void KnobComponent::itemDropped(const SourceDetails& details)
{
    if (auto* source = dynamic_cast<ParameterLinkerComponent*>(details.sourceComponent.get())) {
        source->setTarget(this);
        return;
    }

    if (auto* ellipseSource = dynamic_cast<EllipseComponent*>(details.sourceComponent.get())) {
        if (auto* parentSource = dynamic_cast<ParameterLinkerComponent*>(ellipseSource->getParentComponent())) {
            parentSource->setTarget(this);
        }
    }
}

juce::String KnobComponent::getParamID() const
{
    return paramID;
}