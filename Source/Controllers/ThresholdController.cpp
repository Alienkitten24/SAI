#include "ThresholdController.h"

ThresholdController::ThresholdController()
{
}

ThresholdController::~ThresholdController()
{
}

void ThresholdController::update(const ThresholdParams& p, const SensorDataSnapshot& s)
{
    sensorData = s;
    threshold = p.threshold;
    int type = p.sensorDataType;
    if (lastSensorDataType != type)
    {
        setSensorDataType(type);
    }
}

void ThresholdController::process()
{
    if (targetParam)
    {
        float x = static_cast<float>(sensorData.proximity);

        if (x > threshold) {
            float y = 0.5f;

            targetParam->beginChangeGesture();
            targetParam->setValueNotifyingHost(y);
            targetParam->endChangeGesture();
        }
    }
}

void ThresholdController::setTargetParameter(juce::RangedAudioParameter* param)
{
    targetParam = param;
}

void ThresholdController::setSensorDataType(int type)
{

}