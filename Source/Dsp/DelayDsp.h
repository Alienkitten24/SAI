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

    void processMono(juce::dsp::ProcessContextReplacing<float>& context);
    void processStereo(juce::dsp::ProcessContextReplacing<float>& context);
    void processPingPong(juce::dsp::ProcessContextReplacing<float>& context);

    void setDelayType(int type);

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineL;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineR;

    double sampleRate;
    float feedback; 
    int delayType = DelayType::MONO;
    int lastType = DelayType::MONO;

    juce::dsp::DryWetMixer<float> dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayDsp)
};