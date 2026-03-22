#include "OSCBridge.h"
#include <cstdint>
#include <iostream>
#include <span>
#include <bit>

OSCBridge::OSCBridge()
    : m_destAddr("127.0.0.1"), m_destPort(9001)
{
    if (sender.connect(m_destAddr, m_destPort)) {
        // error 
        // TODO handle errors that could happen:
        //      port num invalid (9001 doesn't exist or smth) fix: find new open port
        //      network perms -- OS could prevent packet send due to lack of perms
    }
}

OSCBridge::~OSCBridge()
{
}

// forwardSensors()
// forwardGesture()
// or foward() { if size: encodeGest() else: encodeSensors()}
void OSCBridge::forward(const std::vector<uint8_t>& bytes)
{
    // get the bytes for each data point 
    std::span<const uint8_t> bytesTime = std::span(bytes).subspan(0,4);
    std::span<const uint8_t> bytesProx = std::span(bytes).subspan(4,4);
    std::span<const uint8_t> bytesAccelX = std::span(bytes).subspan(8,4);
    std::span<const uint8_t> bytesAccelY = std::span(bytes).subspan(12,4);
    std::span<const uint8_t> bytesAccelZ = std::span(bytes).subspan(16,4);
    std::span<const uint8_t> bytesGyroX = std::span(bytes).subspan(20,4);
    std::span<const uint8_t> bytesGyroY = std::span(bytes).subspan(24,4);
    std::span<const uint8_t> bytesGyroZ = std::span(bytes).subspan(28,4);
    std::span<const uint8_t> bytesEulerX = std::span(bytes).subspan(32,4);
    std::span<const uint8_t> bytesEulerY = std::span(bytes).subspan(36,4);
    std::span<const uint8_t> bytesEulerZ = std::span(bytes).subspan(40,4);
    std::span<const uint8_t> bytesMicRms = std::span(bytes).subspan(44,4);
    std::span<const uint8_t> bytesGest = std::span(bytes).subspan(48);

    // convert from byte array to primative types
    float time = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesTime.data()));
    int prox = std::bit_cast<int>(*reinterpret_cast<const std::array<uint8_t, 4>*>(bytesProx.data()));
    float accelX = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesAccelX.data()));
    float accelY = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesAccelY.data()));
    float accelZ = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesAccelZ.data()));
    float gyroX = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesGyroX.data()));
    float gyroY = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesGyroY.data()));
    float gyroZ = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesGyroZ.data()));
    float eulerX = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesEulerX.data()));
    float eulerY = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesEulerY.data()));
    float eulerZ = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesEulerZ.data()));
    float micRms = std::bit_cast<float>(*reinterpret_cast<const std::array<uint8_t,4>*>(bytesMicRms.data()));
    juce::String gest = juce::String(reinterpret_cast<const char*>(bytesGest.data(), bytesGest.size()));

    // initialize messages
    juce::OSCMessage msgTime = juce::OSCMessage("/audimo/time");
    juce::OSCMessage msgProx = juce::OSCMessage("/audimo/prox");
    juce::OSCMessage msgAccel = juce::OSCMessage("/audimo/accel");
    juce::OSCMessage msgGyro = juce::OSCMessage("/audimo/gryo");
    juce::OSCMessage msgEuler = juce::OSCMessage("/audimo/euler");
    juce::OSCMessage msgMicRms = juce::OSCMessage("/audimo/mic");
    juce::OSCMessage msgGest = juce::OSCMessage("/audimo/gest");

    // populate arguments
    msgTime.addFloat32(time);
    msgProx.addInt32(prox);
    msgAccel.addFloat32(accelX);
    msgAccel.addFloat32(accelY);
    msgAccel.addFloat32(accelZ);
    msgGyro.addFloat32(gyroX);
    msgGyro.addFloat32(gyroY);
    msgGyro.addFloat32(gyroZ);
    msgEuler.addFloat32(eulerX);
    msgEuler.addFloat32(eulerY);
    msgEuler.addFloat32(eulerZ);
    msgMicRms.addFloat32(micRms);
    msgGest.addString(gest);

    // create and populate bundle
    juce::OSCBundle bundle;
    bundle.addElement(msgTime);
    bundle.addElement(msgProx);
    bundle.addElement(msgAccel);
    bundle.addElement(msgGyro);
    bundle.addElement(msgEuler);
    bundle.addElement(msgMicRms);
    bundle.addElement(msgGest);

    // send
    sender.send(bundle); 
}
