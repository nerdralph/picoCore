# picoCore
Small Arduino/Wiring core for 8-bit tiny AVRs: ATtiny13 and ATtiny25-85 series.  Arduino Blink sketch compiled for the ATtiny85 is 64 bytes and for the ATtiny13 is 54 bytes.

Work in progress as of March 2020

Goals: More than 50% of Arduino sketches run unmodified with picoCore, and 80% run with minor tweaks.

Only those parts of the Arduino/Wiring API which can be implmented efficiently will be supported:

digitalRead, digitalWrite, pinMode - implemented in v0.1

delay, delayMicroseconds - implemented in v0.1 using avr-gcc builtin _delay functions.

v0.2 goals: analogRead and analogWrite

v0.3 goal: Serial.print
