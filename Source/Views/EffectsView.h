#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"
#include "../Components/Effects/GainComponent.h"
#include "../Components/Effects/DistortionComponent.h"

class EffectsView : public juce::Component
{
public:
    EffectsView (TestAudioProcessor&);
    ~EffectsView();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    TestAudioProcessor& audioProcessor;

    juce::Label label;

    GainComponent gainComponent;
    DistortionComponent distortionComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EffectsView)
};