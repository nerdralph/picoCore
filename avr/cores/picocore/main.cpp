/* picoCore main
 * 2020 Ralph Doncaster open source MIT License
 * 20200301 prototype 
 */

#include "Arduino.h"


__attribute(( section(".init9") ))
int main()
{
    setup();
    while (1) loop();
}
