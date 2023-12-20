#pragma once

#include <cstdint>

#include <Arduino.h>

#include <every.h>

#define ADC_MAX_VAL 8191

class ADC {
public:
  // Constructor with checks for smoothing >= 1
  // optional number of output values (default 256; 8-bit)
  ADC(uint8_t pin, uint16_t smoothing = 100, uint16_t num_values = 256)
      : pin(pin), smoothing(smoothing >= 1 ? smoothing : 1), currentValue(0), num_values(num_values) {
    half_step = (((float)ADC_MAX_VAL) / num_values) / 2;
    pinMode(pin, INPUT);
  }

  // Update the internal value with smoothing
  void update() {
    // Read the analog value
    int rawValue = analogRead(pin);

    // Apply smoothing
    currentValue = ((float)(smoothing - 1) * currentValue + rawValue) / smoothing;
    currentValueMapped =
        map(constrain(currentValue + half_step, 0, ADC_MAX_VAL), 0, ADC_MAX_VAL, 0, num_values - 1);
  }

  // Prime the currentValue by updating it 'smoothing' times
  void prime() {
    currentValue = analogRead(pin);

    for (uint16_t i = 0; i < smoothing; i++) {
      update();
      delay(1);
    }
  }

  // Read and return the (smoothed) currentValue
  uint16_t read() {
    lastReadValue = currentValueMapped;
    return lastReadValue;
  }

  // Check if the value has changed since the last read
  bool changed() {
    return currentValueMapped != lastReadValue;
  }

private:
  uint8_t pin;
  uint16_t smoothing;
  float currentValue;
  uint16_t currentValueMapped;
  uint16_t lastReadValue;
  uint16_t num_values;
  uint16_t half_step;
};
