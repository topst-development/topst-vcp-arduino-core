// SPDX-License-Identifier: Apache-2.0

/*
***************************************************************************************************
*
*   FileName : clock_dev.c
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*/

#include <string.h>
#include "reg_phys.h"
#include "clock.h"
#include "clock_dev.h"
#include "clock_reg.h"

/*
***************************************************************************************************
*                                             DEFINITIONS
***************************************************************************************************
*/


/***************************************************************************************************
*                                             LOCAL VARIABLES
***************************************************************************************************/

static uint32_t stMicomClockSource[CLOCK_SRC_MAX_NUM];

/*
***************************************************************************************************
*                                         FUNCTION PROTOTYPES
***************************************************************************************************
*/

static void   CLOCK_DevWritePll
(
    uint32_t                              uiReg,
    uint32_t                              uiEn,
    uint32_t                              uiP,
    uint32_t                              uiM,
    uint32_t                              uiS
);

static void   CLOCK_DevWritePclkCtrl
(
    SALAddr                             uiReg,
    uint32_t                              uiMd,
    uint32_t                              uiEn,
    uint32_t                              uiSel,
    uint32_t                              uiDiv,
    uint32_t                              uiType
);

static void   CLOCK_DevWriteClkCtrl
(
    SALAddr                             uiReg,
    uint32_t                              uiEn,
    uint32_t                              uiConf,
    uint32_t                              uiSel
);

static int32_t CLOCK_DevFindPms
(
    CLOCKPms_t*                         psPll,
    uint32_t                              uiSrcFreq
);

static int32_t CLOCK_DevSetPllRate
(
    SALAddr                             uiReg,
    uint32_t                              uiRate
);

static uint32_t CLOCK_DevGetPllRate
(
    SALAddr                             uiReg
);

static uint32_t CLOCK_DevGetPllDiv
(
    int32_t                              iId
);

static int32_t CLOCK_DevFindClkCtrl
(
    CLOCKClkCtrl_t*                     CLKCTRL
);

static uint32_t CLOCK_DevCalPclkDiv
(
    const CLOCKPclkCtrl_t*              psPclkCtrl,
    uint32_t*                             puiClkDiv,
    const uint32_t                        uiSrcClk,
    /*uint32_t                              uiDivMin,*/
    uint32_t                              uiDivMax
);

static int32_t CLOCK_DevFindPclk
(
    CLOCKPclkCtrl_t *                   psPclkCtrl,
    CLOCKPclkCtrlType_t                 eType
);

static void   CLOCK_DevResetClkSrc
(
    int32_t                              iId
);

/* PLL Configuration Macro */
static void CLOCK_DevWritePll
(
    uint32_t                              uiReg,
    uint32_t                              uiEn,
    uint32_t                              uiP,
    uint32_t                              uiM,
    uint32_t                              uiS
)
{
    const uint32_t    uiTimeout  = 4000000000UL;
    uint32_t          uiDelay;
    uint32_t          uiTryCnt;

    uiDelay     = 0;
    uiTryCnt    = 0;

    if(uiReg != 0UL)
    {
        if (uiEn != 0UL)
        {
            SAL_WriteReg(0UL                                                                    \
                    | (1UL << (uint32_t)CLOCK_PLL_LOCKEN_SHIFT)                                   \
                    | (2UL << (uint32_t)CLOCK_PLL_CHGPUMP_SHIFT)                                  \
                    | (((uiS) & (uint32_t)CLOCK_PLL_S_MASK) << (uint32_t)CLOCK_PLL_S_SHIFT)         \
                    | (((uiM) & (uint32_t)CLOCK_PLL_M_MASK) << (uint32_t)CLOCK_PLL_M_SHIFT)         \
                    | (((uiP) & (uint32_t)CLOCK_PLL_P_MASK) << (uint32_t)CLOCK_PLL_P_SHIFT),        \
                    uiReg);

            for (uiDelay = 100UL ; uiDelay > 0UL ; uiDelay--)
            {
                ;  /* if cpu clokc is 1HGz then loop 100. */
            }

            SAL_WriteReg(SAL_ReadReg(uiReg) | (((uiEn) & 1UL) << (uint32_t)CLOCK_PLL_EN_SHIFT), \
                            uiReg);

            while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_PLL_LOCKST_SHIFT)) == 0UL)
            {
                uiTryCnt++;

                if(uiTryCnt > uiTimeout)
                {
                    break;
                }
            }
        }
        else
        {
            SAL_WriteReg((uint32_t)(SAL_ReadReg(uiReg)) & (~(1UL << (uint32_t)CLOCK_PLL_EN_SHIFT)), \
                            uiReg);
        }
    }
}

static void CLOCK_DevWritePclkCtrl
(
    SALAddr                             uiReg,
    uint32_t                              uiMd,
    uint32_t                              uiEn,
    uint32_t                              uiSel,
    uint32_t                              uiDiv,
    uint32_t                              uiType
)
{
    if (uiType == (uint32_t)CLOCK_PCLKCTRL_TYPE_XXX)
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_OUTEN_SHIFT), uiReg);
        SAL_WriteReg(SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~((uint32_t)CLOCK_PCLKCTRL_DIV_XXX_MASK \
                        << (uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT))
                | ((uiDiv&(uint32_t)CLOCK_PCLKCTRL_DIV_XXX_MASK) \
                    <<(uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~((uint32_t)CLOCK_PCLKCTRL_SEL_MASK \
                        << (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT))
                | ((uiSel&(uint32_t)CLOCK_PCLKCTRL_SEL_MASK) << (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT), \
                uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT))
                | ((uiEn&1UL) << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_OUTEN_SHIFT))
                | ((uiEn&1UL) << (uint32_t)CLOCK_PCLKCTRL_OUTEN_SHIFT), uiReg);
    }
    else if (uiType == (uint32_t)CLOCK_PCLKCTRL_TYPE_YYY)
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~((uint32_t)CLOCK_PCLKCTRL_DIV_YYY_MASK \
                        << (uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT))
                | ((uiDiv&(uint32_t)CLOCK_PCLKCTRL_DIV_YYY_MASK) \
                    << (uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~((uint32_t)CLOCK_PCLKCTRL_SEL_MASK \
                        << (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT))
                | ((uiSel&(uint32_t)CLOCK_PCLKCTRL_SEL_MASK) \
                    << (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_MD_SHIFT))
                | ((uiMd&1UL) << (uint32_t)CLOCK_PCLKCTRL_MD_SHIFT), uiReg);
        SAL_WriteReg((SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT))
                | ((uiEn&1UL) << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT), uiReg);
    }
    else
    {
        ; //empty statement
    }
}

