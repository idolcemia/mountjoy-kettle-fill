#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(
    int analogPin,
    float fixedResistor,
    float r0Resistance,
    float t0Celsius,
    float betaValue)
{
    pin = analogPin;
    rFixed = fixedResistor;
    r0 = r0Resistance;
    t0 = t0Celsius + 273.15; // Convert to Kelvin
    beta = betaValue;
    adcMax = 1023; // 10-bit ADC on Arduino Giga
}

void TemperatureSensor::begin()
{
    pinMode(pin, INPUT);
    // analogReference(DEFAULT);
}

float TemperatureSensor::readResistance()
{
    int adc = analogRead(pin);

    // Check for invalid ADC readings
    if (adc <= 0 || adc >= adcMax)
    {
        return NAN;
    }

    // Calculate thermistor resistance
    // Circuit: Vcc - Rfixed - A0 - Thermistor - GND
    float rTherm = rFixed * ((float)adcMax / (float)adc - 1.0);

    return rTherm;
}

float TemperatureSensor::getTempC()
{
    float rTherm = readResistance();

    if (isnan(rTherm))
    {
        return NAN;
    }

    // Beta formula: T(K) = 1 / (1/T0 + (1/B) * ln(R/R0))
    float invT = 1.0 / t0 + (1.0 / beta) * log(rTherm / r0);
    float tKelvin = 1.0 / invT;
    float tCelsius = tKelvin - 273.15;

    return tCelsius;
}

float TemperatureSensor::getTempF()
{
    float tempC = getTempC();

    if (isnan(tempC))
    {
        return NAN;
    }

    return tempC * 9.0 / 5.0 + 32.0;
}

float TemperatureSensor::getTempK()
{
    float tempC = getTempC();

    if (isnan(tempC))
    {
        return NAN;
    }

    return tempC + 273.15;
}

bool TemperatureSensor::isValid()
{
    int adc = analogRead(pin);
    return (adc > 0 && adc < adcMax);
}

int TemperatureSensor::getRawADC()
{
    return analogRead(pin);
}