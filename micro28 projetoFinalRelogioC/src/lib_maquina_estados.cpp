#include <lib_botoes.h>
#include <lib_relogio.h>

volatile uint8_t estado = 0;

void maqEstados()
{
  if (alarme_on >= 1)
    return;

  switch (estado)
  {
  // Normal
  case 1:
    if (SW[1])
    {
      estado = 2;
    }
    break;
  // Ajuste minuto
  case 2:
    if (SW[1])
    {
      estado = 3;
    }
    else if (SW[2])
    {
      // Incrementa
      task_incrementa_minutos_relogio = 1;
    }
    else if (SW[3])
    {
      // Decrementa
      task_decrementa_minutos_relogio = 1;
    }
    break;
  // Ajuste hora
  case 3:
    if (SW[1])
    {
      estado = 4;
    }
    else if (SW[2])
    {
      // Incrementa
      task_incrementa_horas_relogio = 1;
    }
    else if (SW[3])
    {
      // Decrementa
      task_decrementa_horas_relogio = 1;
    }
    break;
  // Ajuste minuto alarme
  case 4:
    if (SW[1])
    {
      estado = 5;
    }
    else if (SW[2])
    {
      // Incrementa
      task_incrementa_minutos_alarme = 1;
    }
    else if (SW[3])
    {
      // Decrementa
      task_decrementa_minutos_alarme = 1;
    }
    break;
  // Ajuste hora alarme
  case 5:
    if (SW[1])
    {
      estado = 1;
    }
    else if (SW[2])
    {
      // Incrementa
      task_incrementa_horas_alarme = 1;
    }
    else if (SW[3])
    {
      // Decrementa
      task_decrementa_horas_alarme = 1;
    }
    break;
  default:
    estado = 1;
  }
}
