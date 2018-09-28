![A quote from Brian Kernighan](banner.png)

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
E:\MyProgram\MyProgram.ino:7: someValue = 42
E:\MyProgram\MyProgram.ino:11: void loop()
E:\MyProgram\MyProgram.ino:11: void loop()
E:\MyProgram\MyProgram.ino:11: void loop()
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
* `TRACE()` and `DUMP(variable)` works at global scope, provided that you call `ARDUINOTRACE_INIT()` to initialize the Serial port.
* Flushes the Serial port to make sure that each line is complete
* Uses Flash memory when possible
* Header-only
* Less than 100 lines of code

## A simple recipe to find where the code crashes

1. sprinkle your code with `TRACE()` and `DUMP(variable)`
2. run the program
3. view all traces in the Serial monitor
4. repeat the process until you find the line that causes the crash

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

## Want to see how this library works?

[![Youtube video: How to debug any Arduino program with tracing](video-thumbnail.png)](https://youtu.be/JHMpszgzWSg)