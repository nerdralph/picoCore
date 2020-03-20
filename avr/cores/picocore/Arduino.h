/* picoCore
 * 2020 Ralph Doncaster open source MIT License
 * 20200310 add digital pin functions 
 * 20200301 prototype 
 * 20200319 v0.2beta with analogRead/Write & WDT millis()
 */

#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#ifdef __cplusplus
extern "C"{
#endif

// global constants
#define LOW         0
#define HIGH        1

#define LED_BUILTIN 2

typedef uint8_t byte;

void setup();
void loop();

uint32_t millis();

void badArg(const char*) __attribute((error("")));

#define ASSERT_CONST(pin)               \
    if (!__builtin_constant_p(pin))     \
        badArg("pin must be a constant");

extern inline void delayMicroseconds(uint16_t us)
{
    _delay_us(us);
}

extern void delay_16ms(uint16_t count);

extern inline void delay(uint16_t ms)
{
    if (ms > 16)
        delay_16ms(ms/16);
    else
        _delay_us(ms * 1000);
    //while (ms--) while (bit_is_set(ADCSRA, ADSC));
}

enum _pin_mode {
    INPUT = 0,  OUTPUT, INPUT_PULLUP
};

extern inline void pinMode(uint8_t pin, _pin_mode mode)
{ 
    ASSERT_CONST(pin);
    if (mode == OUTPUT) DDRB |= (1<<pin);
    else {
        DDRB &= ~(1<<pin);
        if (mode == INPUT_PULLUP) PORTB |= (1<<pin);
    }
}

extern inline void digitalWrite(uint8_t pin, uint8_t val)
{
    if (__builtin_constant_p(pin)) {
        if (pin > 5) badArg("pin out of range");
    } else {
        badArg("pin must be a constant");
    }

    if (val)
        PORTB |= (1<<pin);
    else
        PORTB &= ~(1<<pin);
}

extern inline uint8_t digitalRead(uint8_t pin)
{
    return (PINB & (1<<pin)) ? HIGH : LOW;
}

// PWM supported on PB0/OCOA & PB1/OC0B
inline void analogWrite(uint8_t pin, uint8_t count)
{
    if (__builtin_constant_p(pin)) {
        if (pin > 1) badArg("pin out of range");
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

enum _analog_ref { DEFAULT = 0, INTERNAL };

inline void analogReference(_analog_ref ref)
{
    //ADMUX = (ADMUX & ~(1 << REFS0)) | (ref << REFS0);
    if (ref == DEFAULT) ADMUX &= ~(1 << REFS0);
    else ADMUX |= (1 << REFS0);
}

enum _analog_pin { A0 = 0, A1, A2, A3, BAD_ANALOG_PIN };

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

