#include "upADC.h"

#include <every.h>

void upADC::setup() {
  if (adc_pins) {
    for (int i = 0; adc_pins[i]; i++) {
      adc_pins[i]->prime();
    }
  }
}

void upADC::loop() {
  if (adc_pins) {
    for (int i = 0; adc_pins[i]; i++) {
      adc_pins[i]->update();
    }
  }
}
