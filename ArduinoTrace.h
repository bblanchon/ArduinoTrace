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

namespace ArduinoTrace {
struct Initializer {
  Initializer(int bauds) {
    Serial.begin(bauds);
    while (!Serial)
      continue;
  }
};

struct Tracer {
  Tracer(const char *location, const char *function) {
    Serial.print(reinterpret_cast<const __FlashStringHelper *>(location));
    Serial.println(function);
    Serial.flush();
  }
};
} // namespace ArduinoTrace

#define TRACE_STR(X) #X
#define TRACE_STRINGIFY(X) TRACE_STR(X)
#define TRACE_CONCAT(X, Y) X##Y
#define TRACE_CONCAT2(X, Y) TRACE_CONCAT(X, Y)

#define TRACE_ADD_TRACER(id)                                                   \
  static const char TRACE_CONCAT(__location, id)[] PROGMEM =                   \
      __FILE__ ":" TRACE_STRINGIFY(__LINE__) ": ";                             \
  ArduinoTrace::Tracer TRACE_CONCAT(__tracer, id)(                             \
      TRACE_CONCAT(__location, id), __PRETTY_FUNCTION__);

// Initializes the Serial port
//
// Use this macro only if you want to call TRACE() at global scope,
// in other cases, call Serial.begin() in your setup() function, as usual.
#define TRACE_INIT(bauds)                                                      \
  ArduinoTrace::Initializer TRACE_CONCAT2(__initializer, __COUNTER__)(bauds);

// Adds a trace in the Serial port
//
// Call this macro anywhere, including at global scope.
// However, if you use it at global scope, you need to call TRACE_INIT() first,
// otherwise, the Serial port will not be ready.
#define TRACE() TRACE_ADD_TRACER(__COUNTER__)
