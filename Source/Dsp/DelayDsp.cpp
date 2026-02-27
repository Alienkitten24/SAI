#include "DelayDsp.h"

DelayDsp::DelayDsp()
{
}

DelayDsp::~DelayDsp()
{
}

void DelayDsp::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    
    delayLineL.reset();
    delayLineL.prepare(spec);
    delayLineL.setMaximumDelayInSamples(sampleRate * 4); // 4 seconds max
    delayLineL.setDelay(0.0f);

    delayLineR.reset();
    delayLineR.prepare(spec);
    delayLineR.setMaximumDelayInSamples(sampleRate * 4); // 4 seconds max
    delayLineR.setDelay(0.0f);

    delayType = DelayType::MONO;
    lastType = DelayType::MONO;
    
    dryWet.prepare(spec);
    dryWet.setMixingRule(juce::dsp::DryWetMixingRule::linear); // idk
}

void DelayDsp::process(juce::dsp::ProcessContextReplacing<float>& context)
{
    auto& inputBlock  = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    auto numSamples = outputBlock.getNumSamples();
    auto numChannels = outputBlock.getNumChannels();

    dryWet.pushDrySamples(inputBlock);

    // TODO maybe need to support for when there is not exactly 2 audio channels 
    switch (delayType) {
        case DelayType::MONO :
            processMono(context);
            break;
        case DelayType::STEREO :
            processStereo(context);
            break;
        case DelayType::PINGPONG :
            processPingPong(context);
            break;
        default: 
            processStereo(context);
            break;
    }

    dryWet.mixWetSamples(outputBlock);
}

void DelayDsp::reset()
{
    delayLineL.reset();
    delayLineR.reset();
}

void DelayDsp::processMono(juce::dsp::ProcessContextReplacing<float>& context)
{

    auto& inputBlock  = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    auto numSamples = outputBlock.getNumSamples();
    // auto numChannels = outputBlock.getNumChannels();

    auto* inputL = inputBlock.getChannelPointer(0); 
    auto* inputR = inputBlock.getChannelPointer(1); 
    auto* outputL = outputBlock.getChannelPointer(0);
    auto* outputR = outputBlock.getChannelPointer(1);

    dryWet.pushDrySamples(inputBlock);

    for (size_t i = 0; i < numSamples; ++i)
    {
        auto inputSample = (inputL[i] + inputR[i]) * 0.5f; // sum to mono
        auto delayedSample = delayLineL.popSample(0); // use channel 0 for everything
        delayLineL.pushSample(0, inputSample + feedback * delayedSample);
        outputL[i] = delayedSample; 
        outputR[i] = delayedSample;
    }

    dryWet.mixWetSamples(outputBlock);
}

void DelayDsp::processStereo(juce::dsp::ProcessContextReplacing<float>& context)
{
    auto& inputBlock  = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    auto numSamples = outputBlock.getNumSamples();

    auto* inputL = inputBlock.getChannelPointer(0); 
    auto* inputR = inputBlock.getChannelPointer(1); 
    auto* outputL = outputBlock.getChannelPointer(0);
    auto* outputR = outputBlock.getChannelPointer(1);

    dryWet.pushDrySamples(inputBlock);

    for (size_t i = 0; i < numSamples; ++i)
    {
        auto inputSampleL = inputL[i]; 
        auto inputSampleR = inputR[i];

        auto delayedSampleL = delayLineL.popSample(0); 
        auto delayedSampleR = delayLineR.popSample(0); 

        delayLineL.pushSample(0, inputSampleL + feedback * delayedSampleL);
        delayLineR.pushSample(0, inputSampleR + feedback * delayedSampleR);

        outputL[i] = delayedSampleL; 
        outputR[i] = delayedSampleR; 
    }

    dryWet.mixWetSamples(outputBlock);
}

void DelayDsp::processPingPong(juce::dsp::ProcessContextReplacing<float>& context)
{
    auto& inputBlock  = context.getInputBlock();
    auto& outputBlock = context.getOutputBlock();

    auto numSamples = outputBlock.getNumSamples();

    auto* inputL = inputBlock.getChannelPointer(0); 
    auto* inputR = inputBlock.getChannelPointer(1); 
    auto* outputL = outputBlock.getChannelPointer(0);
    auto* outputR = outputBlock.getChannelPointer(1);

    dryWet.pushDrySamples(inputBlock);

    for (size_t i = 0; i < numSamples; ++i)
    {
        auto inputSampleL = inputL[i]; 
        auto inputSampleR = inputR[i];

        auto delayedSampleL = delayLineL.popSample(0); 
        auto delayedSampleR = delayLineR.popSample(0); 

        delayLineL.pushSample(0, inputSampleL + feedback * delayedSampleR);
        delayLineR.pushSample(0, inputSampleR + feedback * delayedSampleL);

        outputL[i] = delayedSampleL; 
        outputR[i] = delayedSampleR; 
    }

    dryWet.mixWetSamples(outputBlock);
}

void DelayDsp::update(const DelayParams& p)
{
    float delaySamplesL = p.delayMsR * sampleRate / 1000.0f;
    delayLineL.setDelay(delaySamplesL);

    float delaySamplesR = p.delayMsL * sampleRate / 1000.0f;
    delayLineR.setDelay(delaySamplesR);

    feedback = p.feedback;

    dryWet.setWetMixProportion(p.mix);

    int type = p.type;
    if (lastType != type)
    {
        setDelayType(type);
    }
}

void DelayDsp::setDelayType(int type) {
    switch (type) {
        case DelayType::MONO:
            delayType = DelayType::MONO;
            break;
        case DelayType::STEREO:
            delayType = DelayType::STEREO;
            break;
        case DelayType::PINGPONG:
            delayType = DelayType::PINGPONG;
            break;
        default:
            delayType = DelayType::MONO;
            break;
    }

    lastType = type;
}