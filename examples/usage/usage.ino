// Example usage for printable-buffer library by Adrian Bateman (https://adebateman.org)

#include "printable-buffer.h"

// Allocate buffer space
uint8_t buffer[50];

// Initialize PrintableBuffer using buffer and size
PrintableBuffer pb(buffer, sizeof(buffer));

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
