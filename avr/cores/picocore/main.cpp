/* picoCore main
 * 2020 Ralph Doncaster open source MIT License
 * 20200301 prototype 
 */

#include "Arduino.h"


__attribute(( noinline ))
void delay_16ms(uint16_t count)
{
    do {
        _delay_loop_2(16 * F_CPU/1000/4);
    } while (--count);
}

__attribute(( used, section(".init9") ))
int main()
{
    setup();
    while (1) loop();
}
