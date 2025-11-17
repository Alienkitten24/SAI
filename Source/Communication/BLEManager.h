#pragma once

#include <thread>
#include <atomic>
#include "BLEClient.h"
#include "OSCBridge.h"
#include "BLEOSCReceiver.h"

class BLEManager
{
public:
    BLEManager();
    ~BLEManager();

    void start();
    void stop();

    BLEOSCReceiver& getReceiver();

private:
    BLEClient m_client;
    OSCBridge m_bridge;
    BLEOSCReceiver m_receiver;

    std::thread m_thread;
    std::atomic<bool> m_running;

    void runLoop();
};
