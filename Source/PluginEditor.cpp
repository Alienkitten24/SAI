/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <thread>

//==============================================================================
TestAudioProcessorEditor::TestAudioProcessorEditor (TestAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), bleSettingsComponent(audioProcessor)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    setResizable (true, false);

    // allows bleSettingsComponent to listen to blemanager errors
    audioProcessor.getBLEManager().addChangeListener(&bleSettingsComponent);

    addAndMakeVisible(bleSettingsComponent);
    bleSettingsComponent.setVisible(false);
    addAndMakeVisible(bleButton);
    bleButton.setButtonText("Bluetooth");
    bleButton.onClick = [this] {
        bleSettingsComponent.setVisible(!bleSettingsComponent.isVisible());
        if (bleSettingsComponent.isVisible()) {
            bleSettingsComponent.toFront(true);
            // audioProcessor.getBLEManager().start();
            std::thread([this] {
                audioProcessor.getBLEManager().start();
            }).detach(); 
        }
    };


    // Lambda: subscribe to OSC bundles from the receiver
    audioProcessor.getBLEManager().getReceiver().onBundleReceived = 
        [this](const juce::OSCBundle& bundle) { onOSCBundleReceived(bundle); };
    audioProcessor.getBLEManager().getReceiver().onMessageReceived = 
        [this](const juce::OSCMessage& message) { onOSCMessageReceived(message); };

    // Set up label
    for (auto& label : labels) {
      addAndMakeVisible(label);
      label.setFont(juce::Font(20.0f));
    }
    
    // Start timer to update label
    startTimerHz(30); // updates 30 times per second
}

TestAudioProcessorEditor::~TestAudioProcessorEditor()
{
    stopTimer();
    audioProcessor.getBLEManager().removeAllChangeListeners();
}

//==============================================================================
void TestAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::Font (15.0f));
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    // g.drawFittedText (String(val), getLocalBounds(), juce::Justification::centred, 1);
}

void TestAudioProcessorEditor::resized()
{
    // Layout labels in two columns
    const int totalLabels = (int)labels.size();
    const int cols = 2;
    const int rows = (totalLabels + cols - 1) / cols;

    auto area = getLocalBounds().reduced (8);
    int labelH = area.getHeight() / rows;
    int colW = area.getWidth() / cols;

    for (int i = 0; i < totalLabels; ++i)
    {
        int r = i % rows;
        int c = i / rows;
        labels[i].setBounds (area.getX() + c * colW, area.getY() + r * labelH, colW - 6, labelH - 4);
    }


    int buttonRow = (totalLabels) % rows; 
    int buttonCol = (totalLabels) / rows; 

    bleButton.setBounds (area.getX() + buttonCol * colW, 
                         area.getY() + buttonRow * labelH, 
                         colW - 6, 
                         labelH - 4);

    // The subwindow should be sized independently of the grid. 
    // Here, we center it and give it a fixed size (e.g., 300x200 pixels).
    const int subW = 300;
    const int subH = 200;

    bleSettingsComponent.setBounds (getWidth()/2 - subW/2, getHeight()/2 - subH/2, subW, subH);
}

// Timer callback to update the label
void TestAudioProcessorEditor::timerCallback() 
{
  // Copy data under lock then update labels on GUI thread
  sensorData copy;
  {
    const juce::ScopedLock sl (dataLock);
    copy = data;
  }

  // Update label texts (match order in sensorData)
  if (labels.size() >= 13) {
    labels[0].setText ("time: " + juce::String (copy.time, 3), juce::dontSendNotification);
    labels[1].setText ("proximity: " + juce::String (copy.proximity), juce::dontSendNotification);
    labels[2].setText ("gesture: " + juce::String (copy.gesture), juce::dontSendNotification);
    labels[3].setText ("ax: " + juce::String (copy.ax, 3), juce::dontSendNotification);
    labels[4].setText ("ay: " + juce::String (copy.ay, 3), juce::dontSendNotification);
    labels[5].setText ("az: " + juce::String (copy.az, 3), juce::dontSendNotification);
    labels[6].setText ("gx: " + juce::String (copy.gx, 3), juce::dontSendNotification);
    labels[7].setText ("gy: " + juce::String (copy.gy, 3), juce::dontSendNotification);
    labels[8].setText ("gz: " + juce::String (copy.gz, 3), juce::dontSendNotification);
    labels[9].setText ("ex: " + juce::String (copy.ex, 3), juce::dontSendNotification);
    labels[10].setText ("ey: " + juce::String (copy.ey, 3), juce::dontSendNotification);
    labels[11].setText ("ez: " + juce::String (copy.ez, 3), juce::dontSendNotification);
    labels[12].setText ("mic_rms: " + juce::String (copy.mic_rms, 3), juce::dontSendNotification);
  }

  repaint();
}

//==============================================================================

// TODO move raw data labels to own seperate component/screen
void TestAudioProcessorEditor::onOSCBundleReceived(const juce::OSCBundle& bundle)
{
    // Temporary storage and flags
    sensorData tmp = data; // start from current values (optional)
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
        const juce::ScopedLock sl (dataLock);
        if (gotTime)        data.time = tmp.time;
        if (gotProximity)   data.proximity = tmp.proximity;
        // if (gotGesture)     data.gesture = tmp.gesture;
        if (gotAccel)       { data.ax = tmp.ax; data.ay = tmp.ay; data.az = tmp.az; }
        if (gotGyro)        { data.gx = tmp.gx; data.gy = tmp.gy; data.gz = tmp.gz; }
        if (gotEuler)       { data.ex = tmp.ex; data.ey = tmp.ey; data.ez = tmp.ez; }
        if (gotMic)         data.mic_rms = tmp.mic_rms;
    }
}

void TestAudioProcessorEditor::onOSCMessageReceived(const juce::OSCMessage& message)
{
    auto addr = message.getAddressPattern().toString();
    if (addr == "/audimo/gest") {
        juce::String tmp = data.gesture;
        bool gotGesture = false;

        if (message.size() >= 1 && message[0].isString())
        {
            tmp = message[0].getString();
            gotGesture = true;
        }

        // Apply updates under lock (only overwrite fields that were present)
        {
            const juce::ScopedLock sl (dataLock);
            if (gotGesture)     data.gesture = tmp;
        }
    }
}
