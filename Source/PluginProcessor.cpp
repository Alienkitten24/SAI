/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TestAudioProcessor::TestAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Lambda: subscribe to OSC bundles from the receiver
    m_bleManager.getReceiver().onBundleReceived = 
        [this](const juce::OSCBundle& bundle) { onOSCBundleReceived(bundle); };
    m_bleManager.getReceiver().onMessageReceived = 
        [this](const juce::OSCMessage& message) { onOSCMessageReceived(message); };

    proportionalParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Proportional::Active);
    proportionalParamPointers.sensorDataTypeParam = m_treeState.getRawParameterValue(ParamIDs::Proportional::SensorDataType);
    proportionalParamPointers.minimumParam = m_treeState.getRawParameterValue(ParamIDs::Proportional::Minimum);
    proportionalParamPointers.maximumParam = m_treeState.getRawParameterValue(ParamIDs::Proportional::Maximum);
    proportionalParamPointers.multiplierParam = m_treeState.getRawParameterValue(ParamIDs::Proportional::Multiplier);

    thresholdParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Threshold::Active);
    thresholdParamPointers.sensorDataTypeParam = m_treeState.getRawParameterValue(ParamIDs::Threshold::SensorDataType);
    thresholdParamPointers.thresholdParam = m_treeState.getRawParameterValue(ParamIDs::Threshold::Threshold);
    thresholdParamPointers.modifierParam = m_treeState.getRawParameterValue(ParamIDs::Threshold::Modifier);

    gainParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Gain::Active);
    gainParamPointers.gainParam = m_treeState.getRawParameterValue(ParamIDs::Gain::Gain);

    distortionParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Active);
    distortionParamPointers.driveParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Drive);
    distortionParamPointers.postGainParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::PostGain);
    distortionParamPointers.mixParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Mix);
    distortionParamPointers.typeParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Type);

    delayParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Delay::Active);
    delayParamPointers.feedbackParam = m_treeState.getRawParameterValue(ParamIDs::Delay::Feedback);
    delayParamPointers.mixParam = m_treeState.getRawParameterValue(ParamIDs::Delay::Mix);
    delayParamPointers.delayMsLParam = m_treeState.getRawParameterValue(ParamIDs::Delay::DelayMsL);
    delayParamPointers.delayMsRParam = m_treeState.getRawParameterValue(ParamIDs::Delay::DelayMsR);
    delayParamPointers.delayTypeParam = m_treeState.getRawParameterValue(ParamIDs::Delay::DelayType);

    filterParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Filter::Active);
    filterParamPointers.mixParam = m_treeState.getRawParameterValue(ParamIDs::Filter::Mix);
    filterParamPointers.cutoffParam = m_treeState.getRawParameterValue(ParamIDs::Filter::Cutoff);
    filterParamPointers.resonanceParam = m_treeState.getRawParameterValue(ParamIDs::Filter::Resonance);
    filterParamPointers.driveParam = m_treeState.getRawParameterValue(ParamIDs::Filter::Drive);
    filterParamPointers.slopeTypeParam = m_treeState.getRawParameterValue(ParamIDs::Filter::SlopeType);
    filterParamPointers.passTypeParam = m_treeState.getRawParameterValue(ParamIDs::Filter::PassType);
}

TestAudioProcessor::~TestAudioProcessor()
{
    m_bleManager.stop();
}

//==============================================================================
SensorDataSnapshot TestAudioProcessor::getSensorDataCopy() const
{
    return m_sensorData.getCopy();
}

SensorData& TestAudioProcessor::getSensorData()
{
    return m_sensorData;
}

BLEManager& TestAudioProcessor::getBLEManager() 
{
    return m_bleManager;
}

