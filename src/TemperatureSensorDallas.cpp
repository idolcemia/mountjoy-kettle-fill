#include "TemperatureSensorDallas.h"

TemperatureSensorDallas::TemperatureSensorDallas(int sensorPin)
    : pin(sensorPin), oneWire(sensorPin), sensors(&oneWire)
{
    deviceCount = 0;
    memset(deviceAddress, 0, sizeof(deviceAddress));
}

void TemperatureSensorDallas::begin()
{
    // pinMode(pin, INPUT);
    sensors.begin();
    deviceCount = sensors.getDeviceCount();
    if (deviceCount > 0 && sensors.getAddress(deviceAddress, 0))
    {
        sensors.setResolution(deviceAddress, 9);
    }
    else
    {
        deviceCount = 0;
        memset(deviceAddress, 0, sizeof(deviceAddress));
    }
    for (int i = 0; i < READING_AVG_WINDOW; ++i)
    {
        _recentReading[i] = 0.0f;
    }
}

float TemperatureSensorDallas::getTempC()
{
    if (deviceCount == 0)
    {
        return NAN; // No sensor found
    }

    sensors.requestTemperatures();
    float tCelsius = sensors.getTempC(deviceAddress);

    if (tCelsius == DEVICE_DISCONNECTED_C)
    {
        return NAN;
    }

    // Update the circular buffer for smoothing
    _recentReadingSum -= _recentReading[_recentReadingIndex];
    _recentReading[_recentReadingIndex] = tCelsius;
    _recentReadingSum += tCelsius;
    _recentReadingIndex = (_recentReadingIndex + 1) % READING_AVG_WINDOW;
    if (_recentReadingCount < READING_AVG_WINDOW)
    {
        _recentReadingCount++;
    }

    return _recentReadingSum / _recentReadingCount;
}
