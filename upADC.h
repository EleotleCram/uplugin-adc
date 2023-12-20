#pragma once

#include "ADC.h"
#include <uPlugin.h>

class upADC : public uPlugin {
private:
  ADC **adc_pins;

public:
  upADC(ADC **adc_pins) : adc_pins(adc_pins) {}
  void setup();
  void loop();
};
