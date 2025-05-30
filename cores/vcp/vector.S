// SPDX-License-Identifier: Apache-2.0

/*******************************************************************************
  
*   Copyright (c) Telechips Inc.
 
*******************************************************************************/


/*****************************************************
 *
 * vector.S
 * Telechips TCC70xx SoCs Cortex-A7 Single Processor
 *
 * History
 * -------------
 * Created by : SangWon, Lee  2016/8/19
 *
 *****************************************************/
.section	.vector	,"ax"

#define REMAP_MICOM_BASE	0x1B936014
#define COLD_RESET_BASE	0x1B93617C

.global	_vector	
.global ARM_Reserved
.global _start
_start:
_vector:
	ldr pc, =reset_handler
	ldr pc, =ARM_ExceptUndefInstrHndlr
	ldr pc, =ARM_ExceptSwiHndlr
	ldr pc, =ARM_ExceptPrefetchAbortHndlr
	ldr pc, =ARM_ExceptDataAbortHndlr
	ldr pc, =ARM_Reserved
	ldr pc, =ARM_ExceptIrqHndlr
	ldr pc, =ARM_ExceptFiqHndlr

	
reset_handler:
	ldr pc, = reset

ARM_Reserved:
	wfi
	b ARM_Reserved

	.end
