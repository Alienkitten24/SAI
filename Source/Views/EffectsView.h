#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../Components/Effects/GainComponent.h"
#include "../Components/Effects/DistortionComponent.h"
#include "../Components/Effects/DelayComponent.h"
#include "../Components/Effects/FilterComponent.h"
#include "../Components/Motions/ProportionalControllerComponent.h"
#include "../Components/Motions/ThresholdControllerComponent.h"

class EffectsView : public juce::Component, 
                    public juce::DragAndDropContainer
{
public:
    EffectsView (AudimoAudioProcessor&);
    ~EffectsView();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    AudimoAudioProcessor& audioProcessor;

    GainComponent gainComponent;
    DistortionComponent distortionComponent;
    DelayComponent delayComponent;
    FilterComponent filterComponent;
    ProportionalControllerComponent proportionalControllerComponent;
    ThresholdControllerComponent thresholdControllerComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsView)
};