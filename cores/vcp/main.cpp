#define ARDUINO_MAIN
#include "Arduino.h"

// Weak empty variant initialization function.
// May be redefined by variant files.
void initVariant() __attribute__((weak));
void initVariant() { }

void init() __attribute__((weak));
void init() { }

/*
 * \brief Main entry point of Arduino application
 */
int main(void)
{
  // Board initialization
  init();

  // Init variant
  initVariant();

  setup();

  for (;;) {
    loop();
    serialEventRun();
  }

  return 0;
}
