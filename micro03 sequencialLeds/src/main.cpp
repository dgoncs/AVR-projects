#include <Arduino.h>

extern "C" {
  void asmContagem();
  void piscaLeds();
}

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  piscaLeds();
}