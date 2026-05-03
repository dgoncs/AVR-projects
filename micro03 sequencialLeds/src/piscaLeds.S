#define __SFR_OFFSET 0
#include "avr/io.h"

.global piscaLeds

piscaLeds:
    ; Configurar pinos
    ldi r16, 0b00111100
    out DDRB, r16

repete:
    ; Ligar 1 LED
    ldi r16, 0b00000100
    out PORTB, r16
    call delay_1000_ms

    ; Ligar 2 LEDs
    ldi r16, 0b00001100
    out PORTB, r16
    call delay_1000_ms

    ; Ligar 3 LEDs
    ldi r16, 0b00011100
    out PORTB, r16
    call delay_1000_ms

    ; Ligar 4 LEDs
    ldi r16, 0b00111100
    out PORTB, r16
    call delay_1000_ms

    ; Desligar 1 LED
    ldi r16, 0b00011100
    out PORTB, r16
    call delay_1000_ms

    ; Desligar 2 LEDs
    ldi r16, 0b00001100
    out PORTB, r16
    call delay_1000_ms

    ; Desligar 3 LEDs
    ldi r16, 0b00000100
    out PORTB, r16
    call delay_1000_ms

    ; Desligar todos os LEDs
    ldi r16, 0b00000000
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