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

    gainParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Gain::Active);
    gainParamPointers.gainParam = m_treeState.getRawParameterValue(ParamIDs::Gain::Gain);

    distortionParamPointers.activeParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Active);
    distortionParamPointers.driveParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Drive);
    distortionParamPointers.postGainParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::PostGain);
    distortionParamPointers.mixParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Mix);
    distortionParamPointers.typeParam = m_treeState.getRawParameterValue(ParamIDs::Distortion::Type);
}

TestAudioProcessor::~TestAudioProcessor()
{
    m_bleManager.stop();
}

//==============================================================================
SensorData TestAudioProcessor::getSensorDataCopy() const
{
    const juce::ScopedLock sl (lock);
    return m_sensorData;
}
BLEManager& TestAudioProcessor::getBLEManager() 
{
    return m_bleManager;
}

void TestAudioProcessor::onOSCBundleReceived(const juce::OSCBundle& bundle)
{
    // Temporary storage and flags
    SensorData tmp = m_sensorData; // start from current values (optional)
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
                    tmp.time = message[0].getFloat32();
                    gotTime = true;
                }
                break;

            case 1: // /audimo/prox
                if (message.size() >= 1 && message[0].isInt32())
                {
                    tmp.proximity = message[0].getInt32();
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
                    tmp.ax = message[0].getFloat32();
                    tmp.ay = message[1].getFloat32();
                    tmp.az = message[2].getFloat32();
                    gotAccel = true;
                }
                break;

            case 4: // /audimo/gyro
                if (message.size() >= 3 && message[0].isFloat32() && message[1].isFloat32() && message[2].isFloat32())
                {
                    tmp.gx = message[0].getFloat32();
                    tmp.gy = message[1].getFloat32();
                    tmp.gz = message[2].getFloat32();
                    gotGyro = true;
                }
                break;

            case 5: // /audimo/euler
                if (message.size() >= 3 && message[0].isFloat32() && message[1].isFloat32() && message[2].isFloat32())
                {
                    tmp.ex = message[0].getFloat32();
                    tmp.ey = message[1].getFloat32();
                    tmp.ez = message[2].getFloat32();
                    gotEuler = true;
                }
                break;

            case 6: // /audimo/mic
                if (message.size() >= 1 && message[0].isFloat32())
                {
                    tmp.mic_rms = message[0].getFloat32();
                    gotMic = true;
                }
                break;

            default:
                // unknown address: ignore
                break;
        }
    }

    // Apply updates under lock (only overwrite fields that were present)
    {
        const juce::ScopedLock sl (lock);
        if (gotTime)        m_sensorData.time = tmp.time;
        if (gotProximity)   m_sensorData.proximity = tmp.proximity;
        // if (gotGesture)     m_sensorData.gesture = tmp.gesture;
        if (gotAccel)       { m_sensorData.ax = tmp.ax; m_sensorData.ay = tmp.ay; m_sensorData.az = tmp.az; }
        if (gotGyro)        { m_sensorData.gx = tmp.gx; m_sensorData.gy = tmp.gy; m_sensorData.gz = tmp.gz; }
        if (gotEuler)       { m_sensorData.ex = tmp.ex; m_sensorData.ey = tmp.ey; m_sensorData.ez = tmp.ez; }
        if (gotMic)         m_sensorData.mic_rms = tmp.mic_rms;
    }
}

void TestAudioProcessor::onOSCMessageReceived(const juce::OSCMessage& message)
{
    auto addr = message.getAddressPattern().toString();
    if (addr == "/audimo/gest") {
        juce::String tmp = m_sensorData.gesture;
        bool gotGesture = false;

        if (message.size() >= 1 && message[0].isString())
        {
            tmp = message[0].getString();
            gotGesture = true;
        }

        // Apply updates under lock (only overwrite fields that were present)
        {
            const juce::ScopedLock sl (lock);
            if (gotGesture)     m_sensorData.gesture = tmp;
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

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

    // float gain = *m_treeState.getRawParameterValue(EffectsTreeState::paramNames::Gain);
    // for (int channel = 0; channel < totalNumInputChannels; ++channel)
    // {
    //     auto* channelData = buffer.getWritePointer (channel);
    //     // ..do something to the data...
    //     buffer.applyGain(channel, 0, buffer.getNumSamples(), gain);
    // }

    juce::dsp::AudioBlock<float> block (buffer);
    juce::dsp::ProcessContextReplacing<float> context (block);

    gainParams.active = gainParamPointers.activeParam->load();
    gainParams.gain = gainParamPointers.gainParam->load();
    gainDsp.update(gainParams);

    distortionParams.active = distortionParamPointers.activeParam->load();
    distortionParams.drive = distortionParamPointers.driveParam->load();
    distortionParams.postGain = distortionParamPointers.postGainParam->load();
    distortionParams.mix = distortionParamPointers.mixParam->load();
    distortionParams.type = distortionParamPointers.typeParam->load();
    distortionDsp.update(distortionParams);

    // each dsp uses the same context but it stacks
    // ex: gainDsp.proc(c); reverbDsp.proc(c) <- this c has gain on it 
    // can use unique contexts for parallel processing (ex wet/dry knob)
    // TODO rn this is all sequential -> unintended effect gainParam is change Distortion's drive
    if (gainParams.active)            gainDsp.process(context);
    if (distortionParams.active)      distortionDsp.process(context);
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
