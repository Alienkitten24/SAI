#include <iostream>
#include "BLEOSCReceiver.h"

BLEOSCReceiver::BLEOSCReceiver()
{
    start();
}

BLEOSCReceiver::~BLEOSCReceiver()
{
    stop();
}

bool BLEOSCReceiver::start(int port)
{
    stop(); // ensure previous connection is closed

    if (!connect(port)) {
        std::cout << "Error: could not connect to UDP port " << port << std::endl;
        return false;
    }

    addListener(this);
    return true;
}

void BLEOSCReceiver::stop()
{
    removeListener(this);
    disconnect();
}

void BLEOSCReceiver::oscMessageReceived(const juce::OSCMessage& message) 
{
    std::cout << "Should never happen" << std::endl;
}

void BLEOSCReceiver::oscBundleReceived(const juce::OSCBundle& bundle)
{
    if (onBundleReceived) {
        onBundleReceived(bundle);
    }
}