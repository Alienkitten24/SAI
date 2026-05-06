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
    modifier = p.modifier;
    int sensorType = p.sensorDataType;
    if (lastSensorDataType != sensorType) {
        setSensorDataType(sensorType);
    }
}

void ThresholdController::process()
{
    if (!targetParam)
        return;

    // x = raw sensor data 
    // sensorMin, sensorMax = min and max range of sensor values
    // mappedThreshold = maps 0-1 knob to sensor value ranges
    float x, sensorMin, sensorMax, mappedThreshold;
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
        default:
            x = 0.0f;
            sensorMin = 0.0f;
            sensorMax = 1.0f;
            break;
    }
    mappedThreshold = juce::jmap(threshold, 0.0f, 1.0f, sensorMin, sensorMax);

    computeLatch(x, mappedThreshold);
}

void ThresholdController::setTargetParameter(juce::RangedAudioParameter* param)
{
    targetParam = param;
}

// TODO make a second mode where if above threshold it activates and when it drops back below it deactivates
// void ThresholdController::computeMomentary(float x, float mappedThreshold)

void ThresholdController::computeLatch(float x, float mappedThreshold)
{
    float y;

    if (x > mappedThreshold) {
        y = modifier;
        setParameterValue(y);
    }
}

void ThresholdController::setParameterValue(float y)
{
    if (targetParam)
    {
        targetParam->beginChangeGesture();
        targetParam->setValueNotifyingHost(y);
        targetParam->endChangeGesture();
    }
}

void ThresholdController::setSensorDataType(int type)
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

// void ThresholdController::setThresholdType(int type)
// {
//     switch (type) {
//         case ThresholdType::MOMENTARY:  
//             lastType = ThresholdType::MOMENTARY;
//             break;
//         case ThresholdType::LATCH:  
//             lastType = ThresholdType::LATCH;
//             break;
//     }
// }