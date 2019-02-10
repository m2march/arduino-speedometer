#include "vector.h"

#define INTERRUPT_PIN 2

#define interrupt_millis_size 100

int interrupt_millis[interrupt_millis_size];
int interrupt_millis_length = 0;
int interrupt_millis_offset = 0;

CircularBuffer<int> test_vector(interrupt_millis_size);

void setup() {
  Serial.begin(9200);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), reed_interrupt, FALLING);
}

void reed_interrupt() {
  int pos = (interrupt_millis_length + interrupt_millis_offset) % interrupt_millis_size;
  interrupt_millis[pos] = micros();
  
  if (interrupt_millis_length == interrupt_millis_size) {
    interrupt_millis_offset += 1;
    if (interrupt_millis_offset == interrupt_millis_size) {
      interrupt_millis_offset = 0;
    }
  } else {
    interrupt_millis_length += 1;
  }
  
}

void loop() {
  Serial.print(interrupt_millis_offset);
  Serial.print("\t");
  Serial.println(interrupt_millis_length);
  delay(100);
}

