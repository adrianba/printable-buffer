#!/bin/bash

FIRMWAREPATH=/mnt/c/Users/ade/Documents/Particle/firmware-release-v0.6.3

g++ -std=c++11 -Wno-write-strings -o run-test test.cpp ../src/printable-buffer.cpp $FIRMWAREPATH/wiring/src/spark_wiring_print.cpp -I$FIRMWAREPATH/wiring/inc -I$FIRMWAREPATH/hal/shared && ./run-test