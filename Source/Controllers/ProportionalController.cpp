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
        targetParam->beginChangeGesture();
        targetParam->setValueNotifyingHost(ComputeTargetValue());
        targetParam->endChangeGesture();
    }
}

void ProportionalController::setTargetParameter(juce::RangedAudioParameter* param)
{
    targetParam = param;
}

float ProportionalController::ComputeTargetValue()
{
    // x = raw sensor data 
    // sensorMin, sensorMax = min and max range of sensor values
    // mappedMin, mappedMax = maps 0-1 knobs to sensor value ranges
    // y = the value the parameter should be set to (0 to 1)
    float x, sensorMin, sensorMax, mappedMin, mappedMax, y;
    switch (sensorDataType) {
        case SensorDataType::PROXIMITY:
            x = static_cast<float>(sensorData.proximity);
            sensorMin = 0.0f;
            sensorMax = 65535.0f;
            break;
        case SensorDataType::ACCELERATIONX:
            x = static_cast<float>(sensorData.ax);
            sensorMin = -40.0f;
            sensorMax = 40.0f;
            break;
        case SensorDataType::ACCELERATIONY:
            x = static_cast<float>(sensorData.ay);
            sensorMin = -40.0f;
            sensorMax = 40.0f;
            break;
        case SensorDataType::ACCELERATIONZ:
            x = static_cast<float>(sensorData.az);
            sensorMin = -40.0f;
            sensorMax = 40.0f;
            break;
        case SensorDataType::GYROX:
            x = static_cast<float>(sensorData.gx);
            sensorMin = -2000.0f;
            sensorMax = 2000.0f;
            break;
        case SensorDataType::GYROY:
            x = static_cast<float>(sensorData.gy);
            sensorMin = -2000.0f;
            sensorMax = 2000.0f;
            break;
        case SensorDataType::GYROZ:
            x = static_cast<float>(sensorData.gz);
            sensorMin = -2000.0f;
            sensorMax = 2000.0f;
            break;
        case SensorDataType::EULERX:
            x = static_cast<float>(sensorData.ex);
            sensorMin = 0.0f;
            sensorMax = 360.0f;
            break;
        case SensorDataType::EULERY:
            x = static_cast<float>(sensorData.ey);
            sensorMin = -90.0f;
            sensorMax = 90.0f;
            break;
        case SensorDataType::EULERZ:
            x = static_cast<float>(sensorData.ez);
            sensorMin = -180.0f;
            sensorMax = 180.0f;
            break;
        case SensorDataType::MICRMS:
            x = static_cast<float>(sensorData.mic_rms);
            sensorMin = 0.0f;
            sensorMax = 100'000'000.0f;
            break;
        // default
    }
    mappedMin = juce::jmap(minimum, 0.0f, 1.0f, sensorMin, sensorMax);
    mappedMax = juce::jmap(maximum, 0.0f, 1.0f, sensorMin, sensorMax);
    y = juce::jmap(x, mappedMin, mappedMax, 0.0f, 1.0f);
    return y;
}

void ProportionalController::setSensorDataType(int type)
{
    switch (type) {
        case SensorDataType::PROXIMITY:
            sensorDataType = SensorDataType::PROXIMITY;
            break;
        case SensorDataType::ACCELERATIONX:
            sensorDataType = SensorDataType::ACCELERATIONX;
            break;
        case SensorDataType::ACCELERATIONY:
            sensorDataType = SensorDataType::ACCELERATIONY;
            break;
        case SensorDataType::ACCELERATIONZ:
            sensorDataType = SensorDataType::ACCELERATIONZ;
            break;
        case SensorDataType::GYROX:
            sensorDataType = SensorDataType::GYROX;
            break;
        case SensorDataType::GYROY:
            sensorDataType = SensorDataType::GYROY;
            break;
        case SensorDataType::GYROZ:
            sensorDataType = SensorDataType::GYROZ;
            break;
        case SensorDataType::EULERX:
            sensorDataType = SensorDataType::EULERX;
            break;
        case SensorDataType::EULERY:
            sensorDataType = SensorDataType::EULERY;
            break;
        case SensorDataType::EULERZ:
            sensorDataType = SensorDataType::EULERZ;
            break;
        case SensorDataType::MICRMS:
            sensorDataType = SensorDataType::MICRMS;
            break;

    }

}