#include <Arduino.h>

extern "C" {
  void item_a();
  void item_b();
}

void setup() {
}

void loop() {
  item_a();
  item_b();
}
