#ifndef LIB_DISPLAY7S_H
#define LIB_DISPLAY7S_H

#include <stdint.h>

extern volatile uint8_t dig7a;
extern volatile uint8_t dig7b;
extern volatile uint8_t dig7c;
extern volatile uint8_t dig7d;

void setup_display7seg();
void display7segWrite(uint8_t b1, uint8_t b2);
void apagaTodosDigitos();
void trocaDisplay();
void taskVarreduraDisplay();

#endif
