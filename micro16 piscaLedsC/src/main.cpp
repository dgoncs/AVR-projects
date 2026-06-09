#include <avr/io.h>

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

void piscaLeds()
{
  // Acende leds
  PORTB |= (1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2);
  delay(1000);

  // Apaga leds
  PORTB &= ~((1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2));
  delay(1000);
}

void setup()
{
  // pinos PB5-PB2 output
  DDRB |= (1 << DDB5) | (1 << DDB4) | (1 << DDB3) | (1 << DDB2);

  // inicia leds apagados
  PORTB &= ~((1 << PB5) | (1 << PB4) | (1 << PB3) | (1 << PB2));
}

int main()
{
  setup();
  while (1)
  {
    piscaLeds();
  }
}
