#define __SFR_OFFSET 0
#include "avr/io.h"

.global botaoLed

botaoLed:
    ldi r16, 0b00000100
    out DDRB, r16
    ldi r17, 0b00000000
    out DDRC, r17

repete:
; Ao pressionar botao:
; simulador: nivel logico 1
; kit fisico: nivel logico 0
    sbic PINC, PC1
    rjmp repete

inverte_led:
    ldi r19, 0b00000100
    out PINB, r19
    rjmp repete
