#pragma once

#include <JuceHeader.h>

class GainDsp
{
public:
    GainDsp();
    ~GainDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void setGain(float gainDb);

    // enum {
    //     gainIndex
    // };

private:
    juce::dsp::Gain<float> gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainDsp)
};