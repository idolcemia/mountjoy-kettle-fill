#include "HeatControl.h"
#include "ui/ui.h"
#include "lvgl.h"

// ---------------- Constructor ----------------
HeatControl::HeatControl(
    int sensorPin,
    int relayPin,
    float tempSetPoint)
    : _sensorPin(sensorPin), _relayPin(relayPin), _tempSetPoint(tempSetPoint), tempSensor(sensorPin, 4700, 4800, 25, 3950, true)    
{
}

void HeatControl::begin()
{
    pinMode(_sensorPin, INPUT);
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW); // Ensure heater is off
    _state = HeatControlState::HC_DONE;
    TemperatureSensor tempSensor(_sensorPin, 4700, 4800, 25, 3950, true);

   // OneWire oneWire(_sensorPin);
  //  DallasTemperature dallasTemperature(&oneWire);

   // dallasTemperature.begin();
}

void HeatControl::start()
{
    digitalWrite(_relayPin, HIGH);
    _startingTemp = getTempC(); // Capture starting temperature for deviation checks
    _state = HeatControlState::HC_RUN;

}
void HeatControl::stop()
{
    digitalWrite(_relayPin, LOW);
    _state = HeatControlState::HC_DONE;
}
void HeatControl::reset()
{
    stop();
    _startingTemp = 0; // Reset starting temp
    lv_slider_set_value(ui_sliderHeat, 0, LV_ANIM_OFF);
    lv_arc_set_value(ui_arcHeat, 0);

}
float HeatControl::getTempC()
{
   // dallasTemperature.requestTemperatures();

  //  _temp = dallasTemperature.getTempCByIndex(0);
    _temp = tempSensor.getTempC();

    return _temp;
}

float HeatControl::updateUI()
{
    float tempPercent = min(100.0, max(0.0, (_temp - _startingTemp) / (_tempSetPoint - _startingTemp) * 100.0));
    lv_slider_set_value(ui_sliderHeat, int(tempPercent), LV_ANIM_OFF);
    lv_arc_set_value(ui_arcHeat, int(tempPercent));
    lv_label_set_text(ui_labelTempValue, String(_temp, 1).c_str());
}