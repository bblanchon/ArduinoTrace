// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018
// MIT License

#include <ArduinoTrace.h>

int value = 0;

void setup() {
  Serial.begin(9600);
  TRACE();
}

void loop() {
  value++;
  DUMP(value);
  BREAK();
}
