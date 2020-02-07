#pragma once

#include <cstdlib>
#include <iostream>
#include <regex>

void ASSERT_RE(std::string actual, std::string expected) {
  std::regex re(expected);
  if (regex_match(actual, re))
    return;
  std::cerr << "Assertion failed:\n"
               "Expected:\n"
            << expected << "\n"
            << "but got:\n"
            << actual << std::endl;
  std::exit(1);
}
