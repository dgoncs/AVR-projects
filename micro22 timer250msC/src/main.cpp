#include <avr/io.h>
#include <lib_macros.h>
#include <lib_timer.h>
#include <avr/interrupt.h>

uint16_t last_led = 0;

void inverteLeds()
{
  for (uint8_t i = 5; i >= 2; i--)
  {
    bitToggle(PORTB, i);
  }
}

void piscaLeds1() {
  if(tick_250ms) {
    tick_250ms = 0;
    inverteLeds();
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
  // PINB = 0b00111100;
    
  // pinos PC1-PC3 input
  for (uint8_t i = 1; i <= 3; i++)
  {
    bitClear(DDRC, i);
  }
  
  setup_timer_0();
  sei();
}

int main()
{
  setup();
  while (1)
  {
    piscaLeds1();
  }
}
