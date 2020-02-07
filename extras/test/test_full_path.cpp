// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018-2020
// MIT License
//
#define ARDUINOTRACE_ENABLE_FULLPATH 1
#include <ArduinoTrace.h>

#include "myassert.h"

void test_trace() {
  Serial.clear();
  TRACE();
  ASSERT_RE(Serial.log(),
            ".+test_full_path.cpp:\\d+: void test_trace\\(\\)\r\n"
            "flush\\(\\)\r\n");
}

void test_dump() {
  Serial.clear();
  int answer = 42;
  DUMP(answer);
  ASSERT_RE(Serial.log(),
            ".+test_full_path.cpp:\\d+: answer = 42\r\n"
            "flush\\(\\)\r\n");
}

void test_init() {
  Serial.clear();
  ARDUINOTRACE_INIT(9600);
  ASSERT_RE(Serial.log(), "begin\\(9600\\)\r\n");
}

int main() {
  test_trace();
  test_dump();
  test_init();
}
