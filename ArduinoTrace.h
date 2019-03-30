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
#if !defined(ARDUINO) || ARDUINO_ARCH_ESP8266
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

constexpr unsigned strlen(const char *str) {
  return str[0] ? strlen(str + 1) + 1 : 0;
}

template <char... chars>
struct string {
#if ARDUINOTRACE_ENABLE_PROGMEM
  const __FlashStringHelper *data() {
    static const char buffer[] PROGMEM = {chars...};
    return reinterpret_cast<const __FlashStringHelper *>(buffer);
  }
#else
  const char *data() {
    static const char buffer[] = {chars...};
    return buffer;
  }
#endif
};

template <typename TSourceString, unsigned length, char... chars>
struct string_maker {
  using result = typename string_maker<TSourceString, length - 1,
                                       TSourceString::data()[length - 1],
                                       chars...>::result;
};

template <typename TSourceString, char... chars>
struct string_maker<TSourceString, 0, chars...> {
  using result = string<chars..., '\0'>;
};

template <typename TStringSource>
using make_string =
    typename string_maker<TStringSource, strlen(TStringSource::data())>::result;

struct Initializer {
  template <typename TSerial>
  Initializer(TSerial &serial, int bauds) {
    serial.begin(bauds);
    while (!serial) continue;
  }
};

template <typename TFilename>
struct Printer {
  template <typename TSerial, typename TValue>
  Printer(TSerial &serial, prefix_type prefix, const TValue &content) {
    serial.print(make_string<TFilename>{}.data());
    serial.print(prefix);
    serial.println(content);
    serial.flush();
  }
};
}  // namespace ArduinoTrace

#define ARDUINOTRACE_STRINGIFY(X) #X
#define ARDUINOTRACE_CONCAT(X, Y) X##Y

#if ARDUINOTRACE_ENABLE_PROGMEM
#define ARDUINOTRACE_FLASHIFY(X) F(X)
#else
#define ARDUINOTRACE_FLASHIFY(X) X
#endif

#define ARDUINOTRACE_PRINT(id, file, prefix, content)                 \
  {                                                                   \
    struct __filename {                                               \
      constexpr static char const *data() { return file; }            \
    };                                                                \
    ArduinoTrace::Printer<__filename> __tracer(                       \
        ARDUINOTRACE_SERIAL, ARDUINOTRACE_FLASHIFY(prefix), content); \
  }

#define ARDUINOTRACE_INIITIALIZE(id, bauds)                         \
  ArduinoTrace::Initializer ARDUINOTRACE_CONCAT(__initializer, id)( \
      ARDUINOTRACE_SERIAL, bauds);

#define ARDUINOTRACE_TRACE_PREFIX(line) ":" ARDUINOTRACE_STRINGIFY(line) ": "

#define ARDUINOTRACE_DUMP_PREFIX(line, variable) \
  ":" ARDUINOTRACE_STRINGIFY(line) ": " #variable " = "

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
#define TRACE()                             \
  ARDUINOTRACE_PRINT(__COUNTER__, __FILE__, \
                     ARDUINOTRACE_TRACE_PREFIX(__LINE__), __PRETTY_FUNCTION__)

// Prints the value of a variable.
//
// This function will print the name and the value of the variable to the
// Serial. If you use it at global scope, you need to call ARDUINOTRACE_INIT()
// first, otherwise, the Serial port will not be ready.
#define DUMP(variable)                      \
  ARDUINOTRACE_PRINT(__COUNTER__, __FILE__, \
                     ARDUINOTRACE_DUMP_PREFIX(__LINE__, variable), variable)
