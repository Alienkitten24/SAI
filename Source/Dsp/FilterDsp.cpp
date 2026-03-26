#include "FilterDsp.h"

FilterDsp::FilterDsp()
{
}

FilterDsp::~FilterDsp()
{
}

void FilterDsp::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;

    iirFilter.prepare(spec);
    *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 1000.0f, 0.1f);

    // // Map normalized cutoff (0-1) to frequency range (20 Hz - 20 kHz)
    // float cutoffHz = 20.0f * std::pow(1000.0f, 0.5f); // 447 Hz default
    // *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoffHz, 0.707f);
}

void FilterDsp::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    // auto& inputBlock  = context.getInputBlock();
    // auto& outputBlock = context.getOutputBlock();
    
    // dryWet.pushDrySamples(inputBlock);

    drive.process(context);
    iirFilter.process(context);

    // dryWet.mixWetSamples(outputBlock);
}

void FilterDsp::reset()
{
    iirFilter.reset();
}

void FilterDsp::update(const FilterParams& p)
{
    drive.setGainDecibels(p.drive);
    dryWet.setWetMixProportion(p.mix);

    *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, p.cutoff, p.resonance);

    // // Map normalized cutoff (0-1) to frequency range (20 Hz - 20 kHz) logarithmically
    // float cutoffHz = 20.0f * std::pow(1000.0f, p.cutoff);
    
    // // Map normalized resonance (0-1) to Q range (0.1 - 10.0)
    // float q = 0.1f + (p.resonance * 9.9f);
    
    // *iirFilter.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoffHz, q);

    // // TODO: Handle slope type and pass type switching
}