void TestAudioProcessor::onOSCBundleReceived(const juce::OSCBundle& bundle)
{
    // Temporary storage and flags
    float tmpTime = 0.0f;
    int tmpProximity = 0;
    float tmpAx = 0.0f, tmpAy = 0.0f, tmpAz = 0.0f;
    float tmpGx = 0.0f, tmpGy = 0.0f, tmpGz = 0.0f;
    float tmpEx = 0.0f, tmpEy = 0.0f, tmpEz = 0.0f;
    float tmpMicRms = 0.0f;
    
    bool gotTime = false;
    bool gotProximity = false;
    // bool gotGesture = false;
    bool gotAccel = false;
    bool gotGyro = false;
    bool gotEuler = false;
    bool gotMic = false;

    // Iterate every message in the bundle (order doesn't matter)
    for (int i = 0; i < bundle.size(); ++i)
    {
        const juce::OSCMessage& message = bundle[i].getMessage();
        auto addr = message.getAddressPattern().toString();

        // Map address to an integer id, then switch on it.
        int msgId = -1;
        if (addr == "/audimo/time")        msgId = 0;
        else if (addr == "/audimo/prox")   msgId = 1;
        // else if (addr == "/audimo/gest")   msgId = 2;
        else if (addr == "/audimo/accel")  msgId = 3;
        else if (addr == "/audimo/gyro")   msgId = 4;
        else if (addr == "/audimo/euler")  msgId = 5;
        else if (addr == "/audimo/mic")    msgId = 6;

        switch (msgId)
        {
            case 0: // /audimo/time
                if (message.size() >= 1 && message[0].isFloat32())
                {
                    tmpTime = message[0].getFloat32();
                    gotTime = true;
                }
                break;

            case 1: // /audimo/prox
                if (message.size() >= 1 && message[0].isInt32())
                {
                    tmpProximity = message[0].getInt32();
                    gotProximity = true;
                }
                break;

            // TODO rethink this
            case 2: // /audimo/gest
                // if (message.size() >= 1 && message[0].isInt32())
                // {
                //     tmp.gesture = message[0].getInt32();
                //     gotGesture = true;
                // }
                break;

            case 3: // /audimo/accel
                if (message.size() >= 3 && message[0].isFloat32() && message[1].isFloat32() && message[2].isFloat32())
                {
                    tmpAx = message[0].getFloat32();
                    tmpAy = message[1].getFloat32();
                    tmpAz = message[2].getFloat32();
                    gotAccel = true;
                }
                break;

            case 4: // /audimo/gyro
                if (message.size() >= 3 && message[0].isFloat32() && message[1].isFloat32() && message[2].isFloat32())
                {
                    tmpGx = message[0].getFloat32();
                    tmpGy = message[1].getFloat32();
                    tmpGz = message[2].getFloat32();
                    gotGyro = true;
                }
                break;

            case 5: // /audimo/euler
                if (message.size() >= 3 && message[0].isFloat32() && message[1].isFloat32() && message[2].isFloat32())
                {
                    tmpEx = message[0].getFloat32();
                    tmpEy = message[1].getFloat32();
                    tmpEz = message[2].getFloat32();
                    gotEuler = true;
                }
                break;

            case 6: // /audimo/mic
                if (message.size() >= 1 && message[0].isFloat32())
                {
                    tmpMicRms = message[0].getFloat32();
                    gotMic = true;
                }
                break;

            default:
                // unknown address: ignore
                break;
        }
    }

    // Apply updates through thread-safe setters (only overwrite fields that were present)
    if (gotTime)        m_sensorData.setTime(tmpTime);
    if (gotProximity)   m_sensorData.setProximity(tmpProximity);
    if (gotAccel)       m_sensorData.setAcceleration(tmpAx, tmpAy, tmpAz);
    if (gotGyro)        m_sensorData.setGyro(tmpGx, tmpGy, tmpGz);
    if (gotEuler)       m_sensorData.setEuler(tmpEx, tmpEy, tmpEz);
    if (gotMic)         m_sensorData.setMicRms(tmpMicRms);

}

void TestAudioProcessor::onOSCMessageReceived(const juce::OSCMessage& message)
{
    auto addr = message.getAddressPattern().toString();
    if (addr == "/audimo/gest") {
        if (message.size() >= 1 && message[0].isString())
        {
            m_sensorData.setGesture(message[0].getString());
        }
    }
}

