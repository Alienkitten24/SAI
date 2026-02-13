#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../Model/DistortionParams.h"


class DistortionDsp
{
public:
    DistortionDsp();
    ~DistortionDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void setDriveGain(float gainDb);

    void update(const DistortionParams& p);

private:
    // pregain
    // postgain
    // drive
    // mix
    // prefilter
    // postfilter
    // oversampling
    // Waveshaper -> clipping, bitcrush
    // asymetry/bias
    // threshold

    std::unique_ptr<juce::dsp::Oversampling<float>> oversampling;

    juce::dsp::Gain<float> driveGain;
    juce::dsp::Gain<float> postGain;

    // juce::dsp::Bias<float> asymmetry;

    juce::dsp::WaveShaper<float> waveshaper;

    // TODO decide to name all dryWet or Mix
    juce::dsp::DryWetMixer<float> dryWet;

    // juce::SmoothedValue<float> driveSmoothed;
    // juce::SmoothedValue<float> postSmoothed;
    // juce::SmoothedValue<float> mixSmoothed;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionDsp)
};