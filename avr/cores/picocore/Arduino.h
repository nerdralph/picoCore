/* picoCore
 * 2020 Ralph Doncaster open source MIT License
 * 20200310 add digital pin functions 
 * 20200301 prototype 
 * 20200319 v0.2beta with analogRead/Write & WDT millis()
 * 20200416 v0.2.1 with FlashStringHelper & portxxxxRegister functions
 */

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "constants.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define abs(x) __builtin_abs(x)

#ifdef __cplusplus
class __FlashStringHelper;
#define F(string_literal) (reinterpret_cast<const __FlashStringHelper *>(PSTR(string_literal)))

extern "C"{
#endif

typedef uint8_t byte;

// main in .init9 saves rjmp instruction
__attribute(( section(".init9") )) int main();

void setup();
void loop();

uint32_t millis();

typedef volatile uint8_t* ioregptr;

extern inline ioregptr portOutputRegister(unsigned addr)
    { return (ioregptr) addr; }

extern inline ioregptr portModeRegister(unsigned addr)
    { return (ioregptr) (addr - 1); }

extern inline ioregptr portInputRegister(unsigned addr)
    { return (ioregptr) (addr - 2); }

void badArg(const char*) __attribute((error("")));

#define ASSERT_CONST(pin) \
    if (!__builtin_constant_p(pin)) badArg("pin must be a constant")

__attribute((always_inline))
inline void check_valid_digital_pin(uint8_t pin)
{
    if (__builtin_constant_p(pin)) {
        if (pin >= NUM_DIGITAL_PINS) badArg("pin out of range");
    } else {
        badArg("pin must be a constant");
    }
}

extern inline void delayMicroseconds(uint16_t us)
{
    _delay_us(us);
}

void delay_16ms(uint16_t count);

extern inline void delay(uint16_t ms)
{
    if (ms > 16)
        delay_16ms(ms/16);
    else
        _delay_us(ms * 1000);
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, _bitOrder bitOrder, uint8_t value);
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, _bitOrder bitOrder);

extern inline void pinMode(uint8_t pin, _pin_mode mode)
{ 
    check_valid_digital_pin(pin);

    if (mode == OUTPUT) DDRB |= (1<<pin);
    else {
        DDRB &= ~(1<<pin);
        if (mode == INPUT_PULLUP) PORTB |= (1<<pin);
    }
}

extern inline void digitalWrite(uint8_t pin, uint8_t val)
{
    check_valid_digital_pin(pin);

    if (val)
        PORTB |= (1<<pin);
    else
        PORTB &= ~(1<<pin);
}

extern inline uint8_t digitalRead(uint8_t pin)
{
    check_valid_digital_pin(pin);

    return (PINB & (1<<pin)) ? HIGH : LOW;
}

// PWM supported on PB0/OCOA & PB1/OC0B
inline void analogWrite(uint8_t pin, uint8_t count)
{
    const int BAD_PWM_PIN = 2;
    if (__builtin_constant_p(pin)) {
        if (pin >= BAD_PWM_PIN) badArg("pin out of range");
    } else {
        badArg("pin must be a constant");
    }

    // enable timer, no prescaler
    TCCR0B = (1 << CS00);

    // set pin to output mode
    pinMode(pin, OUTPUT);

    uint8_t FastPWM = (1 << WGM00) | (1 << WGM01);
    if (pin == 0)
    {
        TCCR0A |= FastPWM | (1 << COM0A1);
	    OCR0A = count;
    }
    else
    {
        TCCR0A |= FastPWM | (1 << COM0B1);
	    OCR0B = count;
    }
}

inline void analogReference(_analog_ref ref)
{
    //ADMUX = (ADMUX & ~(1 << REFS0)) | (ref << REFS0);
    if (ref == DEFAULT) ADMUX &= ~(1 << REFS0);
    else ADMUX |= (1 << REFS0);
}

// 9 instr / 18B compiled
// try extern inline instead of always_inline?
__attribute((always_inline))
inline int analogRead(_analog_pin pin)
{
    if (__builtin_constant_p(pin)) {
        if (pin >= BAD_ANALOG_PIN) badArg("pin out of range");
    } else {
        badArg("pin must be a constant");
    }

    // MUX1 & MUX0 are 2 lowest bits in ADMUX
    ADMUX = (ADMUX & 0xFC) | pin;

    // start ADC with /32 prescaler 
    ADCSRA = (1 << ADPS2) | (1 << ADPS0) | (1 << ADSC) | (1 << ADEN);
    while ( bit_is_set(ADCSRA, ADSC) );    
    int result = ADCW;
    ADCSRA = 0;                         // turn off ADC
    return result;
}

#ifdef __cplusplus
} // extern "C"
#endif

