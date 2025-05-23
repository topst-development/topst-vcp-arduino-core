// SPDX-License-Identifier: Apache-2.0

/*
***************************************************************************************************
*
*   FileName : mpu.c
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*/

//#include <cache.h>
#include <bsp.h>
#include <mpu.h>
//#include <reg_phys.h>

#ifdef __MPU_ENABLED__

/*****************************************************************************/
/*                               USER SETTING                                */
/*****************************************************************************/

/*** 1. SELECT DMA SIZE - CHOICE ONLY ONE ***/

/*** 2. SET RESION ATTRIBUTES ***/
//Msg(4:3408) 'sMPUTable' has external linkage but is being defined without any previous declaration. MISRA-C:2004 Rule 8.8

/*
***************************************************************************************************
*                                       MPU_EnableRegion
*
* Set the memory attributes for a section of memory with starting address uiAddr
* of the region size defined by reg_size having attributes attrib of region number
*
* @param    uiRegionNumber specifies the number for that memory region.
* @param    uiAddr is the address for which attributes are to be set.
* @param    uiSize specifies the size for that memory region.
* @param    uiAttr specifies the attributes for that memory region.
* @return   None.
*
***************************************************************************************************
*/

static void MPU_EnableRegion
(
    uint32_t                              uiRegionNumber,
    uint32_t                              uiAddr,
    uint32_t                              uiSize,
    uint32_t                              uiAttr
);


/*
***************************************************************************************************
*                                       MPU_GetDMARegiion
*
* Calculate & Get the region size flag
*
* @param    None
* @return   MPU Region size flag
*
***************************************************************************************************
*/

static uint32_t MPU_GetSizeOfRegion
(
    uint8_t                               ucRegionIdx
);

static void MPU_EnableRegion
(
    uint32_t                              uiRegionNumber,
    uint32_t                              uiAddr,
    uint32_t                              uiSize,
    uint32_t                              uiAttr
)
{
    uint32_t  uiAddress;
    uint32_t  uiRegionsize;

    uiAddress       = uiAddr;
    uiRegionsize    = 0;

    //if((sMPUConfig[uiRegionNumber].uiRegionEnable != MPU_REGION_ENABLE) && (uiRegionNumber < MPU_MAX_REGION))
    if ( uiRegionNumber < MPU_MAX_REGION ) //QAC : Dereference of an invalid pointer value of uiRegionNumber
    {
        MPU_WriteControlRegisterConfigurationData( MPU_ARM_CP15_MPU_MEMORY_REG_NUMBER, uiRegionNumber );
        uiRegionsize    = uiSize;
        uiRegionsize    <<= 1;
        uiRegionsize    |= MPU_REGION_EN;
        ARM_DSB();

        MPU_WriteControlRegisterConfigurationData( MPU_ARM_CP15_MPU_REG_BASEADDR,    uiAddress );
        MPU_WriteControlRegisterConfigurationData( MPU_ARM_CP15_MPU_REG_ACCESS_CTRL, uiAttr );
        MPU_WriteControlRegisterConfigurationData( MPU_ARM_CP15_MPU_REG_SIZE_EN,     uiRegionsize );

        ARM_DSB();
    }
    else
    {
        // Error Print
    }
}

static uint32_t MPU_GetSizeOfRegion
(
    uint8_t                               ucRegionIdx
)
{
    uint32_t      uiSize;
    uint32_t      uiI;
    uint32_t      uiMask;

    if(ucRegionIdx == MPU_DMA_INDEX)
    {
        uiSize = ((uint32_t)(&_end_of_nc_dma) - (uint32_t)(&__nc_dmastart));
    }
    else if(ucRegionIdx == MPU_CAN_INDEX)
    {
        uiSize = ((uint32_t)(&_end_of_nc_can) - (uint32_t)(&__nc_canstart));
    }
    else
    {
        ;
    }

    for(uiI = 18u; ; uiI--) /* check from 256k */
    {
        uiMask = (1u << uiI);

        if((uiSize & uiMask) == uiMask)
        {
            break;
        }
    }

    uiI = (uiI - 1u);
    return uiI;
}

