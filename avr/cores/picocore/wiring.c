#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "constants.h"

void delay_16ms(uint16_t count)
{
    do {
        _delay_loop_2(16 * F_CPU/1000/4);
    } while (--count);
}

// shift data in after rising edge of clock, 9 cycles/bit
uint8_t shiftIn(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder)
{  
    uint8_t value;

    if (bitOrder == MSBFIRST) value = 0x01;
    else value = 0x80;

    {
    // use inline asm to access the carry bit (not part of C/C++)
    morebits:
        PORTB |= 1 << clockPin;
        if (bitOrder == MSBFIRST) value <<= 1;
        else value >>= 1;

        if (bit_is_set(PORTB, dataPin))
        { 
            if (bitOrder == MSBFIRST) value |= 0x01;
            else value |= 0x80;
        }  
        PORTB &= ~(1 << clockPin);

        asm goto ("brcc %l[morebits]" :::: morebits);
    }

    return value;
}


// clock data out, 50% duty cycle, 8 cycles/bit
// clock line left high after shiftOut
void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value)
{
    const uint8_t dataMask = 1 << dataPin;
    const uint8_t clkMask = 1 << clockPin;
    uint8_t portbits = (PORTB & ~(dataMask | clkMask));

    // setup first bit in carry & set 9th bit
    if (bitOrder == MSBFIRST)
    {
        value <<= 1;
        value |= 0x01;
    } else {
        value >>= 1;
        value |= 0x80;
    }

    {
    // use inline asm to access the carry bit (not part of C/C++)
    morebits:
        PORTB = portbits; // Clock and data pin low  
        // if (carry == 1) PINB = dataMask;
        asm(
        "brcc .+2                   \n"
        "out %[pinreg], %[dataMask] \n"
        :
        : [pinreg] "I"(_SFR_IO_ADDR(PINB)),
          [dataMask] "r"(dataMask)
        );
        PORTB |= 1 << clockPin;         // Toggle clock pin
        if (bitOrder == MSBFIRST) value <<= 1;
        else value >>= 1;
        // loop until no more bits
        asm goto ("brne %l[morebits]" :: "r"(value) :: morebits);
    }
}

