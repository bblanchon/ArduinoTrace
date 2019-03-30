// ArduinoTrace - github.com/bblanchon/ArduinoTrace
// Copyright Benoit Blanchon 2018-2019
// MIT License
//
#define ARDUINOTRACE_ENABLE 0
#include <ArduinoTrace.h>

#include "myassert.h"

void test_trace() {
  Serial.clear();
  TRACE();
  ASSERT_RE(Serial.log(), "");
}

void test_dump() {
  Serial.clear();
  int answer = 42;
  DUMP(answer);
  ASSERT_RE(Serial.log(), "");
}

void test_init() {
  Serial.clear();
  ARDUINOTRACE_INIT(9600);
  ASSERT_RE(Serial.log(), "");
}

int main() {
  test_trace();
  test_dump();
  test_init();
}
