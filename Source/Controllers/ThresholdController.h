#pragma once

#include <JuceHeader.h>
#include "../Model/ThresholdParams.h"
#include "../Model/SensorData.h"
#include "../Components/Core/KnobComponent.h"

class ThresholdController
{
public: 
    ThresholdController();
    ~ThresholdController();

    void update(const ThresholdParams& p, const SensorDataSnapshot& s);
    void process();
    void setTargetParameter(juce::RangedAudioParameter* param);

    void setSensorDataType(int type);

private:
    juce::RangedAudioParameter* targetParam = nullptr;

    SensorDataSnapshot sensorData;
    int lastSensorDataType;     

    float threshold;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ThresholdController)
};