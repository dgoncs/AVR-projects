.global item_a, item_b   ; Torna as rotinas acessíveis globalmente

item_a:                  ; Label referente a rotina de incremento
    ldi r16, 0           ; Carrega o valor imediato 0 no registrador r16
l1: inc r16              ; Incrementa o valor de r16 em 1 (r16 = r16 + 1)
    cpi r16, 9           ; Compara o valor de r16 com a constante 9
    brne l1              ; Se não for igual (Branch if Not Equal), continua o loop
    rjmp l2              ; Salto relativo incondicional para l2 (quando r16 chega a 9)
l2: dec r16              ; Decrementa o valor de r16 em 1 (r16 = r16 - 1)
    cpi r16, 0           ; Compara o valor de r16 com a constante 0
    brne l2              ; Se não for igual, segue o loop
    ret                  ; Fim da rotina A (quando r16 chega a 0)

item_b:                  ; Label referente a rotina de contagem regressiva
    ldi r16, 9           ; Carrega o valor imediato 9 no registrador r16
l3: dec r16              ; Decrementa o valor de r16 em 1 (r16 = r16 - 1)
    cpi r16, 0           ; Compara o valor de r16 com a constante 0
    brne l3              ; Se não for igual (Branch if Not Equal), continua o loop
    rjmp l4              ; Salto relativo incondicional para l4 (quando r16 chega a 0)
l4: inc r16              ; Incrementa o valor de r16 em 1 (r16 = r16 + 1)
    cpi r16, 9           ; Compara o valor de r16 com a constante 9
    brne l4              ; Se não for igual, segue o loop
    ret                  ; Fim da rotina B (quando r16 chega a 9)
