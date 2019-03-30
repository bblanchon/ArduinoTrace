// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018-2019
// MIT License
//

#define ARDUINOTRACE_SERIAL Serial2
#include <ArduinoTrace.h>

static SpyingSerial Serial2;

#include "myassert.h"

void test_trace() {
  Serial2.clear();
  TRACE();
  ASSERT_RE(Serial2.log(),
            "test_alternative_serial.cpp:\\d+: void test_trace\\(\\)\r\n"
            "flush\\(\\)\r\n");
}

void test_dump() {
  Serial2.clear();
  int answer = 42;
  DUMP(answer);
  ASSERT_RE(Serial2.log(),
            "test_alternative_serial.cpp:\\d+: answer = 42\r\n"
            "flush\\(\\)\r\n");
}

void test_init() {
  Serial2.clear();
  ARDUINOTRACE_INIT(9600);
  ASSERT_RE(Serial2.log(), "begin\\(9600\\)\r\n");
}

int main() {
  test_trace();
  test_dump();
  test_init();
}
