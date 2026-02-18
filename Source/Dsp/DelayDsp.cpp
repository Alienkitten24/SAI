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
    
    delayLine.reset();
    delayLine.prepare(spec);
    delayLine.setMaximumDelayInSamples(sampleRate * 4); // 4 seconds max
    delayLine.setDelay(0.0f);
    
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

    for (size_t ch = 0; ch < numChannels; ++ch)
    {
        auto* input = inputBlock.getChannelPointer (ch);
        auto* output = outputBlock.getChannelPointer (ch);

        for (size_t i = 0; i < numSamples; ++i)
        {
            auto inputSample = input[i]; 
            auto delayedSample = delayLine.popSample(ch); 

            // can use tanh() to add more "character"
            delayLine.pushSample(ch, inputSample + feedback * delayedSample);
            output[i] = delayedSample; 
        }
    }

    dryWet.mixWetSamples(outputBlock);
}

void DelayDsp::reset()
{
    delayLine.reset();
}

void DelayDsp::update(const DelayParams& p)
{
    float delaySamples = p.delayMs * sampleRate / 1000.0f;
    delayLine.setDelay(delaySamples);
    feedback = p.feedback;
    dryWet.setWetMixProportion(p.mix);
    // int type = (int) p.type;
    // if (lastType != type)
    // {
    //     setDelayMode(type);
    // }
}