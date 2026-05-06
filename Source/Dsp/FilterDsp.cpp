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

    iirFilter1.prepare(spec);
    iirFilter2.prepare(spec);
    *iirFilter1.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 1000.0f, 0.1f);
    *iirFilter2.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, 1000.0f, 0.1f);
}

void FilterDsp::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    auto& inputBlock  = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();
    
    dryWet.pushDrySamples(inputBlock);

    drive.process(context);
    iirFilter1.process(context);
    if (slopeType == SlopeType::DB24) {
        iirFilter2.process(context);
    }

    dryWet.mixWetSamples(outputBlock);
}

void FilterDsp::reset()
{
    iirFilter1.reset();
    iirFilter2.reset();
}

void FilterDsp::update(const FilterParams& p)
{
    drive.setGainDecibels(p.drive);
    dryWet.setWetMixProportion(p.mix);

    cutoff = p.cutoff;
    resonance = p.resonance;
    if (lastSlopeType != p.slopeType) {
        setSlopeType(p.slopeType);
    }
    if (lastPassType != p.passType) {
        setPassType(p.passType);
    }

    setIIRCoefficients();
}

void FilterDsp::setIIRCoefficients()
{
    switch (passType) {
        case PassType::LOWPASS:
            *iirFilter1.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoff, resonance);
            *iirFilter2.state = *juce::dsp::IIR::Coefficients<float>::makeLowPass(sampleRate, cutoff, resonance);
            break;
        case PassType::HIGHPASS:
            *iirFilter1.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, cutoff, resonance);
            *iirFilter2.state = *juce::dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, cutoff, resonance);
            break;
        case PassType::BANDPASS:
            *iirFilter1.state = *juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, cutoff, resonance);
            *iirFilter2.state = *juce::dsp::IIR::Coefficients<float>::makeBandPass(sampleRate, cutoff, resonance);
            break;
    }

}

void FilterDsp::setSlopeType(int type)
{
    switch (type) {
        case SlopeType::DB12:
            slopeType = SlopeType::DB12;
            break;
        case SlopeType::DB24:
            slopeType = SlopeType::DB24;
            break;
    }
    lastSlopeType = type;
}

void FilterDsp::setPassType(int type) 
{
    switch (type) {
        case PassType::LOWPASS:
            passType = PassType::LOWPASS;
            break;
        case PassType::HIGHPASS:
            passType = PassType::HIGHPASS;
            break;
        case PassType::BANDPASS:
            passType = PassType::BANDPASS;
            break;
    }
    lastPassType = type;
}