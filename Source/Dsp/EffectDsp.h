// #pragma once

// #include <JuceHeader.h>

// /**
//  * @brief Base class for all DSP effect processors
//  * 
//  * All audio effect DSP classes should inherit from this abstract class
//  * and implement the required pure virtual methods.
//  */
// class EffectDsp
// {
// public:
//     EffectDsp() = default;
//     virtual ~EffectDsp() = default;

//     virtual void prepare(const juce::dsp::ProcessSpec& spec) = 0;
//     virtual void process(juce::dsp::ProcessContextReplacing<float>& context) = 0;
//     virtual void reset() = 0;

//     virtual void update(const EffectParams& p) = 0;

// private:
//     JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(EffectDsp)
// };