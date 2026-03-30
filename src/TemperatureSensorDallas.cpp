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
    return tCelsius;
}
