#include <util/delay.h>

void delay_16ms(uint16_t count)
{
    do {
        _delay_loop_2(16 * F_CPU/1000/4);
    } while (--count);
}

