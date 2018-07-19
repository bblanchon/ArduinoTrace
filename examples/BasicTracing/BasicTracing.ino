// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018
// MIT License

#include <ArduinoTrace.h>

int someValue = 42;

void setup() {
  Serial.begin(9600);
  DUMP(someValue);
}

void loop() {
  TRACE();
  delay(1000);
}