//==============================================================================
juce::AudioProcessorValueTreeState& TestAudioProcessor::getTreeState()
{
    return m_treeState;
}

//==============================================================================
const juce::String TestAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TestAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TestAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TestAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TestAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TestAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TestAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TestAudioProcessor::getProgramName (int index)
{
    return {};
}

void TestAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TestAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

    gainDsp.prepare(spec);
    distortionDsp.prepare(spec);
    delayDsp.prepare(spec);
    filterDsp.prepare(spec);
}

void TestAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TestAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TestAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    proportionalParams.active = proportionalParamPointers.activeParam->load();
    proportionalParams.sensorDataType = proportionalParamPointers.sensorDataTypeParam->load();
    proportionalParams.minimum = proportionalParamPointers.minimumParam->load();
    proportionalParams.maximum = proportionalParamPointers.maximumParam->load();
    proportionalParams.multiplier = proportionalParamPointers.multiplierParam->load();
    proportionalController.update(proportionalParams, m_sensorData.getCopy());

    thresholdParams.active = thresholdParamPointers.activeParam->load();
    thresholdParams.sensorDataType = thresholdParamPointers.sensorDataTypeParam->load();
    thresholdParams.threshold = thresholdParamPointers.thresholdParam->load();
    thresholdParams.modifier = thresholdParamPointers.modifierParam->load();
    thresholdController.update(thresholdParams, m_sensorData.getCopy());

    gainParams.active = gainParamPointers.activeParam->load();
    gainParams.gain = gainParamPointers.gainParam->load();
    gainDsp.update(gainParams);

    distortionParams.active = distortionParamPointers.activeParam->load();
    distortionParams.drive = distortionParamPointers.driveParam->load();
    distortionParams.postGain = distortionParamPointers.postGainParam->load();
    distortionParams.mix = distortionParamPointers.mixParam->load();
    distortionParams.type = distortionParamPointers.typeParam->load();
    distortionDsp.update(distortionParams);

    delayParams.active = delayParamPointers.activeParam->load();
    delayParams.feedback = delayParamPointers.feedbackParam->load();
    delayParams.mix = delayParamPointers.mixParam->load();
    delayParams.delayMsL = delayParamPointers.delayMsLParam->load();
    delayParams.delayMsR = delayParamPointers.delayMsRParam->load();
    delayParams.delayType = delayParamPointers.delayTypeParam->load();
    delayDsp.update(delayParams);

    filterParams.active = filterParamPointers.activeParam->load();
    filterParams.mix = filterParamPointers.mixParam->load();
    filterParams.cutoff = filterParamPointers.cutoffParam->load();
    filterParams.resonance = filterParamPointers.resonanceParam->load();
    filterParams.drive = filterParamPointers.driveParam->load();
    filterParams.slopeType = filterParamPointers.slopeTypeParam->load();
    filterParams.passType = filterParamPointers.passTypeParam->load();
    filterDsp.update(filterParams);

    // each dsp uses the same context but it stacks
    // ex: gainDsp.proc(c); reverbDsp.proc(c) <- this c has gain on it 
    // can use unique contexts for parallel processing (ex wet/dry knob)
    // TODO rn this is all sequential -> unintended effect gainParam is change Distortion's drive


    proportionalController.setTargetParameter(m_treeState.getParameter(ParamIDs::Gain::Gain));
    thresholdController.setTargetParameter(m_treeState.getParameter(ParamIDs::Gain::Gain));
    if (proportionalParams.active)    proportionalController.process();
    if (thresholdParams.active)       thresholdController.process();

    if (gainParams.active)            gainDsp.process(context);
    if (distortionParams.active)      distortionDsp.process(context);
    if (delayParams.active)           delayDsp.process(context);
    if (filterParams.active)          filterDsp.process(context);
}

//==============================================================================
bool TestAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TestAudioProcessor::createEditor()
{
    return new TestAudioProcessorEditor (*this);
}

//==============================================================================
void TestAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TestAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TestAudioProcessor();
}
