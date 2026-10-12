#include "HeatControl.h"
#include "ui/ui.h"
#include "lvgl.h"
// #include "TemperatureSensorDallas.h"
#include <math.h>

// ---------------- Constructor ----------------
HeatControl::HeatControl(
    int sensorPin,
    int relayPin,
    float tempSetPoint)
    : _sensorPin(sensorPin), _relayPin(relayPin), _tempSetPoint(tempSetPoint), tempSensorIR() // Initialize IR temperature sensor
{
}

void HeatControl::begin()
{
    pinMode(_sensorPin, INPUT);
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW); // Ensure heater is off
    _state = HeatControlState::HC_DONE;
    _temp = NAN;
    tempSensorIR.begin();
}

void HeatControl::start()
{
    digitalWrite(_relayPin, HIGH);
    _state = HeatControlState::HC_RUN;
}
void HeatControl::stop()
{
    lv_obj_clear_state(ui_switchHeat, LV_STATE_CHECKED);
    lv_slider_set_value(ui_sliderHeat, 0, LV_ANIM_OFF);
    digitalWrite(_relayPin, LOW);
    _state = HeatControlState::HC_DONE;
}
void HeatControl::reset()
{
    stop();
    updateUI(); // Update UI to reflect reset state
}
float HeatControl::getTempC()
{
    _temp = tempSensorIR.getTempC();

    // If set point reached or exceeded, transition to DONE state
    if (_temp >= _tempSetPoint)
    {
        reset();
    }
    return _temp;
}

float HeatControl::updateUI()
{

    if (isnan(_temp)) {

        lv_label_set_text(ui_labelTempValue, "--.-");
        return _temp;
    }

    float tempPercent = 0.0f;  // Currently unused.
    lv_slider_set_value(ui_sliderHeat, int(tempPercent), LV_ANIM_OFF);
    lv_arc_set_value(ui_arcHeat, int(_temp));
    lv_label_set_text(ui_labelTempValue, String(_temp, 1).c_str());

    return _temp;
}