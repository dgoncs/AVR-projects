#define __SFR_OFFSET 0
#include "avr/io.h"

.global piscaLeds

piscaLeds:
    ; Configurar pinos
    ldi r16, 0b00111100
    out DDRB, r16

repete:
    ; Ligar LED 1
    ldi r16, 0b11111011
    out PORTB, r16
    call delay_1000_ms

    ; Ligar LED 2
    ldi r16, 0b11110111
    out PORTB, r16
    call delay_1000_ms

    ; Ligar LED 3
    ldi r16, 0b11101111
    out PORTB, r16
    call delay_1000_ms

    ; Ligar LED 4
    ldi r16, 0b11011111
    out PORTB, r16
    call delay_1000_ms

    ; Ligar todos
    ldi r16, 0b11000011
    out PORTB, r16
    call delay_1000_ms

    ; Apaga led 4
    ldi r16, 0b11100011
    out PORTB, r16
    call delay_1000_ms

    ; Apaga led 3
    ldi r16, 0b11110011
    out PORTB, r16
    call delay_1000_ms

    ; Apaga led 2
    ldi r16, 0b11111011
    out PORTB, r16
    call delay_1000_ms

    ; Apaga led 1
    ldi r16, 0b11111111
    out PORTB, r16
    call delay_1000_ms

    rjmp repete

delay_1000_ms:
    ldi r21, 4

delay_250_ms:
loop_3:
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
    dec r21
    brne loop_3
    ret