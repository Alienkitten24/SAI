#include "SensorData.h"

SensorDataSnapshot SensorData::getCopy() const
{
    const juce::ScopedLock sl(lock);
    
    SensorDataSnapshot snapshot;
    snapshot.time = time;
    snapshot.proximity = proximity;
    snapshot.gesture = gesture;
    snapshot.ax = ax;
    snapshot.ay = ay;
    snapshot.az = az;
    snapshot.gx = gx;
    snapshot.gy = gy;
    snapshot.gz = gz;
    snapshot.ex = ex;
    snapshot.ey = ey;
    snapshot.ez = ez;
    snapshot.mic_rms = mic_rms;
    
    return snapshot;
}

void SensorData::setProximity(int newProximity)
{
    const juce::ScopedLock sl(lock);
    proximity = newProximity;
}

void SensorData::setTime(float newTime)
{
    const juce::ScopedLock sl(lock);
    time = newTime;
}

void SensorData::setGesture(const juce::String& newGesture)
{
    const juce::ScopedLock sl(lock);
    gesture = newGesture;
}

void SensorData::setAcceleration(float newAx, float newAy, float newAz)
{
    const juce::ScopedLock sl(lock);
    ax = newAx;
    ay = newAy;
    az = newAz;
}

void SensorData::setGyro(float newGx, float newGy, float newGz)
{
    const juce::ScopedLock sl(lock);
    gx = newGx;
    gy = newGy;
    gz = newGz;
}

void SensorData::setEuler(float newEx, float newEy, float newEz)
{
    const juce::ScopedLock sl(lock);
    ex = newEx;
    ey = newEy;
    ez = newEz;
}

void SensorData::setMicRms(float newMicRms)
{
    const juce::ScopedLock sl(lock);
    mic_rms = newMicRms;
}

int SensorData::getProximity() const
{
    const juce::ScopedLock sl(lock);
    return proximity;
}

float SensorData::getTime() const
{
    const juce::ScopedLock sl(lock);
    return time;
}

juce::String SensorData::getGesture() const
{
    const juce::ScopedLock sl(lock);
    return gesture;
}

float SensorData::getAccelerationX() const
{
    const juce::ScopedLock sl(lock);
    return ax;
}

float SensorData::getAccelerationY() const
{
    const juce::ScopedLock sl(lock);
    return ay;
}

float SensorData::getAccelerationZ() const
{
    const juce::ScopedLock sl(lock);
    return az;
}

float SensorData::getGyroX() const
{
    const juce::ScopedLock sl(lock);
    return gx;
}

float SensorData::getGyroY() const
{
    const juce::ScopedLock sl(lock);
    return gy;
}

float SensorData::getGyroZ() const
{
    const juce::ScopedLock sl(lock);
    return gz;
}

float SensorData::getEulerX() const
{
    const juce::ScopedLock sl(lock);
    return ex;
}

float SensorData::getEulerY() const
{
    const juce::ScopedLock sl(lock);
    return ey;
}

float SensorData::getEulerZ() const
{
    const juce::ScopedLock sl(lock);
    return ez;
}

float SensorData::getMicRms() const
{
    const juce::ScopedLock sl(lock);
    return mic_rms;
}
