/*
***************************************************************************************************
*
*   FileName : clock.h
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

#ifndef MCU_BSP_CLOCK_HEADER
#define MCU_BSP_CLOCK_HEADER

#include <sal_internal.h>
#include <stdbool.h>

/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/

#define CKC_MHZ(x)                      (uint32_t)((x) * 1000000)

/*
***************************************************************************************************
*                                         FUNCTION PROTOTYPES
***************************************************************************************************
*/

void CLOCK_Init
(
    void
);

uint32_t CLOCK_SetPllRate
(
    uint32_t                              iId,
    uint32_t                              uiRate
);

uint32_t CLOCK_GetPllRate
(
    uint32_t                              iId
);

uint32_t CLOCK_SetPllDiv
(
    uint32_t                              iId,
    uint32_t                              uiPllDiv
);

uint32_t CLOCK_SetClkCtrlRate
(
    uint32_t                              iId,
    uint32_t                              uiRate
);

uint32_t CLOCK_GetClkCtrlRate
(
    uint32_t                              iId
);

uint32_t CLOCK_IsPeriEnabled
(
    uint32_t                              iId
);

uint32_t CLOCK_EnablePeri
(
    uint32_t                              iId
);

uint32_t CLOCK_DisablePeri
(
    uint32_t                              iId
);

uint32_t CLOCK_GetPeriRate
(
    uint32_t                              iId
);

uint32_t CLOCK_SetPeriRate
(
    uint32_t                              iId,
    uint32_t                              uiRate
);

uint32_t CLOCK_IsIobusPwdn
(
    uint32_t                              iId
);

uint32_t CLOCK_EnableIobus
(
    uint32_t                              iId,
    bool                             bEn
);

uint32_t CLOCK_SetIobusPwdn
(
    uint32_t                              iId,
    bool                             bEn
);

uint32_t CLOCK_SetSwReset
(
    uint32_t                              iId,
    bool                             bReset
);

#endif /* __MCU_BSP_CLOCK_HEADER__ */

