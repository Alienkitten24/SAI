#include "GainDsp.h"

GainDsp::GainDsp()
{
}

GainDsp::~GainDsp()
{
}

void GainDsp::prepare(const juce::dsp::ProcessSpec& spec)
{
    gain.prepare(spec);
    gain.setGainDecibels(0.0f);
}

void GainDsp::process(const juce::dsp::ProcessContextReplacing<float>& context)
{
    gain.process(context);
}

void GainDsp::reset()
{
    gain.reset();
}

void GainDsp::update(const GainParams& p)
{
    gain.setGainDecibels(p.gain);
}