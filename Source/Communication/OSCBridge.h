#pragma once

#include <JuceHeader.h>
#include <vector>
#include <cstdint>

class OSCBridge
{
public:
    OSCBridge();
    ~OSCBridge();

    // TODO maybe this should be a std::span not vector?
    void forward(const std::vector<uint8_t>& bytes);

private:
    juce::String m_destAddr;
    int m_destPort;

    juce::OSCSender sender;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCBridge)
};