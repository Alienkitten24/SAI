#include "ComboBoxComponent.h"

ComboBoxComponent::ComboBoxComponent(
    juce::AudioProcessorValueTreeState& treeState,
    const juce::String& paramID)
{
    addAndMakeVisible(comboBox);

    // autofills the combobox with the stringarray from treeState
    if (auto* param = dynamic_cast<juce::AudioParameterChoice*>(treeState.getParameter(paramID)))
    {
        comboBox.addItemList(param->choices, 1);
    }

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(
        treeState, paramID, comboBox
    );
}

ComboBoxComponent::~ComboBoxComponent()
{
}

void ComboBoxComponent::paint(juce::Graphics& g)
{
}

void ComboBoxComponent::resized()
{
    auto bounds = getLocalBounds();
    comboBox.setBounds(bounds);
}