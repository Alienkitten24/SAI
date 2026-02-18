#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../Model/DelayParams.h"

class DelayDsp
{
public:
    DelayDsp();
    ~DelayDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void update(const DelayParams& p);

private:
    // delay time in seconds or bpm tempo 
        // sync
    // feedback aka decay rate
    // mix
    // pre/postGain ?
    // filter
    // type: mono, stereo, pingpong
    // maybe: pitch modulation, pan, slight distortion

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLine;

    double sampleRate;
    float feedback; 

    juce::dsp::DryWetMixer<float> dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayDsp)
};