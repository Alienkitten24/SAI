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

    // std::vector<uint8_t> audimoStringBytes = { 2f 61 75 64 69 6d 6f 00 }; // bytes for "/audimo\n"
    juce::OSCSender sender;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCBridge)
};