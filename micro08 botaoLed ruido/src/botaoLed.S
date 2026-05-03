#define __SFR_OFFSET 0
#include "avr/io.h"

.global botaoLed

#define FLAGREG GPIOR0
#define BTA 0

botaoLed:
    ldi r16, 0b00001100
    out DDRB, r16
    ldi r17, 0b00000000
    out DDRC, r17

le_s1:
    sbic PINC, PC1
    rjmp le_s2

inverte_led_4:
    ldi r19, 0b00000100
    out PINB, r19

le_s2:
    sbis PINC, PC2
    rjmp atual_0

atual_1:
    sbic FLAGREG, BTA
    rjmp le_s1
    rjmp diferentes

atual_0:
    sbis FLAGREG, BTA
    rjmp le_s1
    rjmp diferentes

diferentes:
    sbic FLAGREG, BTA
    rjmp sim
    rjmp nao

sim:
    cbi FLAGREG, BTA    ; set BTA = 0
    rjmp inverte_led_3

nao:
    sbi FLAGREG, BTA    ; set BTA = 1
    rjmp delay_1_ms
    rjmp le_s1

inverte_led_3:
    ldi r19, 0b00001000
    out PINB, r19
    rjmp delay_1_ms

delay_1_ms:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop:
    sbiw r30, 1
    brne loop
    rjmp le_s1
