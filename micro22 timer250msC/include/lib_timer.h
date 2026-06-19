#ifndef LIB_TIMER_H
#define LIB_TIMER_H

#include <avr/io.h>
#include <lib_macros.h>
#include <avr/interrupt.h>

extern volatile uint8_t tick_250ms;

void setup_timer_0();

#endif
