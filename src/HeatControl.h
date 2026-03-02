#ifndef HEAT_CONTROL_H
#define HEAT_CONTROL_H

#include <Arduino.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
#include "TemperatureSensor.h"

enum HeatControlState
{
    HC_RESET = 0,
    HC_RUN = 1,
    HC_PAUSE = 2,
    HC_DONE = 3
};

/**
 * Controls burner.
 *
 * CIRCUIT CONFIGURATION:
 * HOW IT WORKS:
 */

class HeatControl
{
private:
    int _sensorPin;
    int _relayPin;
    float _tempSetPoint;
    float _temp;
    float _startingTemp;
    const float _tempAllowedDeviation = 1.0; // Maximum deviation from baseline allowed.
    TemperatureSensor tempSensor;
public:
    /**
     * Constructor
     *
     */

   // OneWire oneWire;
   // DallasTemperature dallasTemperature;

    HeatControlState _state;
    void begin();

    HeatControl(
        int sensorPin,
        int relayPin,
        float tempSetPoint = 82.2);

    /**
     * Start heating
     */
    void start();

    /**
     * Stop heating
     */
    void stop();

    /**
     * Reset the heat control state and stop heating
     */
    void reset();

        /**
         * Take temperature reading and update state
         */
    float getTempC();

        /**
         * Update display elements based on current temperature and state. Returns current temperature for convenience.
         */
    float updateUI();
};

#endif
