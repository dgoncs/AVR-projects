#define __SFR_OFFSET 0
#include "avr/io.h"

#define SDI PB0 // Pin 8
#define SCLK PD7 // Pin 7
#define SLC PD4 // Pin 4

.global display7segmentos

display7segmentos:
    // Configuracao pinos
    sbi DDRB, SDI
    sbi DDRD, SCLK
    sbi DDRD, SLC

repete:
    ldi r16, 0 ;contador de 0 a f
    ldi r17, 0 ;contador de 0 a f

busca_caractere:
    // Carrega o endereço da tabela em Z
    ldi ZH, hi8(tabela7seg)
    ldi ZL, lo8(tabela7seg)
    add ZL, r16
    clr r1 ;reinicia o r1
    adc ZH, r1
    lpm r18, Z

    call envia_dados
    ldi r18, 0b00010000
    call envia_dados

    ;pulso latch
    sbi PORTD, SLC
    cbi PORTD, SLC

    ;delay 1s
    call delay_1000_ms

    ;repete
    inc r16
    cpi r16, 15
    brne busca_caractere ;loop2

busca_caractere_decrescente:
    // Carrega o endereço da tabela em Z
    ldi ZH, hi8(tabela7seg)
    ldi ZL, lo8(tabela7seg)
    add ZL, r16
    clr r1 ;reinicia o r1
    adc ZH, r1
    lpm r18, Z

    call envia_dados
    ldi r18, 0b00010000
    call envia_dados

    ;pulso latch
    sbi PORTD, SLC
    cbi PORTD, SLC

    ;delay 1s
    call delay_1000_ms

    ;repete
    dec r16
    cpi r16, 0
    brne busca_caractere_decrescente ;loop2
    rjmp repete ;loop1

envia_dados:
    ldi r19, 8 ;contador de bit 8 a 0

envia:
    sbrs r18, 0 ;verifica bit 0 do r18 = 1
    cbi PORTB, SDI
    sbrc r18, 0 ;verifica bit 0 do r18 = 0
    sbi PORTB, SDI

    ;pulso SCLk
    sbi PORTD, SCLK
    cbi PORTD, SCLK

    // Desloca para o proximo bit (r18 >> 1)
    lsr r18
    dec r19
    cpi r19, 0
    brne envia
    ret

tabela7seg:
.byte 0b00000011 ;0
.byte 0b10011111 ;1
.byte 0b00100101 ;2
.byte 0b00001101 ;3
.byte 0b10011001 ;4
.byte 0b01001001 ;5
.byte 0b01000001 ;6
.byte 0b00011111 ;7
.byte 0b00000001 ;8
.byte 0b00001001 ;9
.byte 0b00010001 ;a
.byte 0b11000001 ;b
.byte 0b01100011 ;c
.byte 0b10000101 ;d
.byte 0b01100001 ;e
.byte 0b01110001 ;f  

delay_1000_ms:
    ldi r21, 4

delay_250_ms:
loop_3:
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
