; picoCore millis()
; Ralph Doncaster 2020 MIT License open source

; register in IO address space
#define __SFR_OFFSET 0
#include <avr/io.h>

.section .text.millis

.global millis
millis:
    movw r22, r2
    clr r24
    ldi r25, 4
1:  ; x 16 (shift left 4 bits)
    lsl r22
    rol r23
    rol r24
    dec r25
    brne 1b
    ret

; r3:r2 fixed WD counter
.global WDT_vect
WDT_vect:
    in r4, SREG                         ; save SREG
    inc r2
    brne .+2
    inc r3
    out SREG, r4
    reti

.section .init6
    ldi r16, (1<<6)                     ; WD ISR EN = WDTCR bit 6
    out WDTCR, r16                      ; enable WDT interrupt
    sei
