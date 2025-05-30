// SPDX-License-Identifier: Apache-2.0

/*
***************************************************************************************************
*
*   FileName : reg_phys.h
*
*   Copyright (c) Telechips Inc.
*
*   Description :
*
*
***************************************************************************************************
*/

#ifndef REG_PHYS_HEADER
#define REG_PHYS_HEADER


/* Part 11. MICOM */
#define MCU_BSP_CAN_FD_BASE             (0xA0000000UL)
#define MCU_BSP_ADC_0_BASE              (0xA0080000UL)
#define MCU_BSP_ADC_1_BASE				(0xA0090000UL)
#define MCU_BSP_GPSB_BASE               (0xA0100000UL)
#define MCU_BSP_UART_BASE               (0xA0200000UL)
#define MCU_BSP_UART_CONF_BASE          (0xA02F0000UL)
#define MCU_BSP_I2C_BASE                (0xA0400000UL)
#define MCU_BSP_ICTC_BASE               (0xA0600000UL)
#define MCU_BSP_PWM_BASE                (0xA0700000UL)
#define MCU_BSP_PWM_CFG_BASE            (0xA07F0000UL)
#define MCU_BSP_GDMA_BASE               (0xA0800000UL)
#define MCU_BSP_I2S_BASE                (0xA0880000UL)
#define MCU_BSP_GMAC_BASE               (0xA0900000UL)
#define MCU_BSP_HSM_BASE                (0xA0980000UL)
#define MCU_BSP_CRYPTO_BASE             (0xA09B0000UL)
#define MCU_BSP_MBOX_BASE               (0xA09F0000UL)

#define MCU_BSP_SFMC_BASE               (0xA0F00000UL)
#define MCU_BSP_GIC_BASE                (0xA0F10000UL)
#define MCU_BSP_SUBSYS_BASE             (0xA0F20000UL)
#define MCU_BSP_R5_CONF_BASE            (0xA0F21000UL)
#define MCU_BSP_GPIO_BASE               (0xA0F22000UL)
#define MCU_BSP_WDT_BASE                (0xA0F23000UL)
#define MCU_BSP_CKC_BASE                (0xA0F24000UL)
#define MCU_BSP_CMU_BASE                (0xA0F25000UL)
#define MCU_BSP_SYSSM_BASE              (0xA0F26000UL)
#define MCU_BSP_DSE_BASE                (0xA0F27000UL)
#define MCU_BSP_PMU_BASE                (0xA0F28000UL)
#define MCU_BSP_FMU_BASE                (0xA0F28400UL)
#define MCU_BSP_PMIO_BASE               (0xA0F28800UL)
#define MCU_BSP_RTC_BASE                (0xA0F28C00UL)
#define MCU_BSP_TIMER_BASE              (0xA0F2A000UL)

/*  for reference address
#define MBOX_CMD_FIFO_TXD_ADDR          (MCU_BSP_MBOX_BASE)
#define MBOX_CMD_FIFO_RXD_ADDR          (MCU_BSP_MBOX_BASE + 0x20UL)
#define MBOX_CTRL_ADDR                  (MCU_BSP_MBOX_BASE + 0x40UL)
#define MBOX_CMD_FIFO_STS_ADDR          (MCU_BSP_MBOX_BASE + 0x44UL)
*/
#endif /* REG_PHYS_HEADER */