static void CLOCK_DevWriteClkCtrl
(
    SALAddr                             uiReg,
    uint32_t                              uiEn,
    uint32_t                              uiConf,
    uint32_t                              uiSel
)
{
    const uint32_t    uiTimeout = 4000000000;
    uint32_t          uiCurConf;
    uint32_t          uiTryCnt;

    uiCurConf = (SAL_ReadReg(uiReg) >> (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT) \
                & (uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK;

    if (uiConf >= uiCurConf)
    {
        SAL_WriteReg((SAL_ReadReg(uiReg) & (~((uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK \
                            << (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT)))
                | ((uiConf&(uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK) \
                    << (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT), uiReg);
        uiTryCnt    = 0;

        while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_MCLKCTRL_CLKCHG_SHIFT)) != 0UL)
        {
            uiTryCnt++;

            if(uiTryCnt > uiTimeout)
            {
                break;
            }
        }

        SAL_WriteReg((SAL_ReadReg(uiReg) & (~((uint32_t)CLOCK_MCLKCTRL_SEL_MASK \
                            << (uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT)))
                | ((uiSel & (uint32_t)CLOCK_MCLKCTRL_SEL_MASK) \
                    << (uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT), uiReg);
        uiTryCnt = 0;

        while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_MCLKCTRL_CLKCHG_SHIFT)) != 0UL)
        {
            uiTryCnt++;

            if(uiTryCnt > uiTimeout)
            {
                break;
            }
        }
    }
    else
    {
        SAL_WriteReg((SAL_ReadReg(uiReg) & (~((uint32_t)CLOCK_MCLKCTRL_SEL_MASK \
                            << (uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT)))
                | ((uiSel&(uint32_t)CLOCK_MCLKCTRL_SEL_MASK) \
                    <<(uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT), uiReg);
        uiTryCnt = 0;

        while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_MCLKCTRL_CLKCHG_SHIFT)) != 0UL)
        {
            uiTryCnt++;

            if(uiTryCnt > uiTimeout)
            {
                break;
            }
        }

        SAL_WriteReg((SAL_ReadReg(uiReg) & (~((uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK \
                            << (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT)))
                | ((uiConf&(uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK) \
                    << (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT), uiReg);
        uiTryCnt = 0;

        while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_MCLKCTRL_CLKCHG_SHIFT)) != 0UL)
        {
            uiTryCnt++;

            if(uiTryCnt > uiTimeout)
            {
                break;
            }
        }
    }

    if (uiEn != 0UL)
    {
        SAL_WriteReg((SAL_ReadReg(uiReg) & (~(1UL << (uint32_t)CLOCK_MCLKCTRL_EN_SHIFT)))
                | ((uiEn & 1UL) << (uint32_t)CLOCK_MCLKCTRL_EN_SHIFT), uiReg);
        uiTryCnt = 0;

        while((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_MCLKCTRL_DIVSTS_SHIFT)) != 0UL)
        {
            uiTryCnt++;

            if(uiTryCnt > uiTimeout)
            {
                break;
            }
        }
    }
}

static int32_t CLOCK_DevFindPms
(
    CLOCKPms_t *                        psPll,
    uint32_t                              uiSrcFreq
)
{
    uint64_t ullPll;
    uint64_t ullSrc;
    uint64_t ullFvco;
    uint64_t ullSrchP;
    uint64_t ullSrchM;
    uint64_t ullTemp;
    uint64_t ullSrchPll;

    uint32_t uiErr;
    uint32_t uiSrchErr;

    int32_t  iSrchS;

    if (psPll == NULL)
    {
        return 0;
    }

    if (psPll->uiFpll == 0UL)
    {
        psPll->uiEn = 0;
        return 0;
    }

    ullPll = (uint64_t)psPll->uiFpll;
    ullSrc = (uint64_t)uiSrcFreq;

    uiErr       = 0xFFFFFFFFUL;
    uiSrchErr   = 0xFFFFFFFFUL;

    for (iSrchS = (int32_t)CLOCK_PLL_S_MIN ; iSrchS <= (int32_t)CLOCK_PLL_S_MAX ; iSrchS++)
    {
        ullFvco = ullPll << (uint64_t)iSrchS;

        if ((ullFvco >= (uint64_t)CLOCK_PLL_VCO_MIN) && (ullFvco <= (uint64_t)CLOCK_PLL_VCO_MAX))
        {
            for (ullSrchP = (uint64_t)CLOCK_PLL_P_MIN \
                    ; ullSrchP <= (uint64_t)CLOCK_PLL_P_MAX \
                    ; ullSrchP++)
            {
                ullSrchM    = ullFvco*ullSrchP;
                (void)SAL_CoreDiv64To32(&(ullSrchM), (uint32_t)uiSrcFreq, NULL);

                if ((ullSrchM < (uint64_t)CLOCK_PLL_M_MIN) || (ullSrchM > (uint64_t)CLOCK_PLL_M_MAX))
                {
                    continue;
                }

                ullTemp = ullSrchM*ullSrc;
                (void)SAL_CoreDiv64To32(&(ullTemp), (uint32_t)ullSrchP, NULL);
                ullSrchPll  = (ullTemp>>(uint64_t)iSrchS);

                if ((ullSrchPll < (uint64_t)CLOCK_PLL_MIN_RATE) \
                        || (ullSrchPll > (uint64_t)CLOCK_PLL_MAX_RATE))
                {
                    continue;
                }

                uiSrchErr = (uint32_t)((ullSrchPll > ullPll) ? (ullSrchPll - ullPll) \
                        : (ullPll - ullSrchPll));

                if (uiSrchErr < uiErr)
                {
                    uiErr       = uiSrchErr;
                    psPll->uiP  = (uint32_t)ullSrchP;
                    psPll->uiM  = (uint32_t)ullSrchM;
                    psPll->uiS  = (uint32_t)iSrchS;
                }
            }
        }
    }

    if (uiErr == 0xFFFFFFFFUL)
    {
        return -1;
    }

    ullTemp = ullSrc * (uint64_t)psPll->uiM;
    (void)SAL_CoreDiv64To32(&(ullTemp), (uint32_t)(psPll->uiP), NULL);
    psPll->uiFpll   = (uint32_t)(ullTemp >> psPll->uiS);
    psPll->uiEn     = 1;

    return 0;
}

static int32_t CLOCK_DevSetPllRate
(
    SALAddr                             uiReg,
    uint32_t                              uiRate
)
{
    CLOCKPms_t  sPll;
    uint64_t      ullCalM;
    int32_t      iErr;

    iErr    = 0;
    sPll.uiFpll = uiRate;

    if (CLOCK_DevFindPms(&sPll, CLOCK_XIN_CLK_RATE) != 0L)
    {
        //goto tcc_ckc_setpll2_failed;
        ullCalM = (uint64_t)CLOCK_PLL_P_MIN * (uint64_t)CLOCK_PLL_VCO_MIN;
        ullCalM += (uint64_t)CLOCK_XIN_CLK_RATE;
        ullCalM /= (uint64_t)CLOCK_XIN_CLK_RATE;
        CLOCK_DevWritePll(                  \
                uiReg,                      \
                0UL,                        \
                (uint32_t)CLOCK_PLL_P_MIN,    \
                (uint32_t)ullCalM,            \
                (uint32_t)CLOCK_PLL_S_MIN     \
                );
        iErr = -1;
    }
    else
    {
        CLOCK_DevWritePll(uiReg, sPll.uiEn, sPll.uiP, sPll.uiM, sPll.uiS);
    }

    //return 0;

    //tcc_ckc_setpll2_failed:
    //  CLOCK_DevWritePll(uiReg, 0, CLOCK_PLL_P_MIN,
    //((CLOCK_PLL_P_MIN*CLOCK_PLL_VCO_MIN)+CLOCK_XIN_CLK_RATE)/CLOCK_XIN_CLK_RATE, CLOCK_PLL_S_MIN);

    return iErr;
}

static uint32_t CLOCK_DevGetPllRate
(
    SALAddr                             uiReg
)
{
    uint32_t      uiRegVa;
    CLOCKPms_t  sPllCfg;
    uint64_t      ullTemp;

    if(uiReg == 0UL)
    {
        return 0;
    }
    else
    {
        uiRegVa = SAL_ReadReg(uiReg);
    }

    sPllCfg.uiP     = (uiRegVa >> (uint32_t)CLOCK_PLL_P_SHIFT) & ((uint32_t)CLOCK_PLL_P_MASK);
    sPllCfg.uiM     = (uiRegVa >> (uint32_t)CLOCK_PLL_M_SHIFT) & ((uint32_t)CLOCK_PLL_M_MASK);
    sPllCfg.uiS     = (uiRegVa >> (uint32_t)CLOCK_PLL_S_SHIFT) & ((uint32_t)CLOCK_PLL_S_MASK);
    sPllCfg.uiEn    = (uiRegVa >> (uint32_t)CLOCK_PLL_EN_SHIFT) & (1UL);
    sPllCfg.uiSrc   = (uiRegVa >> (uint32_t)CLOCK_PLL_SRC_SHIFT) & ((uint32_t)CLOCK_PLL_SRC_MASK);
    ullTemp         = (uint64_t)CLOCK_XIN_CLK_RATE * (uint64_t)sPllCfg.uiM;
    (void)SAL_CoreDiv64To32(&ullTemp, (uint32_t)(sPllCfg.uiP), NULL);

    return (uint32_t)((ullTemp) >> sPllCfg.uiS);
}

static uint32_t CLOCK_DevGetPllDiv
(
    int32_t                              iId
)
{
    uint32_t      uiRet;
    CLOCKMpll_t uiMpllId;
    SALAddr     uiReg;
    uint32_t      uiOffSet;
    uint32_t      uiRegVa;

    uiRet       = 0;
    uiMpllId    = (CLOCKMpll_t)iId;
    uiReg       = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_CLKDIVC;
    uiRegVa     = 0;

    switch(uiMpllId)
    {
        case CLOCK_MPLL_0:
        case CLOCK_MPLL_1:
        {
            uiOffSet = (3UL-(uint32_t)iId) * 8UL;
            break;
        }

        case CLOCK_MPLL_XIN:
        {
            uiOffSet = 8UL;
            break;
        }

        default:
        {
            uiOffSet = 0UL;
            break;
        }
    }

    uiRegVa = SAL_ReadReg(uiReg);

    if(uiOffSet != 0UL)
    {
        uiRet = ((uiRegVa >> uiOffSet) & 0x3FUL);
    }

    return uiRet;
}

static uint32_t CLOCK_DevCalPclkDiv
(
    const CLOCKPclkCtrl_t *             psPclkCtrl,
    uint32_t *                            puiClkDiv,
    const uint32_t                        uiSrcClk,
    /*uint32_t                              uiDivMin,*/
    uint32_t                              uiDivMax
)
{
    uint32_t uiClkRate1;
    uint32_t uiClkRate2;
    uint32_t uiErr1;
    uint32_t uiErr2;

    if(psPclkCtrl == NULL)
    {
        return 0;
    }

    if(puiClkDiv == NULL)
    {
        return 0;
    }

    if (uiSrcClk <= psPclkCtrl->uiFreq)
    {
        *puiClkDiv = 1UL;
    }
    else
    {
        *puiClkDiv = uiSrcClk/psPclkCtrl->uiFreq;
    }

    if ((*puiClkDiv) > uiDivMax)
    {
        *puiClkDiv = uiDivMax;
    }

    uiClkRate1  = (uiSrcClk) / (*puiClkDiv);
    uiClkRate2  = (uiSrcClk) / (((*puiClkDiv) < uiDivMax) ? ((*puiClkDiv) + 1UL) : (*puiClkDiv));
    uiErr1      = (uiClkRate1 > psPclkCtrl->uiFreq) ? (uiClkRate1 - psPclkCtrl->uiFreq) \
                  : (psPclkCtrl->uiFreq - uiClkRate1);
    uiErr2      = (uiClkRate2 > psPclkCtrl->uiFreq) ? (uiClkRate2 - psPclkCtrl->uiFreq) \
                  : (psPclkCtrl->uiFreq - uiClkRate2);

    if (uiErr1 > uiErr2)
    {
        *puiClkDiv += 1UL;
    }

    return (uiErr1 < uiErr2) ? uiErr1 : uiErr2;
}

static int32_t CLOCK_DevFindPclk
(
    CLOCKPclkCtrl_t *                   psPclkCtrl,
    CLOCKPclkCtrlType_t                 eType
)
{
    int32_t              iRet;
    int32_t              iLastIdx;
    int32_t              iIdx;
    uint32_t              uiDivMax;
    uint32_t              uiSrchSrc;
    uint32_t              uiErrDiv;
    uint32_t              uiMd;
    uint32_t              uiDiv[CLOCK_SRC_MAX_NUM];
    uint32_t              uiErr[CLOCK_SRC_MAX_NUM];
    uint32_t              uiDivDiv;
    CLOCKPclkCtrlMode_t tPclkSel;

    uiDivDiv    = CLOCK_PCLKCTRL_DIV_MIN;
    tPclkSel    = CLOCK_PCLKCTRL_MODE_DIVIDER;
    iRet        = 0;

    if(psPclkCtrl == NULL)
    {
        return -1;
    }

    psPclkCtrl->uiMd    = (uint32_t)tPclkSel;
    uiDivMax            = CLOCK_PCLKCTRL_DIV_XXX_MAX;

    (void)SAL_MemSet((void *)uiDiv, 0x00U, sizeof(uiDiv));
    uiSrchSrc   = 0xFFFFFFFFUL;
    iLastIdx    = (int32_t)CLOCK_SRC_MAX_NUM - 1L;

    for (iIdx = iLastIdx ; iIdx >= 0L ; iIdx--)
    {
        if (stMicomClockSource[iIdx] == 0UL)
        {
            continue;
        }

        if ((stMicomClockSource[iIdx] >= (uint32_t)CLOCK_PCLKCTRL_MAX_FCKS) \
                && (eType == CLOCK_PCLKCTRL_TYPE_XXX) )
        {
            continue;
        }

        /* divider mode */
        uiErrDiv = CLOCK_DevCalPclkDiv(     \
                psPclkCtrl,                 \
                &uiDivDiv,                  \
                stMicomClockSource[iIdx],   \
                /*CLOCK_PCLKCTRL_DIV_MIN+1, \*/
                uiDivMax+1UL                \
                );

        uiErr[iIdx] = uiErrDiv;
        uiDiv[iIdx] = uiDivDiv;
        uiMd        = (uint32_t)tPclkSel;

        if (uiSrchSrc == 0xFFFFFFFFUL)
        {
            uiSrchSrc           = (uint32_t)iIdx;
            psPclkCtrl->uiMd    = uiMd;
        }
        else
        {
            /* find similar clock */
            if (uiErr[iIdx] < uiErr[uiSrchSrc])
            {
                uiSrchSrc           = (uint32_t)iIdx;
                psPclkCtrl->uiMd    = uiMd;
            }
            else
            {
                ;
            }
        }
    }

    switch(uiSrchSrc)
    {
        case (uint32_t)CLOCK_MPLL_0:
        {
            psPclkCtrl->uiSel = (uint32_t)CLOCK_MPCLKCTRL_SEL_PLL0;
            break;
        }
        case (uint32_t)CLOCK_MPLL_1:
        {
            psPclkCtrl->uiSel = (uint32_t)CLOCK_MPCLKCTRL_SEL_PLL1;
            break;
        }
        case (uint32_t)CLOCK_MPLL_DIV_0:
        {
            psPclkCtrl->uiSel = (uint32_t)CLOCK_MPCLKCTRL_SEL_PLL0DIV;
            break;
        }

        case (uint32_t)CLOCK_MPLL_DIV_1:
        {
            psPclkCtrl->uiSel = (uint32_t)CLOCK_MPCLKCTRL_SEL_PLL1DIV;
            break;
        }

        case (uint32_t)CLOCK_MPLL_XIN:
        {
            psPclkCtrl->uiSel = (uint32_t)CLOCK_MPCLKCTRL_SEL_XIN;
            break;
        }

        default:
        {
            iRet = -1;
            break;
        }
    }

    if(iRet != 0)
   	{
        return -1;
   	}

    psPclkCtrl->uiDivVal    = uiDiv[uiSrchSrc];

    if ((psPclkCtrl->uiDivVal >= ((uint32_t)CLOCK_PCLKCTRL_DIV_MIN + 1UL)) && \
            (psPclkCtrl->uiDivVal <= (uiDivMax + 1UL)))
    {
        psPclkCtrl->uiDivVal -= 1UL;
    }
    else
    {
        return -1;
    }

    psPclkCtrl->uiFreq  = stMicomClockSource[uiSrchSrc]/(psPclkCtrl->uiDivVal + 1UL);

    return 0;
}

static void CLOCK_DevResetClkSrc
(
    int32_t                              iId
)
{
    if (iId >= (int32_t)CLOCK_SRC_MAX_NUM)
    {
        return;
    }

    if (iId < (int32_t)CLOCK_PLL_MAX_NUM)
    {
        stMicomClockSource[iId] = CLOCK_GetPllRate(iId);
        stMicomClockSource[CLOCK_PLL_MAX_NUM + iId] = stMicomClockSource[iId] /
            (CLOCK_DevGetPllDiv(iId) + 1UL);
    }
}

void CLOCK_Init
(
    void
)
{
    static int32_t iInitialized = 0;
    int32_t iIdx;

    if (iInitialized == 1L)
    {
        return;
    }

    iInitialized = 1;

#if 0 //Rollback
    /*
       Change the PLL rate for low current
    */

    // Stop using PLLs
    SAL_WriteReg(0x03000301UL, (uint32_t)MCU_BSP_CKC_BASE+(uint32_t)CLOCK_MCKC_CLKCTRL);

    // Drop  PLL0 : 1200 -> 600  MHz
    CLOCK_DevWritePll(
            (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL0PMS,
            1UL/*En*/,
            1UL/*P*/, 100UL/*M*/, 1UL/*S*/
            );

    // Drop  PLL1 : 1500 -> 750  MHz
    CLOCK_DevWritePll(
            (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL1PMS,
            1UL/*En*/,
            1UL/*P*/, 125UL/*M*/, 1UL/*S*/
            );

    // Reset CPU/BUS/EFL rate (300   / 187.5 / 150   MHz)
    SAL_WriteReg(0x11002110UL, (uint32_t)MCU_BSP_CKC_BASE+(uint32_t)CLOCK_MCKC_CLKCTRL);

    // Reset CPU/BUS/EFL rate (187.5 / 93.75 / 150   MHz)
    //SAL_WriteReg(0x11002321UL, (uint32_t)MCU_BSP_CKC_BASE+(uint32_t)CLOCK_MCKC_CLKCTRL);

    // Reset CPU/BUS/EFL rate (125   / 62.5  / 150   MHz)
    //SAL_WriteReg(0x11002522UL, (uint32_t)MCU_BSP_CKC_BASE+(uint32_t)CLOCK_MCKC_CLKCTRL);
#endif

    for (iIdx = 0L ; iIdx < ((int32_t)CLOCK_PLL_MAX_NUM * 2L) ; iIdx++)
    {
        stMicomClockSource[iIdx] = 0;
    }

    stMicomClockSource[CLOCK_PLL_MAX_NUM * 2]       = (uint32_t)CLOCK_XIN_CLK_RATE;
    stMicomClockSource[(CLOCK_PLL_MAX_NUM * 2) + 1] = 0UL;

    (void)CLOCK_SetPllDiv((int32_t)CLOCK_MPLL_1, 2);

    for (iIdx=0L ; iIdx < (int32_t)CLOCK_PLL_MAX_NUM ; iIdx++)
    {
        CLOCK_DevResetClkSrc(iIdx);
    }
}

int32_t CLOCK_SetPllDiv
(
    int32_t                              iId,
    uint32_t                              uiPllDiv
)
{
    SALAddr     uiReg;
    CLOCKMpll_t uiMpllId;
    uint32_t      uiOffSet;
    uint32_t      uiRegVa;
    uint32_t      uiRealPllDiv;

    uiReg           = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_CLKDIVC;
    uiMpllId        = (CLOCKMpll_t)iId;

    uiRegVa         = 0;
    uiRealPllDiv    = ((uiPllDiv > 1UL) ? (uiPllDiv - 1UL) : (0UL));

    switch(uiMpllId)
    {
        case CLOCK_MPLL_0:
        case CLOCK_MPLL_1:
        {
            uiOffSet = (3UL-(uint32_t)iId) * 8UL;
            break;
        }

        case CLOCK_MPLL_XIN:
        {
            uiOffSet = 8UL;
            break;
        }

        default:
        {
		    uiOffSet = 0;
            break;
        }
    }

    if(uiOffSet == 0UL)
   	{
        return -1;
   	}

    uiRegVa = (uint32_t)(SAL_ReadReg(uiReg)) & (~(((uint32_t)0xFFUL << uiOffSet)));
    SAL_WriteReg(uiRegVa, uiReg);

    if (uiRealPllDiv != 0UL)
    {
        uiRegVa |= (0x80UL | (uiRealPllDiv & 0x3FUL)) << uiOffSet;
    }
    else
    {
        uiRegVa |= (((uint32_t)0x01UL) << uiOffSet);
    }

    SAL_WriteReg(uiRegVa, uiReg);

    return 0;
}

uint32_t CLOCK_GetPllRate
(
    int32_t                              iId
)
{
    SALAddr     uiReg;
    CLOCKPll_t  uiPllId;

    uiReg   = (SALAddr)0;
    uiPllId = (CLOCKPll_t)iId;

    if (uiPllId == CLOCK_PLL_MICOM_0)
    {
        uiReg = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL0PMS;
    }
    else if (uiPllId == CLOCK_PLL_MICOM_1)
    {
        uiReg = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL1PMS;
    }
    else
    {
        return 0;
    }

    return CLOCK_DevGetPllRate(uiReg);
}

int32_t CLOCK_SetPllRate
(
    int32_t                              iId,
    uint32_t                              uiRate
)
{
    SALAddr             uiReg;
    CLOCKPll_t          uiPllId;
    CLOCKMpclkCtrlSel_t tMpclkSel;
    int32_t              iIdx;

    uiReg   = (SALAddr)0;
    uiPllId = (CLOCKPll_t)iId;
    iIdx    = -1;

    if (uiPllId == CLOCK_PLL_MICOM_0)
    {
        uiReg       = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL0PMS;
        tMpclkSel   = CLOCK_MPCLKCTRL_SEL_PLL0;
    }
    else if (uiPllId == CLOCK_PLL_MICOM_1)
    {
        uiReg       = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PLL1PMS;
        tMpclkSel   = CLOCK_MPCLKCTRL_SEL_PLL1;
    }
    else
    {
        return -1;
    }

    iIdx = (int32_t)tMpclkSel;
    (void)CLOCK_DevSetPllRate(uiReg, uiRate);
    stMicomClockSource[iIdx] = CLOCK_DevGetPllRate(uiReg);

    return 0;
}

static int32_t CLOCK_DevFindClkCtrl
(
    CLOCKClkCtrl_t *                    CLKCTRL
)
{
    int32_t iRet;
    uint32_t uiIdx;
    uint32_t uiDivTable[CLOCK_SRC_MAX_NUM];
    uint32_t uiErr[CLOCK_SRC_MAX_NUM];
    uint32_t uiSrchSrc;
    uint32_t uiClkRate;
    //int32_t uiXinFreq = CLKCTRL->uiEn ? (CLOCK_XIN_CLK_RATE/2) : CLOCK_XIN_CLK_RATE;
    uint32_t uiXinFreq;

    iRet        = 0;
    uiXinFreq   = 0;

    if(CLKCTRL == NULL)
    {
        return -1;
    }

    if( CLKCTRL->uiEn != 0UL)
    {
        uiXinFreq = ((uint32_t)CLOCK_XIN_CLK_RATE/2UL);
    }
    else
    {
        uiXinFreq= (uint32_t)CLOCK_XIN_CLK_RATE;
    }

    uiSrchSrc = 0xFFFFFFFFUL;

    if (CLKCTRL->uiFreq <= uiXinFreq)
    {
        CLKCTRL->uiSel  = (uint32_t)CLOCK_MCLKCTRL_SEL_XIN;
        CLKCTRL->uiFreq = uiXinFreq;
        //CLKCTRL->uiConf = CLKCTRL->uiEn ? 1 : 0;

        if( CLKCTRL->uiEn != 0UL)
        {
            CLKCTRL->uiConf = 1;
        }
        else
        {
            CLKCTRL->uiConf= 0;
        }
    }
    else
    {
        (void)SAL_MemSet((void *) uiDivTable, 0x00U, sizeof(uiDivTable));

        for (uiIdx = 0UL ; uiIdx < (uint32_t)CLOCK_SRC_MAX_NUM ; uiIdx++)
        {
            if (stMicomClockSource[uiIdx] == 0UL)
            {
                continue;
            }

            if (CLKCTRL->uiEn != 0UL)
            {
                uiDivTable[uiIdx] = (stMicomClockSource[uiIdx] + (CLKCTRL->uiFreq - 1UL)) \
                                    / CLKCTRL->uiFreq;
                if (uiDivTable[uiIdx] > ((uint32_t)CLOCK_MCLKCTRL_CONFIG_MAX + 1UL))
                {
                    uiDivTable[uiIdx] = (uint32_t)CLOCK_MCLKCTRL_CONFIG_MAX+1UL;
                }
                else if (uiDivTable[uiIdx] < ((uint32_t)CLOCK_MCLKCTRL_CONFIG_MIN + 1UL))
                {
                    uiDivTable[uiIdx] = (uint32_t)CLOCK_MCLKCTRL_CONFIG_MIN+1UL;
                }
                else
                {
                    ; //empty statement
                }

                uiClkRate = stMicomClockSource[uiIdx]/uiDivTable[uiIdx];
            }
            else
            {
                uiClkRate = stMicomClockSource[uiIdx];
            }

            if (CLKCTRL->uiFreq < uiClkRate)
            {
                continue;
            }

            uiErr[uiIdx] = CLKCTRL->uiFreq - uiClkRate;

            if (uiSrchSrc == 0xFFFFFFFFUL)
            {
                uiSrchSrc = uiIdx;
            }
            else
            {
                /* find similar clock */
                if (uiErr[uiIdx] < uiErr[uiSrchSrc])
                {
                    uiSrchSrc = uiIdx;
                }
                /* find even division vlaue */
                else if(uiErr[uiIdx] == uiErr[uiSrchSrc])
                {
                    if ((uiDivTable[uiIdx]%2UL) == 0UL)
                    {
                        uiSrchSrc = uiIdx;
                    }
                }
                else
                {
                    uiSrchSrc = 0xFFFFFFFFUL;
                }
            }

            if (uiErr[uiSrchSrc] == 0UL)
            {
                break;
            }
        }

        if (uiSrchSrc == 0xFFFFFFFFUL)
        {
            return -1;
        }

        switch(uiSrchSrc)
        {
            case (uint32_t)CLOCK_MPLL_0:
            {
                CLKCTRL->uiSel = (uint32_t)CLOCK_MCLKCTRL_SEL_PLL0;
                break;
            }

            case (uint32_t)CLOCK_MPLL_1:
            {
                CLKCTRL->uiSel = (uint32_t)CLOCK_MCLKCTRL_SEL_PLL1;
                break;
            }

            case (uint32_t)CLOCK_MPLL_DIV_0:
            {
                CLKCTRL->uiSel = (uint32_t)CLOCK_MCLKCTRL_SEL_PLL0DIV;
                break;
            }

            case (uint32_t)CLOCK_MPLL_DIV_1:
            {
                CLKCTRL->uiSel = (uint32_t)CLOCK_MCLKCTRL_SEL_PLL1DIV;
                break;
            }

            case (uint32_t)CLOCK_MPLL_XIN:
            {
                CLKCTRL->uiSel = (uint32_t)CLOCK_MCLKCTRL_SEL_XIN;
                break;
            }

            default:
            {
                iRet = -1;
                break;
            }
        }

        if(iRet != 0L)
        {
            return -1;
        }

        if (CLKCTRL->uiEn != 0UL)
        {
            if (uiDivTable[uiSrchSrc] > ((uint32_t)CLOCK_MCLKCTRL_CONFIG_MAX + 1UL))
            {
                uiDivTable[uiSrchSrc] = (uint32_t)CLOCK_MCLKCTRL_CONFIG_MAX + 1UL;
            }
            else if (uiDivTable[uiSrchSrc] <= (uint32_t)CLOCK_MCLKCTRL_CONFIG_MIN)
            {
                uiDivTable[uiSrchSrc] = (uint32_t)CLOCK_MCLKCTRL_CONFIG_MIN + 1UL;
            }
            else
            {
                ; //else
            }

            CLKCTRL->uiFreq = stMicomClockSource[uiSrchSrc] / uiDivTable[uiSrchSrc];
            CLKCTRL->uiConf = uiDivTable[uiSrchSrc] - 1UL;
        }
        else
        {
            CLKCTRL->uiFreq = stMicomClockSource[uiSrchSrc];
            CLKCTRL->uiConf = 0;
        }
    }

    return 0;
}

int32_t CLOCK_SetClkCtrlRate
(
    int32_t                              iId,
    uint32_t                              uiRate
)
{
    SALAddr         uiReg;
    CLOCKClkCtrl_t  sClkCtrl;

    uiReg   = (SALAddr)((uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_CLKCTRL + ((uint32_t)iId * 4UL));

    //sClkCtrl.uiEn = (SAL_ReadReg(uiReg) & (1<<CLOCK_MCLKCTRL_EN_SHIFT)) ? 1 : 0;
    if((SAL_ReadReg(uiReg) & (1UL<<(uint32_t)CLOCK_MCLKCTRL_EN_SHIFT)) != 0UL)
    {
        sClkCtrl.uiEn = 1;
    }
    else
    {
        sClkCtrl.uiEn = 0;
    }

    sClkCtrl.uiFreq = uiRate;

    if (CLOCK_DevFindClkCtrl(&sClkCtrl) != 0L)
    {
        return -1;
    }

    CLOCK_DevWriteClkCtrl(uiReg, sClkCtrl.uiEn, sClkCtrl.uiConf, sClkCtrl.uiSel);

    return 0;
}

uint32_t CLOCK_GetClkCtrlRate
(
    int32_t                              iId
)
{
    SALAddr             uiReg;
    CLOCKClkCtrl_t      sClkCtrl;
    CLOCKMclkCtrlSel_t  tMclkSel;
    uint32_t              uiRegVa;
    uint32_t              uiSrcFreq;
    uint32_t              uiRet;

    uiReg       = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_CLKCTRL + ((uint32_t)iId * 4UL);
    uiRegVa     = 0;
    uiRet       = 0;
    uiRegVa     = SAL_ReadReg(uiReg);

    sClkCtrl.uiSel = ( uiRegVa & \
            ((uint32_t)CLOCK_MCLKCTRL_SEL_MASK << (uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT) ) >> \
                     (uint32_t)CLOCK_MCLKCTRL_SEL_SHIFT;
    tMclkSel = (CLOCKMclkCtrlSel_t)sClkCtrl.uiSel;

    switch (tMclkSel)
    {
        case CLOCK_MCLKCTRL_SEL_XIN:
        {
            uiSrcFreq = (uint32_t)CLOCK_XIN_CLK_RATE;
            break;
        }

        case CLOCK_MCLKCTRL_SEL_PLL0:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_0);
            break;
        }

        case CLOCK_MCLKCTRL_SEL_PLL1:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_1);
            break;
        }

        case CLOCK_MCLKCTRL_SEL_PLL0DIV:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_0) /
                (CLOCK_DevGetPllDiv((int32_t)CLOCK_PLL_MICOM_0)+1UL);
            break;
        }

        case CLOCK_MCLKCTRL_SEL_PLL1DIV:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_1) /
                (CLOCK_DevGetPllDiv((int32_t)CLOCK_PLL_MICOM_1)+1UL);
            break;
        }

        default:
        {
            uiSrcFreq = 0UL;
            break;
        }
    }

    if(uiSrcFreq > 0UL)
    {
        sClkCtrl.uiConf = (uiRegVa & ((uint32_t)CLOCK_MCLKCTRL_CONFIG_MASK << \
                    (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT)) >> \
            (uint32_t)CLOCK_MCLKCTRL_CONFIG_SHIFT;

        sClkCtrl.uiFreq = uiSrcFreq / (sClkCtrl.uiConf + 1UL);
        uiRet           = (uint32_t)sClkCtrl.uiFreq;
    }

    return uiRet;
}

