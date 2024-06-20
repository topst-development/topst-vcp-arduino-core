/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"
#include "debug.h"
#include "adc.h"

#include "pdm.h"

#ifdef __cplusplus
extern "C" {
#endif

// Perform the read operation on the selected analog pin.
// the initialization of the analog PIN is done through this function
uint32_t analogRead(uint32_t ulPin)
{
  uint32_t value = 0;

  ADC_Init(ADC_MODE_NORMAL, ADC_MODULE_1);

  switch (ulPin)
  {
    case 16: value = 0xFFF & ADC_Read(4UL, ADC_MODULE_1, 0);
             break;
    case 18: value = 0xFFF & ADC_Read(5UL, ADC_MODULE_1, 0);
             break;
    default:
             break;
  }

  return value;
}

void analogWrite(uint32_t ulPin, uint32_t ulValue)
{
  // SALRetCode_t    ret             = SAL_RET_FAILED;
  // uint32          uiDutyRate      = 0;
  // PDMModeConfig_t sModeConfigInfo = {0,};

  // //mcu_printf("\n== Start PDM Phase Mode1 Sample ==\n");

  // (void)PDM_Init();

  // //PDM_TestSleepForSec(2);
  // //delay(1000);

  // sModeConfigInfo.mcOperationMode     = PDM_OUTPUT_MODE_PHASE_1;
  // sModeConfigInfo.mcPortNumber        = GPIO_PERICH_CH2;

  // for(uiDutyRate = 0; uiDutyRate <= 1000; uiDutyRate += 50)
  // {
  //   mcu_printf("\n\t********** DUTY %d %% **********\n", uiDutyRate/10);

  //   sModeConfigInfo.mcPeriodNanoSec1    = 1000UL     * 1000UL;
  //   sModeConfigInfo.mcDutyNanoSec1      = uiDutyRate * 1000UL;

  //   ret = PDM_SetConfig((uint32)PDM_CHANNEL_5, &sModeConfigInfo);

  //   if(ret == SAL_RET_SUCCESS)
  //   {
  //     PDM_Enable((uint32)PDM_CHANNEL_5, PMM_ON);
  //   }

  //   //PDM_TestSleepForSec(4UL);
  //   delay(100);

  // }

  // (void)PDM_Disable((uint32)PDM_CHANNEL_5, PMM_ON);

  // //mcu_printf("\n== End of PDM Phase Mode1 Sample ==\n");

  SALRetCode_t ret = SAL_RET_FAILED;

  uint32_t uiDutyRate = ulValue;
  PDMModeConfig_t sModeConfigInfo = {0,};

  (void)PDM_Init();

  sModeConfigInfo.mcOperationMode  = PDM_OUTPUT_MODE_PHASE_1;
  sModeConfigInfo.mcPortNumber     = GPIO_PERICH_CH2;
  sModeConfigInfo.mcPeriodNanoSec1 = 1000UL * 1000UL;
  sModeConfigInfo.mcDutyNanoSec1   = uiDutyRate * 1000UL;

  ret = PDM_SetConfig((uint32_t)ulPin, &sModeConfigInfo);

  if(ret == SAL_RET_SUCCESS)
  {
    PDM_Enable((uint32_t)ulPin, PMM_ON);
  }

  //(void)PDM_Disable((uint32_t) ulPin, PMM_ON);


}


#ifdef __cplusplus
}
#endif
