#ifndef TEMPERATURE_SENSOR_IR_H
#define TEMPERATURE_SENSOR_IR_H

#include <Arduino.h>
#include <DFRobot_MLX90614.h>

/**
 * Reads temperature from DFRobot infrared sensor using serial communication.
 */
class TemperatureSensorIR
{
private:
    static const int READING_AVG_WINDOW = 5;           // Number of recent readings to average for smoothing
    float _recentReading[READING_AVG_WINDOW] = {0.0f}; // Circular buffer to hold recent volume readings for smoothing
    int _recentReadingIndex = 0;
    int _recentReadingCount = 0;
    float _recentReadingSum = 0.0f;
    DFRobot_MLX90614_I2C sensor;

public:
    /**
     * Constructor
     *
     */
    TemperatureSensorIR();

    /**
     * Initialize the sensor
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
