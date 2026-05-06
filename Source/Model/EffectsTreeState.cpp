#include "EffectsTreeState.h"

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::AudioProcessorParameterGroup>> params;
    // params.reserve()


    // maybe use emplace_back over push_back ? need to research
    auto gainGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Gain, "Gain", "|"
    );
        gainGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Gain::Active, "Active", false
        ));
        gainGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Gain::Gain, "Gain", -60.0f, 6.0f, 0.0f
        ));


    auto distortionGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Distortion, "Distortion", "|"
    );
        distortionGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Distortion::Active, "Active", false
        ));
        distortionGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Distortion::Drive, "Drive", 0.0f, 40.0f, 10.0f
        ));
        distortionGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Distortion::PostGain, "Post Gain", -60.0f, 6.0f, 0.0f
        ));
        distortionGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Distortion::Mix, "Mix", 0.0f, 1.0f, 0.5f
        ));
        // TODO maybe move this stringarray declaration 
        distortionGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Distortion::Type, "Type", juce::StringArray { "Soft Clip", "Hard Clip", "Bit Crush" }, 0
        ));

    auto delayGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Delay, "Delay", "|"
    );
        delayGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Delay::Active, "Active", false 
        ));
        delayGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Delay::Feedback, "Feedback", 0.0f, 1.0f, 0.7f 
        ));
        delayGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Delay::Mix, "Mix", 0.0f, 1.0f, 0.5f 
        ));
        delayGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Delay::DelayMsL, "Delay Ms L", 0.0f, 1000.0f, 250.0f 
        ));
        delayGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Delay::DelayMsR, "Delay Ms R", 0.0f, 1000.0f, 250.0f 
        ));
        delayGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Delay::DelayType, "Delay Type", juce::StringArray { "Mono", "Stereo", "Ping Pong" }, 0
        ));
        // delayGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
        //     ParamIDs::Delay::TempoType, "Tempo Type", juce::StringArray { "Milliseconds", "Tempo Straight", "Tempo Dotted", "Tempo Triplet" }, 0
        // ));
        // delayGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
        //     ParamIDs::Delay::Division, "Division", juce::StringArray { "1/64", "1/32", "1/16", "1/8", "1/4", "1/2", "1/1" }, 0
        // ));

    auto filterGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Filter, "Filter", "|"
    );
        filterGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Filter::Active, "Active", false 
        ));
        filterGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Filter::Mix, "Mix", 0.0f, 1.0f, 0.5f
        ));
        auto cutoffRange = juce::NormalisableRange<float>(20.0f, 20000.0f, 0.1f);
        cutoffRange.setSkewForCentre(1000.0f);
        filterGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Filter::Cutoff, "Cutoff", cutoffRange, 1000.0f 
        ));
        filterGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Filter::Resonance, "Resonance", 0.1f, 10.0f, 0.707f 
        ));
        filterGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Filter::Drive, "Drive", 0.0f, 40.0f, 0.0f
        ));
        filterGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Filter::SlopeType, "Slope Type", juce::StringArray { "12 dB", "24 dB" }, 0
        ));
        filterGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Filter::PassType, "Pass Type", juce::StringArray { "Low Pass", "High Pass", "Band Pass" }, 0
        ));

    auto proportionalGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Proportional, "Controller", "|"
    );
        proportionalGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Proportional::Active, "Active", false 
        ));
        proportionalGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Proportional::SensorDataType, "Sensor Data Type", ParamIDs::Sensor::SensorDataStrings, 0
        ));
        proportionalGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Proportional::Minimum, "Minimum", 0.0f, 1.0f, 0.5f
        ));
        proportionalGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Proportional::Maximum, "Maximum", 0.0f, 1.0f, 0.5f
        ));
        proportionalGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Proportional::Multiplier, "Multiplier", 0.0f, 10.0f, 1.0f
        ));

    auto thresholdGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Threshold, "Controller", "|"
    );
        thresholdGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Threshold::Active, "Active", false 
        ));
        thresholdGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Threshold::SensorDataType, "Sensor Data Type", ParamIDs::Sensor::SensorDataStrings, 0
        ));
        thresholdGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Threshold::Threshold, "Threshold", 0.0f, 1.0f, 0.5f
        ));
        thresholdGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Threshold::Modifier, "Modifier", 0.0f, 1.0f, 0.5f
        ));
    
    params.push_back(std::move(gainGroup));
    params.push_back(std::move(distortionGroup));
    params.push_back(std::move(delayGroup));
    params.push_back(std::move(filterGroup));

    params.push_back(std::move(proportionalGroup));
    params.push_back(std::move(thresholdGroup));

    return { params.begin(), params.end() };
}
