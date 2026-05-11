#define __SFR_OFFSET 0
#include "avr/io.h"

#define SDI PB0 // Pin 8
#define SCLK PD7 // Pin 7
#define SLC PD4 // Pin 4
#define FLAGREG GPIOR0
#define BTA1 0
#define BTA2 1

.global display7segmentos

display7segmentos:
    ldi r17, 0b00000000
    out DDRC, r17

    // Configuracao pinos
    sbi DDRB, SDI
    cbi DDRC, PC0
    sbi DDRD, SCLK
    sbi DDRD, SLC

start:
    ldi r16, 0 ;num atual
    rjmp incremento

read_s1:
    sbis PINC, PC1
    rjmp s1_atual_0

s1_atual_1:
    sbic FLAGREG, BTA1
    rjmp read_s2
    rjmp s1_diferentes

s1_atual_0:
    sbis FLAGREG, BTA1
    rjmp read_s2

s1_diferentes:
    sbic FLAGREG, BTA1
    rjmp decremento ;realiza ação de pressionar o botão 1

tempo_morto_s1:
    sbi FLAGREG, BTA1 ;set BTA = 1
    call delay_1_ms

read_s2:
    sbis PINC, PC2
    rjmp s2_atual_0

s2_atual_1:
    sbic FLAGREG, BTA2
    rjmp read_s1
    rjmp s2_diferentes

s2_atual_0:
    sbis FLAGREG, BTA2
    rjmp read_s1

s2_diferentes:
    sbic FLAGREG, BTA2
    rjmp incremento ;realiza ação de pressionar o botão 2

tempo_morto_s2:
    sbi FLAGREG, BTA2 ;set BTA = 1
    call delay_1_ms
    rjmp read_s1

decremento:
    cbi FLAGREG, BTA2 ;set BTA = 0

    ; se r16 = 0 não decrementamos mais
    cpi r16, 0
    breq busca_caractere_unidade

    dec r16
    mov r21, r16
    ldi r22, 0
    rjmp loop_bin_dec

incremento:
    cbi FLAGREG, BTA1 ;set BTA = 0
    
    inc r16
    cpi r16, 100
    breq busca_caractere_unidade

    mov r21, r16
    ldi r22, 0

loop_bin_dec:
    subi r21, 10
    brcs carry_set
    inc r22
    rjmp loop_bin_dec

carry_set:
    subi r21, -10

busca_caractere_unidade:
    // Carrega o endereço da tabela em Z
    ldi ZH, hi8(tabela7seg)
    ldi ZL, lo8(tabela7seg)
    add ZL, r21
    clr r1 ;reinicia o r1
    adc ZH, r1
    lpm r18, Z
    call envia_dados

    ldi r18, 0b00010000
    call envia_dados

    ;pulso latch
    sbi PORTD, SLC
    cbi PORTD, SLC

    call delay_5_ms

busca_caractere_dezena:
    // Carrega o endereço da tabela em Z
    ldi ZH, hi8(tabela7seg)
    ldi ZL, lo8(tabela7seg)
    add ZL, r22
    clr r1 ;reinicia o r1
    adc ZH, r1
    lpm r18, Z
    call envia_dados

    ldi r18, 0b00100000
    call envia_dados

    ;pulso latch
    sbi PORTD, SLC
    cbi PORTD, SLC

    call delay_5_ms
    rjmp read_s1

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

delay_5_ms:
loop_3:
    ldi r20, 5
loop_1:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop_2:
    sbiw r30, 1
    brne loop_2
    dec r20
    brne loop_1
    ret

delay_1_ms:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop_interno:
    sbiw r30, 1
    brne loop_interno
    ret
