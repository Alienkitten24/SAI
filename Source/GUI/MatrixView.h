#pragma once

#include <JuceHeader.h>
#include "../PluginProcessor.h"

class MatrixView : public juce::Component
{
public:
    MatrixView (TestAudioProcessor&);
    ~MatrixView();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    TestAudioProcessor& audioProcessor;

    juce::Label label;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixView)
};