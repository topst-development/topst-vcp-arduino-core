/*
* hsj 20240603 test 
 */

#include <stdint.h>
#include "wiring_constants.h"
#include "gpio.h"

#ifdef PinNameSyntex
// VCP PinName array : Syntax Analysis 
/*
  reserved -> ..
*/
#endif

uint8_t pinCFG(uint32_t vcpPin, uint32_t vcpPinM)
{
  uint8_t ret;
  uint32_t vcpPinMode = vcpPinM << 9;

  if(vcpPinM == OUTPUT)
  {
        switch (vcpPin)
        {
                case  3: GPIO_Config(GPIO_GPB(1UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case  5: GPIO_Config(GPIO_GPB(0UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case  7: GPIO_Config(GPIO_GPB(4UL), (GPIO_FUNC(0UL)|vcpPinMode)); 
                         break;
                case  8: GPIO_Config(GPIO_GPB(25UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 10: GPIO_Config(GPIO_GPB(26UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 11: GPIO_Config(GPIO_GPB(6UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 12: GPIO_Config(GPIO_GPA(16UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 13: GPIO_Config(GPIO_GPB(23UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 15: GPIO_Config(GPIO_GPK(11UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 16: GPIO_Config(GPIO_GPC(4UL), (GPIO_FUNC(0UL)|vcpPinMode)); 
                         break;
                case 18: GPIO_Config(GPIO_GPC(5UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 19: GPIO_Config(GPIO_GPA(24UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 21: GPIO_Config(GPIO_GPA(25UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 22: GPIO_Config(GPIO_GPK(9UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 23: GPIO_Config(GPIO_GPA(27UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 24: GPIO_Config(GPIO_GPA(26UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 26: GPIO_Config(GPIO_GPC(13UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 27: GPIO_Config(GPIO_GPB(3UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 28: GPIO_Config(GPIO_GPB(2UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 29: GPIO_Config(GPIO_GPA(29UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 31: GPIO_Config(GPIO_GPB(19UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 32: GPIO_Config(GPIO_GPB(11UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 33: GPIO_Config(GPIO_GPC(11UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 35: GPIO_Config(GPIO_GPC(15UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 36: GPIO_Config(GPIO_GPB(18UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 37: GPIO_Config(GPIO_GPA(18UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 38: GPIO_Config(GPIO_GPC(14UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                case 40: GPIO_Config(GPIO_GPC(12UL), (GPIO_FUNC(0UL)|vcpPinMode));
                         break;
                /* LED_BUILTIN : GPIO_K16 */
                case 316: GPIO_Config(GPIO_GPK(16UL), (GPIO_FUNC(0UL)|vcpPinMode)); 
                         break;        
                default:
                         break;
        }
  }
  else if(vcpPinM == INPUT)
  {
        switch (vcpPin)
        {
                case  3: GPIO_Config(GPIO_GPB(1UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case  5: GPIO_Config(GPIO_GPB(0UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case  7: GPIO_Config(GPIO_GPB(4UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode)); 
                         break;
                case  8: GPIO_Config(GPIO_GPB(25UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 10: GPIO_Config(GPIO_GPB(26UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 11: GPIO_Config(GPIO_GPB(6UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 12: GPIO_Config(GPIO_GPA(16UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 13: GPIO_Config(GPIO_GPB(23UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 15: GPIO_Config(GPIO_GPK(11UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 16: GPIO_Config(GPIO_GPC(4UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode)); 
                         break;
                case 18: GPIO_Config(GPIO_GPC(5UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 19: GPIO_Config(GPIO_GPA(24UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 21: GPIO_Config(GPIO_GPA(25UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 22: GPIO_Config(GPIO_GPK(9UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 23: GPIO_Config(GPIO_GPA(27UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 24: GPIO_Config(GPIO_GPA(26UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 26: GPIO_Config(GPIO_GPC(13UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 27: GPIO_Config(GPIO_GPB(3UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 28: GPIO_Config(GPIO_GPB(2UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 29: GPIO_Config(GPIO_GPA(29UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 31: GPIO_Config(GPIO_GPB(19UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 32: GPIO_Config(GPIO_GPB(11UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 33: GPIO_Config(GPIO_GPC(11UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 35: GPIO_Config(GPIO_GPC(15UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 36: GPIO_Config(GPIO_GPB(18UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 37: GPIO_Config(GPIO_GPA(18UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 38: GPIO_Config(GPIO_GPC(14UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                case 40: GPIO_Config(GPIO_GPC(12UL), (GPIO_FUNC(0UL)|GPIO_INPUTBUF_EN|GPIO_PULLDN|vcpPinMode));
                         break;
                /* LED_BUILTIN : GPIO_K16 */
                case 316: GPIO_Config(GPIO_GPK(16UL), (GPIO_FUNC(0UL)|vcpPinMode)); 
                         break;        
                default:
                         break;
        }
  }

  return ret;
}

uint8_t pinSET(uint32_t vcpPin, uint32_t vcpValue)
{
  uint8_t ret;

  switch (vcpPin)
  {
    case 3: GPIO_Set(GPIO_GPB(1UL), vcpValue); 
            break;
    case 5: GPIO_Set(GPIO_GPB(0UL), vcpValue);
            break;
    case 7: GPIO_Set(GPIO_GPB(4UL), vcpValue); 
            break;
    case 8: GPIO_Set(GPIO_GPB(25UL), vcpValue);
            break;
    case 10: GPIO_Set(GPIO_GPB(26UL), vcpValue);
            break;
    case 11: GPIO_Set(GPIO_GPB(6UL), vcpValue); 
            break;
    case 12: GPIO_Set(GPIO_GPA(16UL), vcpValue); 
            break;
    case 13: GPIO_Set(GPIO_GPB(23UL), vcpValue); 
            break;
    case 15: GPIO_Set(GPIO_GPK(11UL), vcpValue); 
            break;
    case 16: GPIO_Set(GPIO_GPC(4UL), vcpValue);
            break;
    case 18: GPIO_Set(GPIO_GPC(5UL), vcpValue);
            break;
    case 19: GPIO_Set(GPIO_GPA(24UL), vcpValue);
            break;
    case 21: GPIO_Set(GPIO_GPA(25UL), vcpValue);
            break;
    case 22: GPIO_Set(GPIO_GPK(9UL), vcpValue); 
            break;
    case 23: GPIO_Set(GPIO_GPA(27UL), vcpValue);
            break;
    case 24: GPIO_Set(GPIO_GPA(26UL), vcpValue);
            break;
    case 26: GPIO_Set(GPIO_GPC(13UL), vcpValue);
            break;
    case 27: GPIO_Set(GPIO_GPB(3UL), vcpValue); 
            break;
    case 28: GPIO_Set(GPIO_GPB(2UL), vcpValue);
            break;
    case 29: GPIO_Set(GPIO_GPA(29UL), vcpValue); 
            break;
    case 31: GPIO_Set(GPIO_GPB(19UL), vcpValue); 
            break;
    case 32: GPIO_Set(GPIO_GPB(11UL), vcpValue); 
            break;
    case 33: GPIO_Set(GPIO_GPC(11UL), vcpValue); 
            break;
    case 35: GPIO_Set(GPIO_GPC(15UL), vcpValue);
            break;
    case 36: GPIO_Set(GPIO_GPB(18UL), vcpValue); 
            break;
    case 37: GPIO_Set(GPIO_GPA(18UL), vcpValue); 
            break;
    case 38: GPIO_Set(GPIO_GPC(14UL), vcpValue);
            break;
    case 40: GPIO_Set(GPIO_GPC(12UL), vcpValue);
            break;
    /* LED_BUILTIN : GPIO_K16 */
    case 316: GPIO_Set(GPIO_GPK(16UL), vcpValue); 
            break;            
    default:
            break;
  }

  return ret;
}

int pinREAD(uint32_t vcpPin)
{
  uint8_t level = 0;

  switch (vcpPin)
  {
    case 3: level = GPIO_Get(GPIO_GPB(1UL)); 
            break;
    case 5: level = GPIO_Get(GPIO_GPB(0UL));
            break;
    case 7: level = GPIO_Get(GPIO_GPB(4UL)); 
            break;
    case 8: level = GPIO_Get(GPIO_GPB(25UL));
            break;
    case 10: level = GPIO_Get(GPIO_GPB(26UL));
            break;
    case 11: level = GPIO_Get(GPIO_GPB(6UL)); 
            break;
    case 12: level = GPIO_Get(GPIO_GPA(16UL)); 
            break;
    case 13: level = GPIO_Get(GPIO_GPB(23UL)); 
            break;
    case 15: level = GPIO_Get(GPIO_GPK(11UL)); 
            break;
    case 16: level = GPIO_Get(GPIO_GPC(4UL));
            break;
    case 18: level = GPIO_Get(GPIO_GPC(5UL));
            break;
    case 19: level = GPIO_Get(GPIO_GPA(24UL));
            break;
    case 21: level = GPIO_Get(GPIO_GPA(25UL));
            break;
    case 22: level = GPIO_Get(GPIO_GPK(9UL)); 
            break;
    case 23: level = GPIO_Get(GPIO_GPA(27UL));
            break;
    case 24: level = GPIO_Get(GPIO_GPA(26UL));
            break;
    case 26: level = GPIO_Get(GPIO_GPC(13UL));
            break;
    case 27: level = GPIO_Get(GPIO_GPB(3UL)); 
            break;
    case 28: level = GPIO_Get(GPIO_GPB(2UL));
            break;
    case 29: level = GPIO_Get(GPIO_GPA(29UL)); 
            break;
    case 31: level = GPIO_Get(GPIO_GPB(19UL)); 
            break;
    case 32: level = GPIO_Get(GPIO_GPB(11UL)); 
            break;
    case 33: level = GPIO_Get(GPIO_GPC(11UL)); 
            break;
    case 35: level = GPIO_Get(GPIO_GPC(15UL));
            break;
    case 36: level = GPIO_Get(GPIO_GPB(18UL)); 
            break;
    case 37: level = GPIO_Get(GPIO_GPA(18UL)); 
            break;
    case 38: level = GPIO_Get(GPIO_GPC(14UL));
            break;
    case 40: level = GPIO_Get(GPIO_GPC(12UL));
            break;       
    default:
            break;
  }

  return (level) ? HIGH : LOW;  
}
