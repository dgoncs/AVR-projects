#include <avr/io.h>
#include <lib_macros.h>
#include <lib_timer.h>
#include <avr/interrupt.h>

void piscaLed1() {
  if(tick_250ms) {
    tick_250ms = 0;
    bitToggle(PORTB, 5);
  }
}

void piscaLed2() {
  if(tick_450ms) {
    tick_450ms = 0;
    bitToggle(PORTB, 4);
  }
}

void piscaLed3() {
  if(tick_700ms) {
    tick_700ms = 0;
    bitToggle(PORTB, 3);
  }
}

void piscaLed4() {
  if(tick_850ms) {
    tick_850ms = 0;
    bitToggle(PORTB, 2);
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
    piscaLed1();
    piscaLed2();
    piscaLed3();
    piscaLed4();
  }
}
