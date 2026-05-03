#define __SFR_OFFSET 0
#include "avr/io.h"

.global botaoLed

#define FLAGREG GPIOR0
#define BTA 0

botaoLed:
    ldi r16, 0b00111100
    out DDRB, r16
    ldi r17, 0b00000000
    out DDRC, r17
    ldi r20, 0 ; NEW - Contador de estados - começa em ZERO

read_s1:
    sbis PINC, PC1
    rjmp atual_0

atual_1:
    sbic FLAGREG, BTA
    rjmp read_s1
    rjmp diferentes

atual_0:
    sbis FLAGREG, BTA
    rjmp read_s1

diferentes:
    sbic FLAGREG, BTA
    rjmp proximo_passo

tempo_morto:
    sbi FLAGREG, BTA    ; set BTA = 1
    rjmp delay_1_ms

; estados sequenciais em cada pressionamento de botao
proximo_passo:
    cbi FLAGREG, BTA    ; set BTA = 0

    cpi r20, 0
    breq liga_led_4

    cpi r20, 1
    breq liga_led_3

    cpi r20, 2
    breq liga_led_2

    cpi r20, 3
    breq liga_led_1

    cpi r20, 4
    breq desliga_led_1

    cpi r20, 5
    breq desliga_led_2

    cpi r20, 6
    breq desliga_led_3

    cpi r20, 7
    breq desliga_led_4

liga_led_1:
    ldi r19, 0b00100000
    out PINB, r19
    ldi r20, 0 ; reset dos estados
    rjmp delay_1_ms

desliga_led_1:
    ldi r19, 0b00100000
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

liga_led_2:
    ldi r19, 0b00010000
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

desliga_led_2:
    ldi r19, 0b00010000
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

liga_led_3:
    ldi r19, 0b00001000
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

desliga_led_3:
    ldi r19, 0b00001000
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

liga_led_4:
    ldi r19, 0b00000100
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms

desliga_led_4:
    ldi r19, 0b00000100
    out PINB, r19
    inc r20 ; próximo estado
    rjmp delay_1_ms 

delay_1_ms:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop:
    sbiw r30, 1
    brne loop
    rjmp read_s1
