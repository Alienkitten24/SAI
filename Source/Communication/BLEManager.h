#pragma once

#include <thread>
#include <atomic>
#include "BLEClient.h"
#include "OSCBridge.h"
#include "BLEOSCReceiver.h"

class BLEManager : public juce::ChangeBroadcaster
{
public:
    BLEManager();
    ~BLEManager();

    void start();
    void stop();

    BLEOSCReceiver& getReceiver();

    void reportError(const juce::String& err);
    juce::String getLastErrorMessage() const;

private:
    BLEClient m_client;
    OSCBridge m_bridge;
    BLEOSCReceiver m_receiver;

    juce::String m_lastErrorMessage;

    std::thread m_thread;
    std::atomic<bool> m_running;

    void runLoop();
    void onNotify(const std::vector<uint8_t>& msg);
};