int32_t CLOCK_IsPeriEnabled
(
    int32_t                              iId
)
{
    CLOCKPeri_t uiPeriOffset;
    SALAddr     uiReg;

    uiPeriOffset    = CLOCK_PERI_SFMC;
    uiReg           = ((uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PCLKCTRL) \
                      + (((uint32_t)iId - (uint32_t)uiPeriOffset) * 4UL);

    return ((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT)) != 0UL) ? 1L : 0L;
}

int32_t CLOCK_EnablePeri
(
    int32_t                              iId
)
{
    CLOCKPeri_t uiPeriOffset;
    SALAddr     uiReg;

    uiPeriOffset    = CLOCK_PERI_SFMC;
    uiReg           = (uint32_t)CLOCK_BASE_ADDR+(uint32_t)CLOCK_MCKC_PCLKCTRL \
                      + (((uint32_t)iId - (uint32_t)uiPeriOffset) * 4UL);
    SAL_WriteReg((SAL_ReadReg(uiReg) | (1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT)), uiReg);

    return 0;
}

int32_t CLOCK_DisablePeri
(
    int32_t                              iId
)
{
    CLOCKPeri_t uiPeriOffset;
    SALAddr uiReg;

    uiPeriOffset    = CLOCK_PERI_SFMC;
    uiReg           = (uint32_t)CLOCK_BASE_ADDR+(uint32_t)CLOCK_MCKC_PCLKCTRL + \
                    (((uint32_t)iId - (uint32_t)uiPeriOffset) * 4UL);

    SAL_WriteReg(SAL_ReadReg(uiReg) & ~(1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT), uiReg);

    return 0;
}

