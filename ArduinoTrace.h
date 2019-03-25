// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018-2019
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

#ifndef ARDUINOTRACE_SERIAL
#define ARDUINOTRACE_SERIAL Serial
#endif

#ifndef ARDUINOTRACE_ENABLE_PROGMEM
#if ARDUINO_ARCH_ESP8266
// avoid error 'XXX causes a section type conflict with YYY'
#define ARDUINOTRACE_ENABLE_PROGMEM 0
#else
#define ARDUINOTRACE_ENABLE_PROGMEM 1
#endif
#endif

namespace ArduinoTrace {
#if ARDUINOTRACE_ENABLE_PROGMEM
typedef const __FlashStringHelper *prefix_type;
#else
typedef const char *prefix_type;
#endif

struct Initializer {
  template <typename TSerial> Initializer(TSerial &serial, int bauds) {
    serial.begin(bauds);
    while (!serial)
      continue;
  }
};

struct Printer {
  template <typename TSerial, typename TValue>
  Printer(TSerial &serial, prefix_type prefix, const TValue &content) {
    serial.print(prefix);
    serial.println(content);
    serial.flush();
  }
};
} // namespace ArduinoTrace

#define ARDUINOTRACE_STRINGIFY(X) #X
#define ARDUINOTRACE_CONCAT(X, Y) X##Y

#if ARDUINOTRACE_ENABLE_PROGMEM
#define ARDUINOTRACE_FLASHIFY(X) F(X)
#else
#define ARDUINOTRACE_FLASHIFY(X) X
#endif

#define ARDUINOTRACE_PRINT(id, prefix, content)                                \
  ArduinoTrace::Printer ARDUINOTRACE_CONCAT(__tracer, id)(                     \
      ARDUINOTRACE_SERIAL, ARDUINOTRACE_FLASHIFY(prefix), content);

#define ARDUINOTRACE_INIITIALIZE(id, bauds)                                    \
  ArduinoTrace::Initializer ARDUINOTRACE_CONCAT(__initializer, id)(            \
      ARDUINOTRACE_SERIAL, bauds);

#define ARDUINOTRACE_TRACE_PREFIX(file, line)                                  \
  file ":" ARDUINOTRACE_STRINGIFY(line) ": "

#define ARDUINOTRACE_DUMP_PREFIX(file, line, variable)                         \
  file ":" ARDUINOTRACE_STRINGIFY(line) ": " #variable " = "

// Initializes the Serial port
//
// Use this macro only if you want to call TRACE() at global scope,
// in other cases, call Serial.begin() in your setup() function, as usual.
#define ARDUINOTRACE_INIT(bauds) ARDUINOTRACE_INIITIALIZE(__COUNTER__, bauds);

// Adds a trace in the Serial port
//
// Call this macro anywhere, including at global scope.
// However, if you use it at global scope, you need to call ARDUINOTRACE_INIT()
// first, otherwise, the Serial port will not be ready.
#define TRACE()                                                                \
  ARDUINOTRACE_PRINT(__COUNTER__,                                              \
                     ARDUINOTRACE_TRACE_PREFIX(__FILE__, __LINE__),            \
                     __PRETTY_FUNCTION__)

// Prints the value of a variable.
//
// This function will print the name and the value of the variable to the
// Serial. If you use it at global scope, you need to call ARDUINOTRACE_INIT()
// first, otherwise, the Serial port will not be ready.
#define DUMP(variable)                                                         \
  ARDUINOTRACE_PRINT(__COUNTER__,                                              \
                     ARDUINOTRACE_DUMP_PREFIX(__FILE__, __LINE__, variable),   \
                     variable)
