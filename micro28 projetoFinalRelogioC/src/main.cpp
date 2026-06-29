#include <lib_timer.h>
#include <lib_macros.h>
#include <lib_display7s.h>
#include <avr/io.h>

uint8_t leBotao(uint8_t n)
{
  uint8_t estadoBotao = 0;
  static uint8_t BTA[4] = {0};
  static uint8_t tempoMorto[4] = {0};
  uint8_t BT = bitRead(PINC, n);

  if (BT != BTA[n])
  {
    if (tick_1ms)
    {
      tempoMorto[n]++;

      if (tempoMorto[n] >= 20)
      {
        tempoMorto[n] = 0;

        if (BTA[n] == 1)
        {
          BTA[n] = 0;
          estadoBotao = 1;
        }
        else
        {
          BTA[n] = 1;
        }
      }
    }
  }
  else
  {
    tempoMorto[n] = 0;
  }

  return estadoBotao;
}

void varreduraBotao()
{
  if (leBotao(1) == 1)
  {
    // Troca de modo / selecao
  }
  if (leBotao(2) == 1)
  {
    // Incrementar
  }
  if (leBotao(3) == 1)
  {
    // Decrementar
  }
}

void maqEstados()
{
  volatile static uint8_t estado = {0};
  volatile static uint8_t SW1, SW2, SW3;

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
    }
    else if (SW3)
    {
      // Decrementa
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
    }
    else if (SW3)
    {
      // Decrementa
    }
    break;
  default:
    estado = 1;
  }
}

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
