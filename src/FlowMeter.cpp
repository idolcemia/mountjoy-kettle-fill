#include "FlowMeter.h"
#include "ui/ui.h"
#include "lvgl.h"


void FlowMeter::begin()
{
    pinMode(_sensorPin, INPUT_PULLUP);
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW);   // Ensure valve is closed at startup
    digitalWrite(_sensorPin, HIGH); // Enable internal pull-up resistor
    FlowMeter_instance = this;      // Set the static instance pointer for ISR access
    attachInterrupt(digitalPinToInterrupt(_sensorPin), FlowMeter::isr_wrapper, RISING);

    // Calculate fill time based on fill volume and measured flow rate.
    // Measured flow rate is 0.3856 liters per second.}
    _fillTimeMillis = (unsigned long)(_fillVolumeLiters * 3856); // 
  
}

void FlowMeter::start()
{
    digitalWrite(_relayPin, HIGH);
    _state = FlowMeterState::FLOW_RUN;
    _startTimeMillis = millis();
}
void FlowMeter::stop()
{
    digitalWrite(_relayPin, LOW);

    // tests show dry contact relay takes around 24ms to open or close.
    // testing shows 12VDC 1/2-inch NO Solenoid Valve takes 157ms to open
    // and 315ms to close.
    delay(350); // fully stopped
}
void FlowMeter::reset()
{
    _state = FlowMeterState::FLOW_DONE;
    _pulses = 0;
    lv_obj_clear_state(ui_switchFill, LV_STATE_CHECKED);
    lv_slider_set_value(ui_sliderFill, 0, LV_ANIM_OFF);
    lv_arc_set_value(ui_arcFill, 0);
    stop();
}

FlowMeter *FlowMeter::FlowMeter_instance = nullptr;

void FlowMeter::isr_wrapper(void)
{
    if (FlowMeter_instance != nullptr)
    {
        FlowMeter_instance->isr();
    }
}

void FlowMeter::isr(void)
{
    _pulses++;
}


void FlowMeter::updateUI()
    {
        float fillPercent = _pulses / (float)_maxPulse * 100.0;
        lv_slider_set_value(ui_sliderFill, int(fillPercent), LV_ANIM_OFF);
        lv_arc_set_value(ui_arcFill, int(_pulses/_pulsesPerLiter * 100));
        lv_label_set_text(ui_labelFillValue, String(fillPercent, 1).c_str());
    }