uint32_t CLOCK_GetPeriRate
(
    int32_t                              iId
)
{
    CLOCKPeri_t         uiPeriOffset;
    SALAddr             uiReg;
    uint32_t              uiRegVa;
    uint32_t              uiSrcFreq;
    uint32_t              uiRet;
    CLOCKPclkCtrl_t     sPclkCtrl;
    CLOCKPclkctrlSel_t  uiPclkSel;

    uiPeriOffset    = CLOCK_PERI_SFMC;
    uiReg           = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PCLKCTRL \
                      + (((uint32_t)iId - (uint32_t)uiPeriOffset) * 4UL);
    uiRegVa         = SAL_ReadReg(uiReg);
    uiRet           = 0;
    sPclkCtrl.uiSel = (uiRegVa & ((uint32_t)CLOCK_PCLKCTRL_SEL_MASK \
                << (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT)) >> (uint32_t)CLOCK_PCLKCTRL_SEL_SHIFT;

    uiPclkSel = (CLOCKPclkctrlSel_t)(sPclkCtrl.uiSel);

    switch(uiPclkSel)
    {
        case CLOCK_PCLKCTRL_SEL_PLL0:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_0);
            break;
        }

        case CLOCK_PCLKCTRL_SEL_PLL1:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_1);
            break;
        }

        case CLOCK_PCLKCTRL_SEL_PLL0DIV:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_0) /
                (CLOCK_DevGetPllDiv((int32_t)CLOCK_PLL_MICOM_0) + 1UL);
            break;
        }

        case CLOCK_PCLKCTRL_SEL_PLL1DIV:
        {
            uiSrcFreq = CLOCK_GetPllRate((int32_t)CLOCK_PLL_MICOM_1) /
                (CLOCK_DevGetPllDiv((int32_t)CLOCK_PLL_MICOM_1) + 1UL);
            break;
        }

        case CLOCK_PCLKCTRL_SEL_XIN:
        {
            uiSrcFreq = (uint32_t)CLOCK_XIN_CLK_RATE;
            break;
        }

        default :
        {
            uiSrcFreq = 0UL;
            break;
        }
    }

    if(uiSrcFreq > 0UL)
    {
        sPclkCtrl.uiFreq    = 0;
        sPclkCtrl.uiDivVal  = (uiRegVa & ((uint32_t)CLOCK_PCLKCTRL_DIV_XXX_MASK <<    \
                             (uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT)) >>                  \
                             (uint32_t)CLOCK_PCLKCTRL_DIV_SHIFT;
        sPclkCtrl.uiFreq    = uiSrcFreq / (sPclkCtrl.uiDivVal + 1UL);
        uiRet               = (uint32_t)sPclkCtrl.uiFreq;
    }

    return uiRet;
}

