#include <lib_timer.h>
#include <lib_macros.h>
#include <avr/io.h>

volatile uint8_t SW[4] = {0, 0, 0, 0};

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

void varreduraBotoes()
{
  for (uint8_t i = 1; i <= 3; i++)
  {
    SW[i] = leBotao(i);
  }
}
