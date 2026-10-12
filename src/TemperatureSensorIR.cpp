#include "TemperatureSensorIR.h"

TemperatureSensorIR::TemperatureSensorIR()
{
}

void TemperatureSensorIR::begin()
{

    sensor.begin();

    for (int i = 0; i < READING_AVG_WINDOW; ++i)
    {
        _recentReading[i] = 0.0f;
    }
}

float TemperatureSensorIR::getTempC()
{

    float tCelsius = sensor.getObjectTempCelsius() ;


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
