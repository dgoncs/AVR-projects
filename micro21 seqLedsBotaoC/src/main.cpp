#include <avr/io.h>

#define bitRead(r, n) ((r & (1 << n)) >> n)
#define bitSet(r, n) (r |= (1 << n))
#define bitClear(r, n) (r &= (~(1 << n)))
#define bitToggle(r,n) (r ^= (1 << n))

extern "C"
{
  void delay_1_ms();
}

static uint8_t ledsAtivados;

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
    if (BTA == 1) {
      BTA = 0;
      // borda descida
      estadoBotao = 1;

      // tempo morto
      delay(50);
    } else {
      // borda subida
      BTA = 1;
      // tempo morto
      delay(50);
    }
  }

  return estadoBotao;
}

uint8_t leBotao2() {
  static uint8_t BTA;
  uint8_t estadoBotao = 0;
  uint8_t BT = bitRead(PINC, 2);

  if (BT != BTA) {
    if (BTA == 1) {
      BTA = 0;
      // borda descida
      estadoBotao = 1;

      // tempo morto
      delay(50);
    } else {
      // borda subida
      BTA = 1;
      // tempo morto
      delay(50);
    }
  }

  return estadoBotao;
}

void testeBotao1() {
  if(leBotao1()) {
    PINB = 0b00111100;
  }
}

void testeBotoes() {
  if(leBotao1()) {
    if(ledsAtivados == 4)
      ledsAtivados = 0;
    else
      ledsAtivados++;
  } else if(leBotao2()) {
    if(ledsAtivados == 0)
      ledsAtivados = 4;
    else
      ledsAtivados--;
  } else {
    return;
  }

  switch(ledsAtivados) {
    case 0:
    PORTB = 0b00111100;
    break;

    case 1:
    PORTB = 0b00011100;
    break;

    case 2:
    PORTB = 0b00001100;
    break;

    case 3:
    PORTB = 0b00000100;
    break;

    case 4:
    PORTB = 0b00000000;
    break;
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
    testeBotoes();
  }
}
