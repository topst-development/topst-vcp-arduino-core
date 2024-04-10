/*
***************************************************************************************************
*
*   FileName : tost_app.c
*
*   Copyright (c) Telechips Inc.
*
*   Description : Tost Application
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

/**************************************************************************************************
*                                           INCLUDE FILES
**************************************************************************************************/

#include <app_cfg.h>

#if (ACFG_APP_TOST_EN == 1)
#include "bsp.h"
#include "sal_internal.h"
#include "debug.h"
#include "uart.h"
#include "pmu_reg.h"
#include "tost_app.h"
#include "clock.h"
#include "clock_dev.h"
#include "gpio.h"
#include "timer.h"


/**************************************************************************************************
*                                          LOCAL VARIABLES
**************************************************************************************************/

static TIMERConfig_t sTimerCfg;

/**************************************************************************************************
 *                                         DEFINTIONS
 **************************************************************************************************/

#define GPIO_WriteReg(a,v)              (SAL_WriteReg(v,a))
#define GPIO_ReadReg(a)                 (SAL_ReadReg(a))

/**************************************************************************************************
*                                  STATIC FUNCTIONS DECLARATION
**************************************************************************************************/
static int32_t Timer_MainHandler(TIMERChannel_t iChannel, void * args);

static void TopstAppTask
(
    void                                *pArg
);

/**************************************************************************************************
*                                        STATIC FUNCTIONS
**************************************************************************************************/

static int32_t Timer_MainHandler(TIMERChannel_t iChannel, void * args)
{
    (void)iChannel;
    (void)args;
    static uint32_t uiCnt = 0;

    if (uiCnt++ % 2 == 0) {
        // LED Off
        (void)GPIO_Set(GPIO_GPK(16UL), 1UL);
    }
    else
    {
        // LED On
        (void)GPIO_Set(GPIO_GPK(16UL), 0UL);
    }

    return 0;
}

static void TopstAppTask
(
    void                                *pArg
)
{
    uint8_t ucAccSwitchStatus;
    uint8_t ucILLISwitchStatus;
    uint8_t ucStrSwitchStatus;
    uint8_t ucKey0Status;

    GPIO_WriteReg(0xA0F28808, 0xFFFFFFFFUL);
    // set GPIOK_16 as output for LED
    GPIO_Config(GPIO_GPK(16UL), (GPIO_FUNC(0UL) | GPIO_OUTPUT));
    // LED Off
    GPIO_Set(GPIO_GPK(16UL), 1UL);

    // set GPIOK_7 as input for KEY0 button
    GPIO_Config(GPIO_GPK(7UL), (GPIO_FUNC(0UL) | GPIO_INPUTBUF_EN | GPIO_PULLUP));

    // set GPIOK_5 as input for ACC Switch
    GPIO_Config(GPIO_GPK(5UL), (GPIO_FUNC(0UL) | GPIO_INPUTBUF_EN | GPIO_PULLUP));
    // set GPIOC_3 as input for ILLI Switch
    GPIO_Config(GPIO_GPC(3UL), (GPIO_FUNC(0UL) | GPIO_INPUTBUF_EN));
    // set GPIOK_2 as input for STR Switch
    GPIO_Config(GPIO_GPK(2UL), (GPIO_FUNC(0UL) | GPIO_INPUTBUF_EN | GPIO_PULLUP));

    ucAccSwitchStatus = GPIO_Get(GPIO_GPK(5UL));
    ucILLISwitchStatus = GPIO_Get(GPIO_GPC(3UL));
    ucStrSwitchStatus = GPIO_Get(GPIO_GPK(2UL));
    ucKey0Status = GPIO_Get(GPIO_GPK(7UL));

    mcu_printf("%s, ACC Switch Status : %d\n", __func__, ucAccSwitchStatus);
    mcu_printf("%s, ILLI Switch Status : %d\n", __func__, ucILLISwitchStatus);
    mcu_printf("%s, STR Switch Status : %d\n", __func__, ucStrSwitchStatus);
    mcu_printf("%s, KEY0 Button Status : %d\n", __func__, ucKey0Status);

    sTimerCfg.ctChannel = TIMER_CH_1;
    sTimerCfg.ctStartMode = TIMER_START_ZERO;
    sTimerCfg.ctOpMode = TIMER_OP_FREERUN;
    sTimerCfg.ctCounterMode = TIMER_COUNTER_MAIN;
    sTimerCfg.ctMainValueUsec = 1 * 1000 * 1000; // 1 sec
    sTimerCfg.ctCmp0ValueUsec = 0;
    sTimerCfg.ctCmp1ValueUsec = 0;
    sTimerCfg.fnHandler = Timer_MainHandler;
    sTimerCfg.pArgs = NULL;

    (void)TIMER_Init();
    (void)TIMER_EnableWithCfg(&sTimerCfg);
    GIC_IntSrcEn((uint32_t)GIC_TIMER_0 + sTimerCfg.ctChannel);

    if (ucKey0Status == 0) 
    {
        mcu_printf("%s, TOPST App Download Mode\n", __func__);
    } else {
        mcu_printf("%s, TOPST App Normal Boot Mode\n", __func__);
        return;
    }
}

/**************************************************************************************************
*                                             FUNCTIONS
**************************************************************************************************/

void CreateTopstAppTask(void)
{
    static uint32_t   uiTopstAppTaskID = 0UL;
    static uint32_t   uiTopstAppTaskStk[TOPST_APP_TASK_STK_SIZE];

    (void)SAL_TaskCreate
    (
        &uiTopstAppTaskID,
        (const uint8_t *)"Topst App Task",
        (SALTaskFunc)&TopstAppTask,
        &uiTopstAppTaskStk[0],
        TOPST_APP_TASK_STK_SIZE,
        SAL_PRIO_TOPST_APP,
        NULL
    );
}

#endif //#if (ACFG_APP_TOPST_EN == 1)

