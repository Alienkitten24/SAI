#include <iostream>
#include "BLEOSCReceiver.h"

BLEOSCReceiver::BLEOSCReceiver()
{
}

BLEOSCReceiver::~BLEOSCReceiver()
{
    stop();
}

bool BLEOSCReceiver::start(int port)
{
    stop(); // ensure previous connection is closed

    if (!connect(port)) {
        throw std::runtime_error("Cannot connect to UDP port");
    }

    addListener(this);
    return true;
}

void BLEOSCReceiver::stop()
{
    removeListener(this);
    disconnect(); // TODO catch disconnect errors 
}

void BLEOSCReceiver::oscMessageReceived(const juce::OSCMessage& message) 
{
    // if callback function is assigned, use it
    if (onMessageReceived) {
        onMessageReceived(message);
    }
}

void BLEOSCReceiver::oscBundleReceived(const juce::OSCBundle& bundle)
{
    // if callback function is assigned, use it
    if (onBundleReceived) {
        onBundleReceived(bundle);
    }
}