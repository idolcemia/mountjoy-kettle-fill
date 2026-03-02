#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(
    int analogPin,
    float fixedResistor,
    float r0Resistance,
    float t0Celsius,
    float betaValue,
    bool resistorOnBottom)
{
    pin = analogPin;
    rFixed = fixedResistor;
    r0 = r0Resistance;
    t0 = t0Celsius + 273.15; // Convert to Kelvin
    beta = betaValue;
    adcMax = 1023; // 10-bit ADC on Arduino Giga
    onBottom = resistorOnBottom;
}

void TemperatureSensor::begin()
{
    pinMode(pin, INPUT);
    // analogReference(DEFAULT);
}

float TemperatureSensor::readResistance()
{
    int adc = analogRead(pin);
    float rTherm;

    // Check for invalid ADC readings
    if (adc <= 0 || adc >= adcMax)
    {
        return NAN;
    }

    // Calculate thermistor resistance based on voltage divider configuration
    //
    // The voltage divider can be wired two ways, and the formula changes accordingly:
    //
    // CONFIGURATION 1: Thermistor on BOTTOM (between analog pin and GND)
    //   Vcc --- [Fixed Resistor] --- [Analog Pin] --- [Thermistor] --- GND
    //   Formula: R_therm = R_fixed × (ADC_max / ADC_reading - 1)
    //   Behavior: Temperature ↑ → Resistance ↓ → Voltage ↓ → ADC ↓
    //
    // CONFIGURATION 2: Thermistor on TOP (between Vcc and analog pin)
    //   Vcc --- [Thermistor] --- [Analog Pin] --- [Fixed Resistor] --- GND
    //   Formula: R_therm = R_fixed × (ADC_reading / (ADC_max - ADC_reading))
    //   Behavior: Temperature ↑ → Resistance ↓ → Voltage ↑ → ADC ↑
    //

    // Apply the correct formula based on thermistor position

    rTherm = (onBottom) ? rFixed * ((float)adcMax / (float)adc - 1.0)
                        : rFixed * ((float)adc / ((float)adcMax - (float)adc));

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
    float invT = 1.0 / t0 - (1.0 / beta) * log(rTherm / r0);
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