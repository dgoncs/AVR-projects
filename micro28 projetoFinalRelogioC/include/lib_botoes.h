#ifndef LIB_BOTOES_H
#define LIB_BOTOES_H

#include <stdint.h>

extern volatile uint8_t SW1, SW2, SW3;

uint8_t leBotao(uint8_t n);

#endif
