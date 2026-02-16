/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <memory>

#include "Communication/BLEManager.h"
#include "Model/SensorData.h"
#include "Model/EffectsTreeState.h"
#include "Model/GainParams.h"
#include "Model/DistortionParams.h"
#include "Dsp/GainDsp.h"
#include "Dsp/DistortionDsp.h"

//==============================================================================
/**
*/
class TestAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    TestAudioProcessor();
    ~TestAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    SensorData getSensorDataCopy() const; 
    BLEManager& getBLEManager();
    void onOSCBundleReceived(const juce::OSCBundle& bundle);
    void onOSCMessageReceived(const juce::OSCMessage& message);

    //==============================================================================
    juce::AudioProcessorValueTreeState& getTreeState();

private:
    //==============================================================================
    BLEManager m_bleManager;
    mutable juce::CriticalSection lock; // for sensordata
    SensorData m_sensorData;

    //==============================================================================
    // juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    // TODO make treeState take an undo manager ?
    // research if defining { } is better to do in .h or .cpp 
    juce::AudioProcessorValueTreeState m_treeState {
      *this, nullptr, "PARAMETERS", createParameterLayout()
    };

    GainDsp gainDsp;
    GainParams gainParams;
    GainParamPointers gainParamPointers;

    DistortionDsp distortionDsp;
    DistortionParams distortionParams;
    DistortionParamPointers distortionParamPointers;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TestAudioProcessor)
};
