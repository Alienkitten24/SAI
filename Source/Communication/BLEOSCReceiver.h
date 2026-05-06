#pragma once

#include <JuceHeader.h>
#include <functional>

class BLEOSCReceiver : public juce::OSCReceiver,
                       public juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
public:
    BLEOSCReceiver();
    ~BLEOSCReceiver() override;

    bool start(int port = 9001);
    void stop();

    std::function<void(const juce::OSCBundle&)> onBundleReceived;
    std::function<void(const juce::OSCMessage&)> onMessageReceived;

private:
    void oscBundleReceived(const juce::OSCBundle& bundle) override;
    void oscMessageReceived(const juce::OSCMessage& message) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(BLEOSCReceiver)
};