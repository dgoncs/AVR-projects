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
ldi r16, 0 ;contador até 99

bin_dec:
mov r21, r16
ldi r22, 0

loop_bin_dec:
subi r21, 10
brcs carry_set
inc r22
rjmp loop_bin_dec

carry_set:
subi r21, -10

busca_caracteres:
ldi r17, 10 ;repetições: (5ms + 5ms) * 100 = 1s

loop_busca_caracteres:
cpi r17, 0
brne busca_caractere_unidade

;incrementa até 100
inc r16
cpi r16, 100
brne bin_dec

dec r16
rjmp rotina_decrescente

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

dec r17
rjmp loop_busca_caracteres

;r16 = 100
;decresce a 0
rotina_decrescente:
dec r16
cpi r16, 0
breq repete

mov r21, r16
ldi r22, 0

loop_bin_dec_decrescente:
subi r21, 10
brcs carry_set_decrescente
inc r22
rjmp loop_bin_dec_decrescente

carry_set_decrescente:
subi r21, -10

busca_caracteres_decrescente:
ldi r17, 10 ;repete por 1s

loop_busca_caracteres_decrescente:
cpi r17, 0
brne busca_caractere_unidade_decrescente

rjmp rotina_decrescente

busca_caractere_unidade_decrescente:
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

busca_caractere_dezena_decrescente:
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

dec r17
rjmp loop_busca_caracteres_decrescente

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

delay_5_ms:
ldi r20, 5

loop1_delay_5ms:
ldi r31, 4000>>8
ldi r30, 4000&255
loop2_delay_5ms:
sbiw r30, 1
brne loop2_delay_5ms
dec r20
brne loop1_delay_5ms
ret