int32_t CLOCK_SetPeriRate
(
    int32_t                              iId,
    uint32_t                              uiRate
)
{
    CLOCKPeri_t     uiPeriOffset;
    SALAddr         uiReg;
    int32_t          iErr;
    CLOCKPclkCtrl_t sPclkCtrl;

    uiPeriOffset            = CLOCK_PERI_SFMC;
    uiReg                   = (uint32_t)CLOCK_BASE_ADDR + (uint32_t)CLOCK_MCKC_PCLKCTRL \
                              + (((uint32_t)iId - (uint32_t)uiPeriOffset) * 4UL);
    iErr                    = 0;
    sPclkCtrl.uiFreq        = uiRate;
    sPclkCtrl.uiPeriName    = (uint32_t)iId;
    sPclkCtrl.uiDivVal      = 0;
    sPclkCtrl.uiMd          = (uint32_t)CLOCK_PCLKCTRL_MODE_DIVIDER;
    sPclkCtrl.uiSel         = (uint32_t)CLOCK_MPCLKCTRL_SEL_XIN;

    if (CLOCK_DevFindPclk(&sPclkCtrl, CLOCK_PCLKCTRL_TYPE_XXX) != 0L)
    {
        //goto tcc_ckc_setperi_failed;
        CLOCK_DevWritePclkCtrl(                         \
                uiReg,                                  \
                (uint32_t)CLOCK_PCLKCTRL_MODE_DIVIDER,    \
                (uint32_t)SALDisabled,                    \
                (uint32_t)CLOCK_MPCLKCTRL_SEL_XIN,        \
                1UL,                                    \
                (uint32_t)CLOCK_PCLKCTRL_TYPE_XXX         \
                );
        iErr = -1;
    }
    else
    {
        //sPclkCtrl.uiEn = (SAL_ReadReg(uiReg) & (1<<CLOCK_PCLKCTRL_EN_SHIFT)) ? 1 : 0;
        if ((SAL_ReadReg(uiReg) & (1UL << (uint32_t)CLOCK_PCLKCTRL_EN_SHIFT)) != 0UL)
        {
            sPclkCtrl.uiEn = 1;
        }
        else
        {
            sPclkCtrl.uiEn = 0;
        }

        CLOCK_DevWritePclkCtrl(                 \
                uiReg,                          \
                sPclkCtrl.uiMd,                 \
                sPclkCtrl.uiEn,                 \
                sPclkCtrl.uiSel,                \
                sPclkCtrl.uiDivVal,             \
                (uint32_t)CLOCK_PCLKCTRL_TYPE_XXX \
                );
    }

    return iErr;
}

