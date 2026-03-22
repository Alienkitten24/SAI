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
    // void setTempoType(int type);
    // void setDivisionType(int type);

    double sampleRate;
    float feedback; 
    juce::dsp::DryWetMixer<float> dryWet;

    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineL;
    juce::dsp::DelayLine<float, juce::dsp::DelayLineInterpolationTypes::Linear> delayLineR;

    int delayType = DelayType::MONO;
    int lastDelayType = DelayType::MONO;

    // int tempoType = TempoType::STRAIGHT;
    // int lastTempoType = TempoType::STRAIGHT;

    // int division = Division::EIGHTH;
    // int lastDivisionType = Division::EIGHTH;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayDsp)
};