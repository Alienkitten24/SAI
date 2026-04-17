#include "ParameterController.h"

#include <iostream>

ParameterController::ParameterController(juce::AudioProcessorValueTreeState& treeState, SensorData& sensorData)
    : treeState(treeState), sensorData(sensorData)
{
}

ParameterController::~ParameterController()
{
}

void ParameterController::update()
{
    // Get a thread-safe copy of sensor data
    SensorDataSnapshot currentData = sensorData.getCopy();

    if (auto* gainParam = treeState.getParameter(ParamIDs::Gain::Gain))
    {
        gainParam->beginChangeGesture();

        float x = static_cast<float>(currentData.proximity);
        float min = treeState.getRawParameterValue(ParamIDs::Controller::Minimum)->load();
        float max = treeState.getRawParameterValue(ParamIDs::Controller::Maximum)->load();

        float y = juce::jmap(x, min, max, 0.0f, 1.0f);

        // std::cout << "prox: " << x << " | y: " << y << std::endl;
        gainParam->setValueNotifyingHost(y);

        gainParam->endChangeGesture();
    }
}