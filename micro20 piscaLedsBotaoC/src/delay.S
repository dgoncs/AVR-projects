#define __SFR_OFFSET 0
#include "avr/io.h"

.global delay_1_ms

delay_1_ms:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop_interno:
    sbiw r30, 1
    brne loop_interno
    ret