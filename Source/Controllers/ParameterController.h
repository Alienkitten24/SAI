#pragma once

#include <JuceHeader.h>
#include "../Model/SensorData.h"
#include "../Model/EffectsTreeState.h"

class ParameterController
{
public:
    ParameterController(juce::AudioProcessorValueTreeState& treeState, SensorData& sensorData);
    ~ParameterController();

    void update();

protected:
    juce::AudioProcessorValueTreeState& treeState;

    SensorData& sensorData;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParameterController)
};