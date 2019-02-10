#include "CircularBuffer.h"
#include <limits.h>

#define REED_PIN 2
#define INTERRUPT_DELTAS_SIZE 100

#define WHEEL_DIAMETER 26 // Inches
#define MAX_SPEED 100 // Km/h

#define wheel_diameter_cm WHEEL_DIAMETER * 2.54
// V [cm/mus] = C [cm] / I [mus]
// V [km/h] = (C [cm] / 100 / 1000) / (I [mus] / 1000 / 1000 / 60 / 60)
// V [km/h] = C [cm] 36000 / I [mus]
#define min_reed_interval wheel_diameter_cm * 36000L / MAX_SPEED
#define delta_over ULONG_MAX - 10000L


CircularBuffer<unsigned long> interrupt_deltas(INTERRUPT_DELTAS_SIZE);
unsigned long last_interrupt_micro = 0;

void setup() {
  Serial.begin(9200);
  pinMode(REED_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(REED_PIN), reed_interrupt, LOW);
  Serial.println(min_reed_interval);
  Serial.println("");
}

void reed_interrupt() {
    unsigned long mus = micros();
    unsigned long delta = mus - last_interrupt_micro;
    if (delta > delta_over) {
        return;
    }
    Serial.print(delta);
    Serial.print("\t");
    Serial.println(min_reed_interval);
    last_interrupt_micro = mus;
}

void loop() {
  delay(100);
}