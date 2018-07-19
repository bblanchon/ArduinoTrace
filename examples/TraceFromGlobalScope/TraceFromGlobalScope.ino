// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018
// MIT License

#include <ArduinoTrace.h>

// Call Serial.begin(9600)
ARDUINOTRACE_INIT(9600);

TRACE();

int someValue = 42;

DUMP(42);

void setup() {}
void loop() {}
