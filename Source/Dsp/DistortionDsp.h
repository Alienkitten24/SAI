#pragma once

#include <JuceHeader.h>
#include <memory>
#include <cmath>
#include "../Model/DistortionParams.h"


class DistortionDsp
{
public:
    DistortionDsp();
    ~DistortionDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void update(const DistortionParams& p);

private:
    void setWaveshaper(int type);

    std::unique_ptr<juce::dsp::Oversampling<float>> oversampling;

    juce::dsp::Gain<float> driveGain;
    juce::dsp::Gain<float> postGain;

    // juce::dsp::Bias<float> asymmetry;

    int lastType = DistortionType::SOFTCLIP;
    juce::dsp::WaveShaper<float> waveshaper;

    juce::dsp::DryWetMixer<float> dryWet;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionDsp)
};