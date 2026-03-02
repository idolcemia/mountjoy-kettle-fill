#ifndef FLOW_METER_H
#define FLOW_METER_H

#include <Arduino.h>
#include <lvgl.h>

enum FlowMeterState
{
    FLOW_RESET = 0,
    FLOW_RUN = 1,
    FLOW_PAUSE = 2,
    FLOW_DONE = 3
};

/**
 * Reads flow rate from a water flow sensor.
 *
 * CIRCUIT CONFIGURATION:
 * HOW IT WORKS:
 */

class FlowMeter
{
private:
    int _sensorPin;
    int _relayPin;
    float _fillVolumeLiters = 1.0; // Default to 1 liter, can be set in constructor
    const unsigned long _pulsesPerLiter = 290;  // Measured pulses per liter for the specific flow sensor being used. Adjust as needed based on calibration.    
    static FlowMeter *FlowMeter_instance;

public:
    /**
     * Constructor
     *
     */
    volatile uint16_t _pulses = 0;
    const unsigned long _maxPulse = (unsigned long)(_fillVolumeLiters * _pulsesPerLiter);
    FlowMeterState _state = FLOW_DONE;
    unsigned long _startTimeMillis = 0;

    // Actual fill time is 56 seconds.
    unsigned long _fillTimeMillis = 0; // Will be calculated in begin()

    void begin();

    FlowMeter(
        int sensorPin,
        int relayPin,
        float fillVolumeLiters) : _sensorPin(sensorPin), _relayPin(relayPin), _fillVolumeLiters(fillVolumeLiters)
    {
    }

    float getFillVolume() { return _fillVolumeLiters; }

    /**
     * Start filling
     */
    void start();

    /**
     * Stop filling
     */
    void stop();

    /**
     * Reset the flow meter state and stop filling
     */
    void reset();

    /**
     * Interrupt Service Routine to count pulses from the flow sensor
     */
    void isr();

    // Interrupt service routine
    static void isr_wrapper(void);

    void updateUI();
};

#endif
