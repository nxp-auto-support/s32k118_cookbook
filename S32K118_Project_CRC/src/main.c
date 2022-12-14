/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2018, NXP.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * Description:
 * ==========================================================================================
 * The cyclic redundancy check (CRC) module generates 16/32-bit CRC code for error detection.
 * This is a program to show a basic configuration of CRC module following RM steps.
 */

#include "crc.h"
#include "device_registers.h" 	/* include peripheral declarations S32K118 */
#include "clocks_and_modes_S32K11x.h"

void WDOG_disable (void)
{
  WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
  WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value 	*/
  WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

int main(void)
{
	/*!
	 * Initialization
	 * ========================
	 */
	uint8_t test = 0x41;/* test = A */
	uint32_t crc = 0x00000000;

	WDOG_disable();		/* Disable WDOG */
	SOSC_init_40MHz(); 	/* Initialize system oscillator for 40 MHz xtal */
	RUN_mode_48MHz();	/* Init clocks: 48 MHz sys, core and bus,
	  	  	  	  	  	  	  	  	  	24 MHz flash. */

	PCC->PCCn[PCC_CRC_INDEX] |= PCC_PCCn_CGC_MASK;		/* Enable Clock for CRC module */
	crc = CRC_32bits_calculate(&test, 1);				/* Calculate 32-bit CRC */
														/* crc = 547335706 */

	/*!
	 * Wait forever
	 * ========================
	 */
	for(;;)
	{
	}
}
