#include "DistortionDsp.h"

DistortionDsp::DistortionDsp()
{
}

DistortionDsp::~DistortionDsp()
{
}

void DistortionDsp::prepare(const juce::dsp::ProcessSpec& spec)
{
    // init the oversampling object, magic num 2 is for 2^2= 4x oversampling
    oversampling = std::make_unique<juce::dsp::Oversampling<float>>(
        spec.numChannels,
        2, 
        juce::dsp::Oversampling<float>::filterHalfBandPolyphaseIIR
    );
    oversampling->initProcessing(spec.maximumBlockSize);
    oversampling->reset();

    // some params need to be at the oversampled rate
    auto osSpec = spec;
    osSpec.sampleRate *= oversampling->getOversamplingFactor();
    
    driveGain.prepare(osSpec);
    driveGain.setGainDecibels(0.0f);

    postGain.prepare(spec);

    waveshaper.functionToUse = [] (float x) { 
        return std::tanh(x); 
        // return std::tanh(x*drive + asymmetry); 

        // hard clipping
        // return juce::jlimit(-1.0f, 1.0f, x);
    };

    dryWet.prepare(spec);
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear); // idk

    // driveSmoothed.reset (osSpec.sampleRate, 0.02);
    // outputSmoothed.reset (spec.sampleRate, 0.02);
    // mixSmoothed.reset (spec.sampleRate, 0.02);
}

void DistortionDsp::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    juce::dsp::AudioBlock inputBlock  = context.getInputBlock();
    juce::dsp::AudioBlock outputBlock = context.getOutputBlock();

    // push dry signals before modification
    dryWet.pushDrySamples(inputBlock);

    // oversample
    outputBlock.copyFrom(inputBlock);
    juce::dsp::AudioBlock osBlock = oversampling->processSamplesUp(outputBlock);

    // process with oversampling
    juce::dsp::ProcessContextReplacing<float> osContext (osBlock);
    driveGain.process(osContext);
    waveshaper.process(osContext);
    postGain.process(osContext);

    // downsample and mix
    oversampling->processSamplesDown(outputBlock);
    dryWet.mixWetSamples(outputBlock);
}

void DistortionDsp::reset()
{
}

void DistortionDsp::setDriveGain(float gainDb)
{
    driveGain.setGainDecibels(gainDb);
}

void DistortionDsp::update(const DistortionParams& p)
{
    driveGain.setGainDecibels(p.drive);
    postGain.setGainDecibels(p.postGain);
    dryWet.setWetMixProportion(p.mix);
}