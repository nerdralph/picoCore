# picoCore
Small Arduino/Wiring core for 8-pin tiny AVRs: ATtiny13 and ATtiny85 series, and preliminary support for the ATtiny84.  Arduino Blink sketch compiled for the ATtiny85 is 64 bytes and for the ATtiny13 is 54 bytes.

I am writing this core from scratch, with code size and efficiency as the main goal.  I am making use of AVR assembler code when the code size and efficiency goals cannot be readily attained with C/C++.  Unlike the official AVR core, picoCore has compile-time checking of many arguments.  Calling digitalWrite(42) will cause a compile error with the message, "pin out of range". 

This core is not 100% compatible with the official [Arduino AVR Core](https://github.com/arduino/ArduinoCore-avr), and 100% compatibility would be impossible given the differences between the tiny AVR MCU supported by picoCore and the ATmega MCU supported by the official core.  If maximum compatibility is more important than minimal code size, then [ATTinyCore](https://github.com/SpenceKonde/ATTinyCore) may be a better choice.

## Development Status
v0.3.0 includes [debugSerial](https://github.com/nerdralph/debugSerial), for basic serial output supporting the most common [Serial.print()](https://www.arduino.cc/reference/en/language/functions/communication/serial/print) data types.

Plans for v0.4.0 include serial bootloader support using [picoboot-lib](https://github.com/nerdralph/picoboot-lib).

## Supported Functions
* [analogRead()](https://www.arduino.cc/en/Reference/AnalogRead)
* [analogReference()](https://www.arduino.cc/en/Reference/AnalogReference)
* [analogWrite()](https://www.arduino.cc/en/Reference/AnalogWrite)
* [delay()](https://www.arduino.cc/en/Reference/Delay) 
* [delayMicroseconds()](https://www.arduino.cc/en/Reference/DelayMicroseconds)
* [digitalRead()](https://www.arduino.cc/en/Reference/DigitalRead)
* [digitalWrite()](https://www.arduino.cc/en/Reference/DigitalWrite)
* [millis()](https://www.arduino.cc/en/Reference/Millis)   *Watchdog timer based. Will increase with steps of 16*
* [pinMode()](https://www.arduino.cc/en/Reference/PinMode)
* [shiftIn()](https://www.arduino.cc/en/Reference/ShiftIn)
* [shiftOut()](https://www.arduino.cc/en/Reference/ShiftOut)

