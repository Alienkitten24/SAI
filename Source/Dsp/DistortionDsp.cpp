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
    // TODO make it so you can change oversampling rate
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

    // set initial selection to SOFTCLIP
    setWaveshaper(DistortionType::SOFTCLIP);

    dryWet.prepare(spec);
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear); // idk

    // driveSmoothed.reset (osSpec.sampleRate, 0.02);
    // outputSmoothed.reset (spec.sampleRate, 0.02);
    // mixSmoothed.reset (spec.sampleRate, 0.02);
}

void DistortionDsp::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    // TODO since this is replacing dont need two blocks... maybe
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

void DistortionDsp::update(const DistortionParams& p)
{
    driveGain.setGainDecibels(p.drive);
    postGain.setGainDecibels(p.postGain);
    dryWet.setWetMixProportion(p.mix);
    int type = p.type;
    if (lastType != type)
    {
        setWaveshaper(type);
    }
}

void DistortionDsp::setWaveshaper(int type) 
{
    switch (type) {
        case DistortionType::SOFTCLIP :
            waveshaper.functionToUse = [] (float x) { 
                return std::tanh(x); 
                // TODO consider using an approximation formula
                // or juce::dsp::FastMathApproximations::tanh
            };
            break;
        case DistortionType::HARDCLIP :
            waveshaper.functionToUse = [] (float x) { 
                return juce::jlimit(-1.0f, 1.0f, x); 
            };
            break;
        case DistortionType::BITCRUSH :
            waveshaper.functionToUse = [] (float x) {
                // TODO should be able to vary bitdepth
                float bitDepth = 4.0f;
                float levels = std::pow(2.0f, bitDepth);
                return std::round(x * levels) / levels;
            };
            break;
    }

    lastType = type;
}