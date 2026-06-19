#include <avr/io.h>

#define bitRead(r, n) ((r & (1 << n)) >> n)
#define bitSet(r, n) (r |= (1 << n))
#define bitClear(r, n) (r &= (~(1 << n)))
#define bitToggle(r,n) (r ^= (1 << n))

extern "C"
{
  void delay_1_ms();
}

void delay(uint16_t ms)
{
  while (ms)
  {
    delay_1_ms();
    ms--;
  }
}

void inverteLeds()
{
  for (uint8_t i = 5; i >= 2; i--)
  {
    bitToggle(PORTB, i);
  }
}

uint8_t leBotao1() {
  static uint8_t BTA;
  uint8_t estadoBotao = 0;
  uint8_t BT = bitRead(PINC, 1);

  if (BT != BTA) {
    if (BTA) {
      BTA = 0;
      // borda descida
      estadoBotao = 1;

      // tempo morto
      delay(10);
    } else {
      // borda subida
      BTA = 1;
      // tempo morto
      delay(10);
    }
  }

  return estadoBotao;
}

void testeBotao1() {
  if(leBotao1()) {
    PINB = 0b00111100;
  }
}

void setup()
{
  // pinos PB5-PB2 output
  for (uint8_t i = 5; i >= 2; i--)
  {
    bitSet(DDRB, i);
  }

  // inicia leds apagados
  PINB = 0b00111100;

  // pinos PC1-PC3 input
  for (uint8_t i = 1; i <= 3; i++)
  {
    bitClear(DDRC, i);
  }
}

int main()
{
  setup();
  while (1)
  {
    testeBotao1();
  }
}