void MPU_Init
(
    void
)
{
    MPUConfig_t sMPUTable[ MPU_MAX_REGION ] =
    {
        { MPU_REGION_ENABLE,  MPU_SRAM0_ADDR,         MPU_REGION_512KB,   MPU_NORM_SHARED_WB_WA      | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  0,                      0,                  MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  0,                      0,                  MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_REMAP_ADDR,         MPU_REGION_4MB,     MPU_NORM_NSHARED_WB_NWA    | MPU_PRIV_RO_USER_RO },
        { MPU_REGION_ENABLE,  MPU_PFLASH_ADDR,        MPU_REGION_2MB,     MPU_NORM_NSHARED_WB_NWA    | MPU_PRIV_RO_USER_RO },
        { MPU_REGION_ENABLE,  MPU_DFLASH_ADDR,        MPU_REGION_256KB,   MPU_NORM_NSHARED_WB_NWA    | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_SNOR_ADDR,          MPU_REGION_256MB,   MPU_NORM_NSHARED_NCACHE    | MPU_PRIV_RO_USER_RO },
        { MPU_REGION_ENABLE,  MPU_PERI_ADDR,          MPU_REGION_16MB,    MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_PFLASHCON_ADDR,     MPU_REGION_64KB,    MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_PFLASH_OPTAREA_ADDR,MPU_REGION_16KB,    MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RO },
        { MPU_REGION_ENABLE,  MPU_PFLASH_INT_ADDR,    MPU_REGION_32B,     MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_DFLASHCON_ADDR,     MPU_REGION_64KB,    MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
        { MPU_REGION_ENABLE,  MPU_DFLASH_OPTAREA_ADDR,MPU_REGION_2KB,     MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RO },
        { MPU_REGION_ENABLE,  MPU_DFLASH_INT_ADDR,    MPU_REGION_64B,     MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },
//        { MPU_REGION_ENABLE,  MPU_SFMC_ADDR,          MPU_REGION_4KB,     MPU_STRONG_ORDERED_SHARED  | MPU_PRIV_RW_USER_RW },

        //Msg(4:0686) Array has fewer initializers than its declared size. Default initialization is applied to the remainder of the array elements. MISRA-C:2004 Rule 9.2; REFERENCE - ISO-6.5.7 Semantics
    };
    uint32_t      uiIndex;

    sMPUTable[MPU_CAN_INDEX].uiRegionBase = (uint32_t)&__nc_canstart;
    sMPUTable[MPU_CAN_INDEX].uiRegionSize = MPU_GetSizeOfRegion(MPU_CAN_INDEX);

    sMPUTable[MPU_DMA_INDEX].uiRegionBase = (uint32_t)&__nc_dmastart;
    sMPUTable[MPU_DMA_INDEX].uiRegionSize = MPU_GetSizeOfRegion(MPU_DMA_INDEX);

    for( uiIndex = 0; uiIndex < ( sizeof( sMPUTable ) / sizeof( sMPUTable[ 0 ] ) ) ; uiIndex++ )
    {
        MPU_EnableRegion( uiIndex, sMPUTable[ uiIndex ].uiRegionBase, sMPUTable[ uiIndex ].uiRegionSize, sMPUTable[ uiIndex ].uiRegionAttr);
    }
}

uint32_t MPU_GetDMABaseAddress
(
    void
)
{
    // 1. Ths "__nc_dmastart" value already contains the physical base(0xC0000000). Please reference the linker(your) script file(.ld)
    // 2. The dma address is valid only physical address(memory and peripheral point of view).

    uint32_t  uiDMAStart;

    uiDMAStart  = ( uint32_t )( &__nc_dmastart ); // Physical Offset for 512KB SRAM for execution zero base

    return uiDMAStart;
}

uint32_t MPU_GetCANBaseAddress
(
    void
)
{
    uint32_t  uiCANStart;

    uiCANStart  = ( uint32_t )( &__nc_canstart ); // Physical Offset for 512KB SRAM for execution zero base

    return uiCANStart;
}

#endif

