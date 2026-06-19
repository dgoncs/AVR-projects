#include <avr/io.h>
#include <lib_macros.h>
#include <lib_timer.h>
#include <avr/interrupt.h>

static volatile uint16_t contador_0 = 0;
static volatile uint16_t contador_1 = 0;
static volatile uint16_t contador_2 = 0;
static volatile uint16_t contador_3 = 0;
volatile uint8_t tick_250ms = 0;
volatile uint8_t tick_450ms = 0;
volatile uint8_t tick_700ms = 0;
volatile uint8_t tick_850ms = 0;

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
    contador_0++;

    if(contador_0 >= 250) {
        contador_0 = 0;
        tick_250ms = 1;
    }

    contador_1++;

    if(contador_1 >= 450) {
        contador_1 = 0;
        tick_450ms = 1;
    }

    contador_2++;

    if(contador_2 >= 700) {
        contador_2 = 0;
        tick_700ms = 1;
    }

    contador_3++;

    if(contador_3 >= 850) {
        contador_3 = 0;
        tick_850ms = 1;
    }
}
