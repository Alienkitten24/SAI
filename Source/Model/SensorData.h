#pragma once

#include <JuceHeader.h>

// Data-only struct (copyable, no threading)
struct SensorDataSnapshot
{
    float time = 0.0f;
    int proximity = 0;
    juce::String gesture = "";
    float ax = 0.0f;
    float ay = 0.0f;
    float az = 0.0f;
    float gx = 0.0f;
    float gy = 0.0f;
    float gz = 0.0f;
    float ex = 0.0f;
    float ey = 0.0f;
    float ez = 0.0f;
    float mic_rms = 0.0f;
};

class SensorData
{
public:
    // Thread-safe getter - returns a copy of current data
    SensorDataSnapshot getCopy() const
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

    // Thread-safe setters for individual fields
    void setProximity(int newProximity)
    {
        const juce::ScopedLock sl(lock);
        proximity = newProximity;
    }

    void setTime(float newTime)
    {
        const juce::ScopedLock sl(lock);
        time = newTime;
    }

    void setGesture(const juce::String& newGesture)
    {
        const juce::ScopedLock sl(lock);
        gesture = newGesture;
    }

    void setAcceleration(float newAx, float newAy, float newAz)
    {
        const juce::ScopedLock sl(lock);
        ax = newAx;
        ay = newAy;
        az = newAz;
    }

    void setGyro(float newGx, float newGy, float newGz)
    {
        const juce::ScopedLock sl(lock);
        gx = newGx;
        gy = newGy;
        gz = newGz;
    }

    void setEuler(float newEx, float newEy, float newEz)
    {
        const juce::ScopedLock sl(lock);
        ex = newEx;
        ey = newEy;
        ez = newEz;
    }

    void setMicRms(float newMicRms)
    {
        const juce::ScopedLock sl(lock);
        mic_rms = newMicRms;
    }

    // Getter methods for individual fields
    int getProximity() const
    {
        const juce::ScopedLock sl(lock);
        return proximity;
    }

    float getTime() const
    {
        const juce::ScopedLock sl(lock);
        return time;
    }

    juce::String getGesture() const
    {
        const juce::ScopedLock sl(lock);
        return gesture;
    }

    float getAccelerationX() const
    {
        const juce::ScopedLock sl(lock);
        return ax;
    }

    float getAccelerationY() const
    {
        const juce::ScopedLock sl(lock);
        return ay;
    }

    float getAccelerationZ() const
    {
        const juce::ScopedLock sl(lock);
        return az;
    }

    float getGyroX() const
    {
        const juce::ScopedLock sl(lock);
        return gx;
    }

    float getGyroY() const
    {
        const juce::ScopedLock sl(lock);
        return gy;
    }

    float getGyroZ() const
    {
        const juce::ScopedLock sl(lock);
        return gz;
    }

    float getEulerX() const
    {
        const juce::ScopedLock sl(lock);
        return ex;
    }

    float getEulerY() const
    {
        const juce::ScopedLock sl(lock);
        return ey;
    }

    float getEulerZ() const
    {
        const juce::ScopedLock sl(lock);
        return ez;
    }

    float getMicRms() const
    {
        const juce::ScopedLock sl(lock);
        return mic_rms;
    }

private:
    mutable juce::CriticalSection lock;

    float time = 0.0f;
    int proximity = 0;
    juce::String gesture = "";
    float ax = 0.0f;
    float ay = 0.0f;
    float az = 0.0f;
    float gx = 0.0f;
    float gy = 0.0f;
    float gz = 0.0f;
    float ex = 0.0f;
    float ey = 0.0f;
    float ez = 0.0f;
    float mic_rms = 0.0f;
};

// enum OscID {
//     TIME = 0,
//     PROXIMITY = 1,
//     GESTURE = 2, 
//     ACCELERATION = 3,
//     GYRO = 4, 
//     EULER = 5,
//     MIC = 6
// };