// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018
// MIT License
//
// A simple tracing macro to debug you program.
//
// Recipe to find where the code crashes:
//  1. sprinkle your code with TRACE()
//  2. run the program
//  3. view all traces in the Serial monitor
//
// Each trace includes the:
//  * the filename
//  * the line number
//  * the current function
//  * the template parameters (if any)

#pragma once

#include <Arduino.h>

#ifndef ARDUINOTRACE_ENABLE_PROGMEM
#if ARDUINO_ARCH_ESP8266
// avoid error 'XXX causes a section type conflict with YYY'
#define ARDUINOTRACE_ENABLE_PROGMEM 0
#else
#define ARDUINOTRACE_ENABLE_PROGMEM 1
#endif
#endif

namespace ArduinoTrace {
struct Initializer {
  Initializer(int bauds) {
    Serial.begin(bauds);
    while (!Serial)
      continue;
  }
};

struct Tracer {
#if ARDUINOTRACE_ENABLE_PROGMEM
  typedef const __FlashStringHelper *location_type;
#else
  typedef const char *location_type;
#endif

  Tracer(location_type location, const char *function) {
    Serial.print(location);
    Serial.println(function);
    Serial.flush();
  }
};
} // namespace ArduinoTrace

#define ARDUINOTRACE_STRINGIFY(X) #X
#define ARDUINOTRACE_STRINGIFY2(X) ARDUINOTRACE_STRINGIFY(X)
#define ARDUINOTRACE_CONCAT(X, Y) X##Y
#define ARDUINOTRACE_CONCAT2(X, Y) ARDUINOTRACE_CONCAT(X, Y)

#if ARDUINOTRACE_ENABLE_PROGMEM
#define ARDUINOTRACE_FLASHIFY(X) F(X)
#else
#define ARDUINOTRACE_FLASHIFY(X) X
#endif

#define ARDUINOTRACE_ADD_TRACER(id)                                            \
  ArduinoTrace::Tracer ARDUINOTRACE_CONCAT(__tracer, id)(                      \
      ARDUINOTRACE_FLASHIFY(__FILE__                                           \
                            ":" ARDUINOTRACE_STRINGIFY2(__LINE__) ": "),       \
      __PRETTY_FUNCTION__);

#define ARDUINOTRACE_ADD_INIITIALIZER(id, bauds)                               \
  ArduinoTrace::Initializer ARDUINOTRACE_CONCAT(__initializer, id)(bauds);

// Initializes the Serial port
//
// Use this macro only if you want to call TRACE() at global scope,
// in other cases, call Serial.begin() in your setup() function, as usual.
#define TRACE_INIT(bauds) ARDUINOTRACE_ADD_INIITIALIZER(__COUNTER__, bauds);

// Adds a trace in the Serial port
//
// Call this macro anywhere, including at global scope.
// However, if you use it at global scope, you need to call TRACE_INIT() first,
// otherwise, the Serial port will not be ready.
#define TRACE() ARDUINOTRACE_ADD_TRACER(__COUNTER__)
