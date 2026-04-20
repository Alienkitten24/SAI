#pragma once

#include <JuceHeader.h>

enum SensorDataType {
    PROXIMITY = 0,
    ACCELERATIONX = 1,
    ACCELERATIONY = 2,
    ACCELERATIONZ = 3,
    GYROX = 4,
    GYROY = 5,
    GYROZ = 6,
    EULERX = 7,
    EULERY = 8,
    EULERZ = 9,
    MICRMS = 10
};


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
    SensorDataSnapshot getCopy() const;

    // Thread-safe setters for individual fields
    void setProximity(int newProximity);
    void setTime(float newTime);
    void setGesture(const juce::String& newGesture);
    void setAcceleration(float newAx, float newAy, float newAz);
    void setGyro(float newGx, float newGy, float newGz);
    void setEuler(float newEx, float newEy, float newEz);
    void setMicRms(float newMicRms);

    // Getter methods for individual fields
    int getProximity() const;
    float getTime() const;
    juce::String getGesture() const;
    float getAccelerationX() const;
    float getAccelerationY() const;
    float getAccelerationZ() const;
    float getGyroX() const;
    float getGyroY() const;
    float getGyroZ() const;
    float getEulerX() const;
    float getEulerY() const;
    float getEulerZ() const;
    float getMicRms() const;

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