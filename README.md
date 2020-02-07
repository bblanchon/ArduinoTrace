![A quote from Brian Kernighan](extras/img/banner.png)

ArduinoTrace
============

A dead-simple tracing library to debug your Arduino programs.

## Example

All you need to do is call `TRACE()` or `DUMP(variable)`.

```c++
#include <ArduinoTrace.h>

int someValue = 42;

void setup() {
    Serial.begin(9600);
    DUMP(someValue);
}

void loop() {
    TRACE();
}
```

The program above would print:

```text
MyProgram.ino:7: someValue = 42
MyProgram.ino:11: void loop()
MyProgram.ino:11: void loop()
MyProgram.ino:11: void loop()
...
```

## Features

* `TRACE()` prints:
    - filename
    - line number
    - function's name
    - function's parameters
    - template parameters (if any)
* `DUMP(variable)` prints:
    - filename
    - line number
    - variable's name
    - variable's value
* `TRACE()` and `DUMP(variable)` work at global scope, provided that you call `ARDUINOTRACE_INIT()` to initialize the Serial port.
* Flushes the Serial port to make sure that each line is complete
* Uses Flash memory when possible
* Header-only
* Less than 100 lines of code

## A simple recipe to find where the code crashes

1. sprinkle your code with `TRACE()` and `DUMP(variable)`
2. run the program
3. view all traces in the Serial monitor
4. repeat the process until you find the line that causes the crash

## Configuration

| Setting                        | Default  | Description                                                                                                                                                                                                                                       |
|:-------------------------------|:---------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `ARDUINOTRACE_ENABLE`          | `1`      | Determines whether the library is active. If set to `1`, ArduinoTrace is active, and prints traces to the serial port. Set this value to `0` to disable all the traces at once.                                                                   |
| `ARDUINOTRACE_ENABLE_PROGMEM`  | `1`      | Determines whether the strings are stored in Flash or RAM. If defined to `1` (it's the default), ArduinoTrace places the string in the Flash memory to reduce the memory consumption. Only set this value to `0` if you have a compilation issue. |
| `ARDUINOTRACE_ENABLE_FULLPATH` | `0`      | Determines how the filename is written. If set to `1`, ArduinoTrace prints the full path of the file. If set to `0`, ArduinoTrace only prints the filename.                                                                                       |
| `ARDUINOTRACE_SERIAL`          | `Serial` | Define the serial port to use. Change this value to use an alternative serial port, for example, `SerialUSB`.                                                                                                                                     |

To change one of the settings above, you must define the symbol before including the library. For example:

```c++
#define ARDUINOTRACE_ENABLE 0  // Disable all traces
#include <ArduinoTrace.h>
```

## FAQ

#### Is there a performance impact?

Of course, there is! Your program will become fat and slow, so it's essential to use this 
library only when debugging.

You should never use it in production.

You should never commit a program with traces.

#### Does this library replace my logging library?

Absolutely not! Tracing and logging are different things.

Logging is recording (possibly in an SD card) the important things that happen in a program so that we can do a post-mortem analysis, in case something goes wrong.

Tracing is recording every little step to narrow down the area of analysis when you're
fixing a bug. It's a technique that you use for short periods of time, during a debugging session.
Again, you should not commit code that contains traces.

In short: logging is something you do in production, tracing is something you do while debugging.

#### Why not use a debugger instead?

Sometimes, you cannot use a debugger.
In this case, you can always go back to the good-old tracing technique.

#### And what about EspExceptionDecoder?

EspExceptionDecoder is an awesome tool, but unfortunately, the results are not always accurate; you
often see unrelated function names in the stack.
I don't know why that happens (I guess it's due to compiler optimizations), but whatever the reason, it's still good to have a fallback option.

## Tutorials

* [ESP32 / ESP8266 Arduino: Debugging with the ArduinoTrace library](https://techtutorialsx.com/2018/10/11/esp32-esp8266-arduino-debugging-with-the-arduinotrace-library/) (`techtutorialsx.com`)
* [ESP32 / ESP8266 ArduinoTrace: using the TRACE macro](https://techtutorialsx.com/2018/10/12/esp32-esp8266-arduinotrace-using-the-trace-macro/) (`techtutorialsx.com`)

## Want to see how this library works?

[![Youtube video: How to debug any Arduino program with tracing](extras/img/video-thumbnail.png)](https://youtu.be/JHMpszgzWSg)
