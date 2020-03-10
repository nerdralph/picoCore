/* picoCore
 * 2020 Ralph Doncaster open source MIT License
 * 20200301 prototype 
 */
#pragma once

#include <avr/io.h>

#ifdef __cplusplus
extern "C"{
#endif

void setup() asm("setup"); 
void loop() asm("loop");

#ifdef __cplusplus
} // extern "C"
#endif
