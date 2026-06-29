#include <lib_timer.h>
#include <lib_macros.h>
#include <lib_display7s.h>
#include <lib_maquina_estados.h>
#include <avr/io.h>

void setup()
{
  setup_display7seg();
  apagaTodosDigitos();
  setup_timer_0();
}

int main()
{
  setup();
  while (1)
  {
    maqEstados();
    if (tick_1ms)
    {
      tick_1ms = 0;
    }
  }
}
