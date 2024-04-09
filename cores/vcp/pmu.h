/*
***************************************************************************************************
*
*   FileName : pmu.h
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

#ifndef  MCU_BSP_PMU_HEADER
#define  MCU_BSP_PMU_HEADER

#include <sal_internal.h>
#include <gic_enum.h>
#include <stdbool.h>

/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/
typedef enum
{
    PMU_SRC_NOTHING                   = 0,

    PMU_SRC_COLD                      = 1 , //ResetOccur,
    PMU_SRC_HSM_COLD                  = 2 , //ResetOccur, ResetMonitor
    PMU_SRC_FMU_FAULT                 = 3 , //ResetOccur, ResetMonitor
    PMU_SRC_WARM                      = 4 , //ResetOccur,
    PMU_SRC_HSM_WARM                  = 5 , //ResetOccur, ResetMonitor
    PMU_SRC_WDT                       = 6 , //ResetOccur, ResetMonitor
    PMU_SRC_PMU_WDT                   = 7 , //ResetOccur, ResetMonitor
    PMU_SRC_HSM_WDT                   = 8 , //ResetOccur, ResetMonitor

    PMU_SRC_XIN_PVT                   = 10, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR0_PVT                  = 11, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR1_PVT                  = 12, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR2_PVT                  = 13, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR3_PVT                  = 14, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR4_PVT                  = 15, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR5_PVT                  = 16, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR6_PVT                  = 17, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR7_PVT                  = 18, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR8_PVT                  = 19, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR9_PVT                  = 20, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR10_PVT                 = 21, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR11_PVT                 = 22, //ResetOccur, ResetMonitor, ClearPvtError
    PMU_SRC_PWR12_PVT                 = 23, //ResetOccur, ResetMonitor, ClearPvtError

    PMU_SRC_MAX                       = 24
}PMUSrc_t;


typedef enum
{
    PMU_MON_SRC_NOTHING                   = PMU_SRC_NOTHING  ,

    PMU_MON_SRC_HSM_COLD                  = PMU_SRC_HSM_COLD ,
    PMU_MON_SRC_FMU_FAULT                 = PMU_SRC_FMU_FAULT,
    PMU_MON_SRC_HSM_WARM                  = PMU_SRC_HSM_WARM ,
    PMU_MON_SRC_WDT                       = PMU_SRC_WDT      ,
    PMU_MON_SRC_PMU_WDT                   = PMU_SRC_PMU_WDT  ,
    PMU_MON_SRC_HSM_WDT                   = PMU_SRC_HSM_WDT  ,
    PMU_MON_SRC_XIN_PVT                   = PMU_SRC_XIN_PVT  ,
    PMU_MON_SRC_PWR0_PVT                  = PMU_SRC_PWR0_PVT ,
    PMU_MON_SRC_PWR1_PVT                  = PMU_SRC_PWR1_PVT ,
    PMU_MON_SRC_PWR2_PVT                  = PMU_SRC_PWR2_PVT ,
    PMU_MON_SRC_PWR3_PVT                  = PMU_SRC_PWR3_PVT ,
    PMU_MON_SRC_PWR4_PVT                  = PMU_SRC_PWR4_PVT ,
    PMU_MON_SRC_PWR5_PVT                  = PMU_SRC_PWR5_PVT ,
    PMU_MON_SRC_PWR6_PVT                  = PMU_SRC_PWR6_PVT ,
    PMU_MON_SRC_PWR7_PVT                  = PMU_SRC_PWR7_PVT ,
    PMU_MON_SRC_PWR8_PVT                  = PMU_SRC_PWR8_PVT ,
    PMU_MON_SRC_PWR9_PVT                  = PMU_SRC_PWR9_PVT ,
    PMU_MON_SRC_PWR10_PVT                 = PMU_SRC_PWR10_PVT,
    PMU_MON_SRC_PWR11_PVT                 = PMU_SRC_PWR11_PVT,
    PMU_MON_SRC_PWR12_PVT                 = PMU_SRC_PWR12_PVT,

    PMU_MON_SRC_MAX
}PMUMonSrc_t;

typedef enum
{
    PMU_PVT_SRC_NOTHING                   = PMU_SRC_NOTHING  ,

    PMU_PVT_SRC_XIN_PVT                   = PMU_SRC_XIN_PVT  ,
    PMU_PVT_SRC_PWR0_PVT                  = PMU_SRC_PWR0_PVT ,
    PMU_PVT_SRC_PWR1_PVT                  = PMU_SRC_PWR1_PVT ,
    PMU_PVT_SRC_PWR2_PVT                  = PMU_SRC_PWR2_PVT ,
    PMU_PVT_SRC_PWR3_PVT                  = PMU_SRC_PWR3_PVT ,
    PMU_PVT_SRC_PWR4_PVT                  = PMU_SRC_PWR4_PVT ,
    PMU_PVT_SRC_PWR5_PVT                  = PMU_SRC_PWR5_PVT ,
    PMU_PVT_SRC_PWR6_PVT                  = PMU_SRC_PWR6_PVT ,
    PMU_PVT_SRC_PWR7_PVT                  = PMU_SRC_PWR7_PVT ,
    PMU_PVT_SRC_PWR8_PVT                  = PMU_SRC_PWR8_PVT ,
    PMU_PVT_SRC_PWR9_PVT                  = PMU_SRC_PWR9_PVT ,
    PMU_PVT_SRC_PWR10_PVT                 = PMU_SRC_PWR10_PVT,
    PMU_PVT_SRC_PWR11_PVT                 = PMU_SRC_PWR11_PVT,
    PMU_PVT_SRC_PWR12_PVT                 = PMU_SRC_PWR12_PVT,

    PMU_PVT_SRC_MAX
}PMUPvtSrc_t;

/*
***************************************************************************************************
*                                             LOCAL VARIABLES
***************************************************************************************************
*/

/**************************************************************************************************/
/*                                         FUNCTION PROTOTYPES                                    */
/**************************************************************************************************/

//Initial PMU
void PMU_Init
(
    void
);



//Control Reset
bool PMU_GetResetOccur
(
    PMUSrc_t                          tRst
);

void PMU_EnableResetMonitor
(
    PMUMonSrc_t                          tRst
);

void PMU_DisableResetMonitor
(
    PMUMonSrc_t                          tRst
);



//Control SW Reset
void PMU_ColdReset
(
    void
);

void PMU_WarmReset
(
    void
);


//Control PVT Error status
void PMU_ClearPvtError
(
    PMUPvtSrc_t                            tPvt
);

#endif

