#define __SFR_OFFSET 0
#include "avr/io.h"

.global botaoLed

#define FLAGREG GPIOR0
#define BTA1 0
#define BTA2 1

botaoLed:
    ldi r16, 0b00111100
    out DDRB, r16
    ldi r17, 0b00000000
    out DDRC, r17
    ldi r20, 0 ; NEW - Contador de estados - começa em ZERO

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
    rjmp proximo_passo

tempo_morto_s1:
    sbi FLAGREG, BTA1    ; set BTA = 1
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
    rjmp desliga_todos

tempo_morto_s2:
    sbi FLAGREG, BTA2    ; set BTA = 1
    call delay_1_ms
    rjmp read_s1

; estados sequenciais em cada pressionamento de botao
proximo_passo:
    cbi FLAGREG, BTA1    ; set BTA = 0
    
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
    call delay_1_ms 
    rjmp read_s2

desliga_led_1:
    ldi r19, 0b00100000
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

liga_led_2:
    ldi r19, 0b00010000
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

desliga_led_2:
    ldi r19, 0b00010000
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

liga_led_3:
    ldi r19, 0b00001000
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

desliga_led_3:
    ldi r19, 0b00001000
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

liga_led_4:
    ldi r19, 0b00000100
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

desliga_led_4:
    ldi r19, 0b00000100
    out PINB, r19
    inc r20 ; próximo estado
    call delay_1_ms 
    rjmp read_s2

desliga_todos:
    ldi r20, 0          ; reset dos estados
    cbi FLAGREG, BTA2   ; set BTA2 = 0
    ldi r19, 0b00000000 ; tudo desligado
    out PORTB, r19
    rjmp read_s1

delay_1_ms:
    ldi r31, 4000>>8
    ldi r30, 4000&255
loop:
    sbiw r30, 1
    brne loop
    ret
