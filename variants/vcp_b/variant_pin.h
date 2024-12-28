/**
 * @file pin_def.h
 * @brief Pin definitions for VCP-G variant
 * 
 * This header file contains the pin mapping and configuration definitions
 * specific to the VCP-G variant board. It defines constants and macros
 * for GPIO pins, peripheral connections, and other hardware-specific settings.
 */

#ifndef PIN_DEF_H
#define PIN_DEF_H

/* Arduino pin name and GPIO pin name mapping */
#define D3  GPIO_GPB(1UL)
#define D5  GPIO_GPB(0UL)
#define D7  GPIO_GPB(4UL)
#define D8  GPIO_GPB(25UL)
#define D10 GPIO_GPB(26UL)
#define D11 GPIO_GPB(6UL)
#define D12 GPIO_GPA(16UL)
#define D13 GPIO_GPB(23UL)
#define D15 GPIO_GPK(11UL)
#define D16 GPIO_GPC(4UL)
#define D18 GPIO_GPC(5UL)
#define D19 GPIO_GPA(24UL)
#define D21 GPIO_GPA(25UL)
#define D22 GPIO_GPK(9UL)
#define D23 GPIO_GPA(27UL)
#define D24 GPIO_GPA(26UL)
#define D26 GPIO_GPC(13UL)
#define D27 GPIO_GPB(3UL)
#define D28 GPIO_GPB(2UL)
#define D29 GPIO_GPA(29UL)
#define D31 GPIO_GPB(19UL)
#define D32 GPIO_GPB(11UL)
#define D33 GPIO_GPC(11UL)
#define D35 GPIO_GPC(15UL)
#define D36 GPIO_GPB(18UL)
#define D37 GPIO_GPA(18UL)
#define D38 GPIO_GPC(14UL)
#define D40 GPIO_GPC(12UL)
#define LED_BUILTIN GPIO_GPK(16UL)

#endif /* PIN_DEF_H */
