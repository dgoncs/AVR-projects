#include <lib_timer.h>
#include <lib_macros.h>
#include <avr/io.h>

volatile static uint8_t SW1, SW2, SW3;

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
