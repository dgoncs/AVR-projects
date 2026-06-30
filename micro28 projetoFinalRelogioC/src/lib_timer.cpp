#include <lib_macros.h>
#include <lib_display7s.h>
#include <lib_relogio.h>
#include <lib_maquina_estados.h>
#include <avr/interrupt.h>

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
    switch (estado)
    {
    case 1:
        taskRelogio();
        taskMostraRelogio();
        break;
    case 2:
        taskAjusteMinutos();
        break;
    case 3:
        taskAjusteHoras();
        break;
    case 4:
        taskRelogio();
        taskAlarmeMinutos();
        break;
    case 5:
        taskRelogio();
        taskAlarmeHoras();
        break;
    }

    taskVarreduraDisplay();
    tick_1ms = 1;
}
