# printable-buffer

A Particle library for printable-buffer

## Usage

The `PrintableBuffer` class operates over a buffer that you provide and allows you to use all
the methods available in `Print`. This is especially useful if you want to prepare a string before
using it with an API such as `Particle.publish`.

```cpp
#include "printable-buffer.h"

uint8_t buffer[50];
Printablebuffer pb(buffer, sizeof(buffer));

void setup()
{
    // start() resets the buffer and allows printing from the beginning
    pb.start();
    // successive print calls append to the buffer
    pb.print("Hello,");
    pb.print(" world!");
    // using the PrintableBuffer in places of a (const char*) returns a pointer to the buffer start
    Particle.publish("message", pb, 60, PRIVATE);

    // all the methods of Print are available such as converting floating point numbers
    double d = 2.4567;
    pb.start();
    pb.print(d, 3); // print to 3 decimal places
    Particle.publish("message", pb, 60, PRIVATE);

    // PrintableBuffer.printf does work but internally allocates space on the stack before copying
    // to the destination. Instead use the qprintf method, which prints directly into the buffer.
    pb.start();
    pb.qprintf("Value is %.2f", d); // printf direct to buffer
    Particle.publish("message", pb, 60, PRIVATE);
}

void loop()
{
}
```

## Tests

The unit tests for `PrintableBuffer` are in the [tests](tests) folder. Review these tests for more
information about how the buffer works. The tests ensure that writes do not overrun the buffer even
if an empty buffer (length 0) is provided.

The library always makes sure the string is terminated by a NUL ('\0') character unless a zero
length buffer is provided (where there is nowhere to write to).

## LICENSE

Copyright 2017 Adrian Bateman (https://adebateman.org/)

Licensed under the MIT license (see [LICENSE](license)).
