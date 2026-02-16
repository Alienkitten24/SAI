#include "EffectsTreeState.h"

juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout()
{
    std::vector<std::unique_ptr<juce::AudioProcessorParameterGroup>> params;
    // params.reserve()


    // maybe use emplace_back over push_back ? need to research
    // TODO figure out a good Db range (maybe use normalizablerange<> ?)
    // https://github.com/JanWilczek/juce-webview-tutorial/blob/main/plugin/source/PluginProcessor.cpp line 211
    // TODO apparently you don't have to addChild, can just init it in the group line
    auto gainGroup = std::make_unique<juce::AudioProcessorParameterGroup>(
        GroupIDs::Gain, "Gain", "|"
    );
        gainGroup->addChild(std::make_unique<juce::AudioParameterBool>(
            ParamIDs::Gain::Active, "Active", false
        ));
        gainGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Gain::Gain, "Gain", -60.0f, 0.0f, -6.0f
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
            ParamIDs::Distortion::PostGain, "Post Gain", -60.0f, 0.0f, -6.0f
        ));
        // TODO i think this has usuable vales from 0-1 rn and 1-100 is the same
        distortionGroup->addChild(std::make_unique<juce::AudioParameterFloat>(
            ParamIDs::Distortion::Mix, "Mix", 0.0f, 40.0f, 10.0f
        ));
        distortionGroup->addChild(std::make_unique<juce::AudioParameterChoice>(
            ParamIDs::Distortion::Type, "Type", juce::StringArray { "Soft Clip", "Hard Clip" }, 0
        ));
    
    params.push_back(std::move(gainGroup));
    params.push_back(std::move(distortionGroup));

    return { params.begin(), params.end() };
}