int32_t CLOCK_IsIobusPwdn
(
    int32_t                              iId
)
{
    SALAddr         uiReg;
    int32_t          iRest;
    CLOCKIobus_t    tIobus;

    tIobus  = (CLOCKIobus_t)iId;

    if ((int32_t)tIobus < (32L * 1L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK0;
    }
    else if ((int32_t)tIobus < (32L * 2L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK1;
    }
    else if ((int32_t)tIobus < (32L * 3L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK2;
    }
    else
    {
        return -1;
    }

    iRest = (int32_t)tIobus % 32L;

    return ((SAL_ReadReg(uiReg) & ((uint32_t)1UL << (uint32_t)iRest)) != 0UL) ? 0L : 1L;
}

int32_t CLOCK_EnableIobus
(
    int32_t                              iId,
    bool                             bEn
)
{
    int32_t iRet;

    if(bEn == SALEnabled)
    {
        if(CLOCK_SetIobusPwdn(iId, SALDisabled) == 0L)
        {
            iRet = CLOCK_SetSwReset(iId, SALDisabled);
        }
        else
        {
            iRet = -1;
        }
    }
    else
    {
        if(CLOCK_SetSwReset(iId, SALEnabled) == 0L)
        {
            iRet = CLOCK_SetIobusPwdn(iId, SALEnabled);
        }
        else
        {
            iRet = -1;
        }
    }

    return iRet;
}

int32_t CLOCK_SetIobusPwdn
(
    int32_t                              iId,
    bool                             bEn
)
{
    SALAddr         uiReg;
    int32_t          iRest;
    CLOCKIobus_t    tIobus;

    tIobus  = (CLOCKIobus_t)iId;

    if ((int32_t)tIobus < (32L * 1L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK0;
    }
    else if ((int32_t)tIobus < (32L * 2L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK1;
    }
    else if ((int32_t)tIobus < (32L * 3L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLK2;
    }
    else
    {
        return -1;
    }

    iRest = (int32_t)tIobus % 32;

    if (bEn == SALEnabled)
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) & ~((uint32_t)1UL << (uint32_t)iRest), uiReg);
    }
    else
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) | ((uint32_t)1UL << (uint32_t)iRest), uiReg);
    }

    return 0;
}

int32_t CLOCK_SetSwReset
(
    int32_t                              iId,
    bool                             bReset
)
{
    SALAddr         uiReg;
    int32_t          iRest;
    CLOCKIobus_t    tIobus;

    tIobus  = (CLOCKIobus_t)iId;

    if ((int32_t)tIobus < (32L * 1L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLKSWR0;
    }
    else if ((int32_t)tIobus < (32L * 2L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLKSWR1;
    }
    else if ((int32_t)tIobus < (32L * 3L))
    {
        uiReg = (uint32_t)MCU_BSP_SUBSYS_BASE + (uint32_t)CLOCK_MCKC_HCLKSWR2;
    }
    else
    {
        return -1;
    }

    iRest = (int32_t)tIobus % 32;

    if (bReset == SALEnabled)
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) & ~((uint32_t)1UL << (uint32_t)iRest), uiReg);
    }
    else
    {
        SAL_WriteReg(SAL_ReadReg(uiReg) | ((uint32_t)1UL << (uint32_t)iRest), uiReg);
    }

    return 0;
}

