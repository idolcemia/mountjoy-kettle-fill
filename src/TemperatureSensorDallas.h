#ifndef TEMPERATURE_SENSOR_DALLAS_H
#define TEMPERATURE_SENSOR_DALLAS_H

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

/**
 * Reads temperature from any sensor using a DS18820 chip.
 *  The DS18820 is a digital temperature sensor that communicates over a 1-Wire interface.
 * It provides accurate temperature readings and is commonly used in various applications.
 * This class handles the communication with the DS18820 chip and provides an
 * interface for reading temperature values in Celsius, Fahrenheit, and Kelvin.
 */
class TemperatureSensorDallas
{
private:
    static const int READING_AVG_WINDOW = 10; // Number of recent readings to average for smoothing
    int pin; 
    int deviceCount;
    float _recentReading[READING_AVG_WINDOW] = {0.0f}; // Circular buffer to hold recent volume readings for smoothing
    int _recentReadingIndex = 0;
    int _recentReadingCount = 0;
    float _recentReadingSum = 0.0f;
    DeviceAddress deviceAddress;     
    OneWire oneWire;
    DallasTemperature sensors;

public:
    /**
     * Constructor
     *
     */
    TemperatureSensorDallas(
        int sensorPin); 

    /**
     * Initialize the sensor
     * Sets up the analog pin and reference voltage
     * Call this in setup()
     */
    void begin();

    /**
     * Get temperature in Celsius
     * @return Temperature in °C, or NAN if reading is invalid
     */
    float getTempC();


};

#endif
