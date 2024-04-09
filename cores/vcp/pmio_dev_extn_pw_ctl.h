
/*
***************************************************************************************************
*
*   FileName : pmio_dev_extn_pw_ctl.h
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*
*   TCC Version 1.0
*
*   This source code contains confidential information of Telechips.
*
*   Any unauthorized use without a written permission of Telechips including not limited to
*   re-distribution in source or binary form is strictly prohibited.
*
*   This source code is provided "AS IS" and nothing contained in this source code shall constitute
*   any express or implied warranty of any kind, including without limitation, any warranty of
*   merchantability, fitness for a particular purpose or non-infringement of any patent, copyright
*   or other third party intellectual property right. No warranty is made, express or implied,
*   regarding the information's accuracy,completeness, or performance.
*
*   In no event shall Telechips be liable for any claim, damages or other liability arising from,
*   out of or in connection with this source code or the use in the source code.
*
*   This source code is provided subject to the terms of a Mutual Non-Disclosure Agreement between
*   Telechips and Company.
*   This source code is provided "AS IS" and nothing contained in this source code shall constitute
*   any express or implied warranty of any kind, including without limitation, any warranty
*   (of merchantability, fitness for a particular purpose or non-infringement of any patent,
*   copyright or other third party intellectual property right. No warranty is made, express or
*   implied, regarding the information's accuracy, completeness, or performance.
*   In no event shall Telechips be liable for any claim, damages or other liability arising from,
*   out of or in connection with this source code or the use in the source code.
*   This source code is provided subject to the terms of a Mutual Non-Disclosure Agreement
*   between Telechips and Company.
*
***************************************************************************************************
*/

#ifndef  MCU_BSP_PMIO_DEV_EXTN_PW_CTL_HEADER
#define  MCU_BSP_PMIO_DEV_EXTN_PW_CTL_HEADER
/*
***************************************************************************************************
*                                             INCLUDE FILES
***************************************************************************************************
*/
#include <sal_internal.h>
#include <gic_enum.h>

/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/
#define PMIO_EXTN_VA_INTERRUPT_SRC_PMIC_RST  ((uint32_t)(GIC_EXT3))
#define PMIO_EXTN_VA_INTERRUPT_PRIO_PMIC_RST  (1UL)


//Sample Power Pin for D3
#define PMIO_EXTN_VA_STR_MODE_PIN           15UL
#define PMIO_EXTN_VA_STR_MODE_GPIO          (GPIO_GPK(PMIO_EXTN_VA_STR_MODE_PIN))

#define PMIO_EXTN_VA_PWR_EN_PIN             10UL
#define PMIO_EXTN_VA_PWR_EN_GPIO            (GPIO_GPK(PMIO_EXTN_VA_PWR_EN_PIN))

#define PMIO_EXTN_VA_ALIVE_PWR_CON_PIN      4UL
#define PMIO_EXTN_VA_ALIVE_PWR_CON_GPIO     (GPIO_GPB(PMIO_EXTN_VA_ALIVE_PWR_CON_PIN))

#define PMIO_EXTN_VA_PMIC_RESET_OUT_PIN     15UL
#define PMIO_EXTN_VA_PMIC_RESET_OUT_GPIO    (GPIO_GPA(PMIO_EXTN_VA_PMIC_RESET_OUT_PIN))

#define PMIO_EXTN_VA_TCC_RESET_PIN          19UL
#define PMIO_EXTN_VA_TCC_RESET_GPIO         (GPIO_GPA(PMIO_EXTN_VA_TCC_RESET_PIN))
/*
***************************************************************************************************
*                                             LOCAL VARIABLES
***************************************************************************************************
*/

typedef struct
{
    uint32_t uiPwrEnPin;
    uint32_t uiAlivePwrConPin;
    uint32_t uiStrModePin;
    uint32_t uiPmicRstPin;
    uint32_t uiTccRstPin;
}PMIOEXTNExtPwrPins_t;

/*
***************************************************************************************************
*                                         FUNCTION PROTOTYPES
***************************************************************************************************
*/
void PMIO_EXTN_Init
(
    PMIOEXTNExtPwrPins_t tExtPwrPins
);

void PMIO_EXTN_SetStr
(
    uint8_t ucEn
);

void PMIO_EXTN_SetPower
(
    uint8_t ucEn
);

uint32_t PMIO_EXTN_GetUsingGpk32
(
    void
);


#endif /*MCU_BSP_PMIO_DEV_EXTN_PW_CTL_HEADER*/
