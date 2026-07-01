#include <avr/io.h>
#include <lib_botoes.h>
#include <lib_display7s.h>
#include <lib_macros.h>
#include <lib_maquina_estados.h>
#include <lib_timer.h>

void setup()
{
  bitSet(DDRB, PB5);
  bitSet(PORTB, PB5);
  setup_display7seg();
  setup_timer_0();
}

int main()
{
  setup();
  while (1)
  {
    varreduraBotoes();
    maqEstados();
    if (tick_1ms)
    {
      tick_1ms = 0;
    }
  }
}
