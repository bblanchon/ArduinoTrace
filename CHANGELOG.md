ArduinoTrace: changelog
=======================

1.1.1 (2019/04/15)
------------------

* Fixed warning: "ARDUINOTRACE_ENABLE" redefined

1.1.0 (2019/03/30)
------------------

* Added `ARDUINOTRACE_SERIAL` to allow changing the serial port (issue #1)
* Reduced the program size by storing each file name only once
* Enabled Flash string on ESP8266
* Print only the filename instead of the full path
  (You can set `ARDUINOTRACE_ENABLE_FULLPATH` to `1` to restore the original behavior)
* Added `ARDUINOTRACE_ENABLE` to enable/disable all traces at once (issue #2)

1.0.0 (2018/07/19)
------------------

Initial release.
