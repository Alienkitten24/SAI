#pragma once

#include <JuceHeader.h>
#include <memory>
#include "../Model/FilterParams.h"

class FilterDsp
{
public:
    FilterDsp();
    ~FilterDsp();

    void prepare(const juce::dsp::ProcessSpec& spec);
    void process(const juce::dsp::ProcessContextReplacing<float>& context); 
    void reset();

    void update(const FilterParams& p);

private:

    double sampleRate;

    juce::dsp::ProcessorDuplicator<
        juce::dsp::IIR::Filter<float>, juce::dsp::IIR::Coefficients<float>
    > iirFilter;

    juce::dsp::Gain<float> drive;
    juce::dsp::DryWetMixer<float> dryWet;

    int slopeType = SlopeType::DB12;
    int lastSlopeType = SlopeType::DB12;

    int passType = PassType::LOWPASS;
    int lastPassType = PassType::LOWPASS;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterDsp)
};