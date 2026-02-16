#pragma once

#include <JuceHeader.h>
#include "../Model/GainParams.h"

class GainDsp
{
public:
    GainDsp();
    ~GainDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void update(const GainParams& p);

private:
    juce::dsp::Gain<float> gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainDsp)
};