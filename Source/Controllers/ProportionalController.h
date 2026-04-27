#pragma once

#include <JuceHeader.h>
#include "../Model/ProportionalParams.h"
#include "../Model/SensorData.h"
#include "../Components/Core/KnobComponent.h"

class ProportionalController
{
public: 
    ProportionalController();
    ~ProportionalController();

    void update(const ProportionalParams& p, const SensorDataSnapshot& s);
    void process();
    void setTargetParameter(juce::RangedAudioParameter* param);

private:
    float ComputeTargetValue();
    void setSensorDataType(int type);

    juce::RangedAudioParameter* targetParam = nullptr;

    SensorDataSnapshot sensorData;
    int sensorDataType;
    int lastSensorDataType;     

    float minimum;
    float maximum;
    float multiplier;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ProportionalController)
};