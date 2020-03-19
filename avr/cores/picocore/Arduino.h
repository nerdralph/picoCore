/* picoCore
 * 2020 Ralph Doncaster open source MIT License
 * 20200310 add digital pin functions 
 * 20200301 prototype 
 */
#pragma once

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

// global constants
#define LOW         0
#define HIGH        1

#define LED_BUILTIN 2

typedef uint8_t byte;

enum _pin_mode {
    INPUT = 0,  OUTPUT, INPUT_PULLUP
};

// specify setup and loop symbol names to avoid mangling
void setup() asm("setup"); 
void loop() asm("loop");

extern inline void delayMicroseconds(uint16_t us)
{
    _delay_us(us);
}

extern void delay_16ms(uint16_t count);

extern inline void delay(uint16_t ms)
{
    delay_16ms(ms/16);
    //while (ms--) while (bit_is_set(ADCSRA, ADSC));
}

extern inline void pinMode(uint8_t pin, _pin_mode mode)
{
    if (mode == OUTPUT) DDRB |= (1<<pin);
    else {
        DDRB &= ~(1<<pin);
        if (mode == INPUT_PULLUP) PORTB |= (1<<pin);
    }
}

extern inline void digitalWrite(uint8_t pin, uint8_t val)
{
    if (val)
        PORTB |= (1<<pin);
    else
        PORTB &= ~(1<<pin);
}

extern inline uint8_t digitalRead(uint8_t pin)
{
    return (PINB & (1<<pin)) ? HIGH : LOW;
}

