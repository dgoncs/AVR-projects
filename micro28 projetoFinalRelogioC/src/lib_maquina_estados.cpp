#include <lib_botoes.h>
#include <lib_relogio.h>

volatile static uint8_t estado = {0};

void maqEstados()
{
  SW1 = leBotao(1);
  SW2 = leBotao(2);
  SW3 = leBotao(3);

  switch (estado)
  {
  // Normal
  case 1:
    if (SW1)
    {
      estado = 2;
    }
    break;
  // Ajuste minuto
  case 2:
    if (SW1)
    {
      estado = 3;
    }
    else if (SW2)
    {
      // Incrementa
    }
    else if (SW3)
    {
      // Decrementa
    }
    break;
  // Ajuste hora
  case 3:
    if (SW1)
    {
      estado = 4;
    }
    else if (SW2)
    {
      // Incrementa
    }
    else if (SW3)
    {
      // Decrementa
    }
    break;
  // Ajuste minuto alarme
  case 4:
    if (SW1)
    {
      estado = 5;
    }
    else if (SW2)
    {
      // Incrementa
      task_incrementa_minutos_alarme = 1;
    }
    else if (SW3)
    {
      // Decrementa
      task_decrementa_minutos_alarme = 1;
    }
    break;
  // Ajuste hora alarme
  case 5:
    if (SW1)
    {
      estado = 1;
    }
    else if (SW2)
    {
      // Incrementa
      task_incrementa_horas_alarme = 1;
    }
    else if (SW3)
    {
      // Decrementa
      task_decrementa_horas_alarme = 1;
    }
    break;
  default:
    estado = 1;
  }
}
