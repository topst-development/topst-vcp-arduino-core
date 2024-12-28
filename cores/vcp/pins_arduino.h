#include "variant_pin.h"

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

//static const uint8_t LED_BUILTIN = 2;                        // Status LED.
#define BUILTIN_LED LED_BUILTIN                              // backward compatibility
#define LED_BUILTIN 316 // K16
#define A0 16 // P.16 (GPIO_AC04)
#define A1 18 // P.18 (GPIO_AC05)

#endif /* Pins_Arduino_h */
