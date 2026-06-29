#include <lib_macros.h>
#include <lib_display7s.h>
#include <lib_relogio.h>
#include <lib_maquina_estados.h>
#include <avr/interrupt.h>

static volatile uint16_t contador_0 = 0;
volatile uint8_t tick_1ms = 0;

void setup_timer_0()
{
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;
    OCR0A = 249;

    bitSet(TCCR0A, WGM01);
    bitSet(TCCR0B, CS00);
    bitSet(TCCR0B, CS01);
    bitSet(TIMSK0, OCIE0A);

    sei();
}

ISR(TIMER0_COMPA_vect)
{
    if (estado == 1)
    {
        taskRelogio();
    }
    if (estado == 2)
    {
        taskAjusteMinutos();
    }
    if (estado == 3)
    {
        taskAjusteHoras();
    }
    if (estado == 4)
    {
        taskAlarmeMinutos();
    }
    if (estado == 5)
    {
        taskAlarmeHoras();
    }
    
    taskVarreduraDisplay();
    tick_1ms = 1;
}
