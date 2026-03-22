#include "BLEManager.h"
#include <vector>

#include <iostream>

BLEManager::BLEManager()
{
}

BLEManager::~BLEManager()
{
    stop();
}

void BLEManager::start()
{
    // exchange puts new value (true) and returns old value
    // so if already running, exchange returns true, so we can exit
    if (m_running.exchange(true)) {
        return;
    }

    // set onNotify function pointer
    m_client.onNotify = [&](const std::vector<uint8_t>& msg) {
        this->onNotify(msg);
    };

    try {
        m_client.start();
        m_client.subscribe();
        m_receiver.start(9001);

        m_thread = std::thread([this] { runLoop(); });
        
        // abusing error reporting for demo purposes
        m_lastErrorMessage = "Audimo Connected";
        sendChangeMessage();
    }
    catch (const std::exception& e) {
        std::cout << "catching... " << std::endl;
        reportError(e.what());
        stop();
    }

}

void BLEManager::stop()
{
    m_running = false;
    if (m_thread.joinable()) {
        m_thread.join();
    }
    m_receiver.stop();
}

void BLEManager::reportError(const juce::String& err)
{
    m_lastErrorMessage = err;
    sendChangeMessage();
}

void BLEManager::runLoop()
{
    // currently fetch ASAP, stutters on fail. Could add delay to all reads, consistant hertz
    while (m_running) {
        try {
            SimpleBLE::ByteArray raw = m_client.fetch();
            // TODO this cast does nothing, prolly just make the ByteArray a vector<uint8_t> 
            std::vector<uint8_t> msg = std::vector<uint8_t>(raw.begin(), raw.end());
            m_bridge.forward(msg);
            // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        catch (const std::exception &e) {
            std::cerr << "Error in BLE Loop: " << e.what() << std::endl;
            // Backoff on error to give device time to recover
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }
}

void BLEManager::onNotify(const std::vector<uint8_t>& msg)
{
    if (m_running) {
        // try
        m_bridge.forward(msg);
        // catch maybe?
    }
}

BLEOSCReceiver& BLEManager::getReceiver()
{
    return m_receiver;
}

juce::String BLEManager::getLastErrorMessage() const
{
    return m_lastErrorMessage;
}