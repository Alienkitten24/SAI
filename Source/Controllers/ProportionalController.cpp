#include "ProportionalController.h"

ProportionalController::ProportionalController()
{
}

ProportionalController::~ProportionalController()
{
}

void ProportionalController::update(const ProportionalParams& p, const SensorDataSnapshot& s)
{
    sensorData = s;
    minimum = p.minimum;
    maximum = p.maximum;
    multiplier = p.multiplier;
    int type = p.sensorDataType;
    if (lastSensorDataType != type)
    {
        setSensorDataType(type);
    }
}

void ProportionalController::process()
{
    if (targetParam)
    {
        float x = static_cast<float>(sensorData.proximity);
        float y = juce::jmap(x, minimum, maximum, 0.0f, 1.0f);

        targetParam->beginChangeGesture();
        targetParam->setValueNotifyingHost(y);
        targetParam->endChangeGesture();
    }
}

void ProportionalController::setTargetParameter(juce::RangedAudioParameter* param)
{
    targetParam = param;
}

void ProportionalController::setSensorDataType(int type)
{

}