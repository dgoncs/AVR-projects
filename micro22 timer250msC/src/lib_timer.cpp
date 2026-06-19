#include <avr/io.h>
#include <lib_macros.h>
#include <lib_timer.h>
#include <avr/interrupt.h>

static volatile uint16_t contador = 0;
volatile uint8_t tick_250ms = 0;

void setup_timer_0() {
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;
    OCR0A = 249;

    bitSet(TCCR0A, WGM01);
    bitSet(TCCR0B, CS00);
    bitSet(TCCR0B, CS01);
    bitSet(TIMSK0, OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    contador++;

    if(contador >= 250) {
        contador = 0;
        tick_250ms = 1;
    }
}
