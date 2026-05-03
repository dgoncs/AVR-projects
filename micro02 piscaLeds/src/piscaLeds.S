#define __SFR_OFFSET 0
#include "avr/io.h"

.global piscaLeds

piscaLeds:
    ; Configurar pinos
    ldi r16, 0b00111100
    out DDRB, r16

repete:
    ; Ligar LEDs
    ldi r16, 0b00111100
    out PORTB, r16
    call delay_250_ms

    ; Desligar os LEDs
    ldi r16, 0b00000000
    out PORTB, r16
    call delay_250_ms
    rjmp repete

delay_250_ms:
    ; Rotina: loop interno para gerar atraso
    ldi r20, 250

delay_1_ms:
loop_1:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop_2:
    sbiw r30, 1
    brne loop_2
    dec r20
    brne loop_1
    ret