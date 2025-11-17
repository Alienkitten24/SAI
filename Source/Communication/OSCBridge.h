#pragma once

#include <JuceHeader.h>
#include <vector>
#include <cstdint>

class OSCBridge
{
public:
    OSCBridge();
    ~OSCBridge();

    void forward(const std::vector<uint8_t>& message);

private:
    juce::DatagramSocket m_socket;
    juce::String m_destAddr;
    int m_destPort;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCBridge)
};