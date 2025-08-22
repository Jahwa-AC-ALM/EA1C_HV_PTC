/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : r_smc_interrupt.c
* Version          : 1.5.0
* Device(s)        : R7F701695
* Description      : None
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "r_smc_interrupt.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void R_Interrupt_Create(void)
{

}

void r_Config_PWMTMR_interrupt_enable_interrupt(void)
{
    /* Clear INTTAUD0I0 request and enable operation */
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_ENABLED;
}

void r_Config_PWMTMR_interrupt_disable_interrupt(void)
{
    /* Disable INTTAUD0I0 operation and clear request */
    INTC1.ICTAUD0I0.BIT.MKTAUD0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I0.BIT.RFTAUD0I0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_ADCA0_scan_group1_end_interrupt_enable_interrupt(void)
{
    /* Clear INTADCA0I0 request and enable operation */
    INTC1.ICADCA0I0.BIT.RFADCA0I0 = _INT_REQUEST_NOT_OCCUR;
    INTC1.ICADCA0I0.BIT.MKADCA0I0 = _INT_PROCESSING_ENABLED;
}

void r_Config_ADCA0_scan_group1_end_interrupt_disable_interrupt(void)
{
    /* Disable INTADCA0I0 operation and clear request */
    INTC1.ICADCA0I0.BIT.MKADCA0I0 = _INT_PROCESSING_DISABLED;
    INTC1.ICADCA0I0.BIT.RFADCA0I0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_UART0_interrupt_send_enable_interrupt(void)
{
    /* Clear INTRLIN30UR0 request and enable operation */
    INTC2.ICRLIN30UR0.BIT.RFRLIN30UR0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICRLIN30UR0.BIT.MKRLIN30UR0 = _INT_PROCESSING_ENABLED;
}

void r_Config_UART0_interrupt_send_disable_interrupt(void)
{
    /* Disable INTRLIN30UR0 operation and clear request */
    INTC2.ICRLIN30UR0.BIT.MKRLIN30UR0 = _INT_PROCESSING_DISABLED;
    INTC2.ICRLIN30UR0.BIT.RFRLIN30UR0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_UART0_interrupt_receive_enable_interrupt(void)
{
    /* Clear INTRLIN30UR1 request and enable operation */
    INTC2.ICRLIN30UR1.BIT.RFRLIN30UR1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICRLIN30UR1.BIT.MKRLIN30UR1 = _INT_PROCESSING_ENABLED;
}

void r_Config_UART0_interrupt_receive_disable_interrupt(void)
{
    /* Disable INTRLIN30UR1 operation and clear request */
    INTC2.ICRLIN30UR1.BIT.MKRLIN30UR1 = _INT_PROCESSING_DISABLED;
    INTC2.ICRLIN30UR1.BIT.RFRLIN30UR1 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_UART0_interrupt_error_enable_interrupt(void)
{
    /* Clear INTRLIN30UR2 request and enable operation */
    INTC2.ICRLIN30UR2.BIT.RFRLIN30UR2 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICRLIN30UR2.BIT.MKRLIN30UR2 = _INT_PROCESSING_ENABLED;
}

void r_Config_UART0_interrupt_error_disable_interrupt(void)
{
    /* Disable INTRLIN30UR2 operation and clear request */
    INTC2.ICRLIN30UR2.BIT.MKRLIN30UR2 = _INT_PROCESSING_DISABLED;
    INTC2.ICRLIN30UR2.BIT.RFRLIN30UR2 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_INTC_intp0_interrupt_enable_interrupt(void)
{
    /* Clear INTP0 request and enable operation */
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_ENABLED;
}

void r_Config_INTC_intp0_interrupt_disable_interrupt(void)
{
    /* Disable INTP0 operation and clear request */
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_DISABLED;
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_INTC_intp1_interrupt_enable_interrupt(void)
{
    /* Clear INTP1 request and enable operation */
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_ENABLED;
}

void r_Config_INTC_intp1_interrupt_disable_interrupt(void)
{
    /* Disable INTP1 operation and clear request */
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_DISABLED;
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_WDT0_interrupt_enable_interrupt(void)
{
    /* Clear INTWDTA0 request and enable operation */
    INTC2.ICWDTA0.BIT.RFWDTA0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICWDTA0.BIT.MKWDTA0 = _INT_PROCESSING_ENABLED;
}

void r_Config_WDT0_interrupt_disable_interrupt(void)
{
    /* Disable INTWDTA0 operation and clear request */
    INTC2.ICWDTA0.BIT.MKWDTA0 = _INT_PROCESSING_DISABLED;
    INTC2.ICWDTA0.BIT.RFWDTA0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_INTC_intp11_interrupt_enable_interrupt(void)
{
    /* Clear INTP11 request and enable operation */
    INTC2.ICP11.BIT.RFP11 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP11.BIT.MKP11 = _INT_PROCESSING_ENABLED;
}

void r_Config_INTC_intp11_interrupt_disable_interrupt(void)
{
    /* Disable INTP11 operation and clear request */
    INTC2.ICP11.BIT.MKP11 = _INT_PROCESSING_DISABLED;
    INTC2.ICP11.BIT.RFP11 = _INT_REQUEST_NOT_OCCUR;
}

void eiint56_enable_interrupt(void)
{
    /* Clear INTADCA0ERR request and enable operation */
    INTC2.ICADCA0ERR.BIT.RFADCA0ERR = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICADCA0ERR.BIT.MKADCA0ERR = _INT_PROCESSING_ENABLED;
}

void eiint56_disable_interrupt(void)
{
    /* Disable INTADCA0ERR operation and clear request */
    INTC2.ICADCA0ERR.BIT.MKADCA0ERR = _INT_PROCESSING_DISABLED;
    INTC2.ICADCA0ERR.BIT.RFADCA0ERR = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_OSTM0_interrupt_enable_interrupt(void)
{
    /* Clear INTOSTM0 request and enable operation */
    INTC2.ICOSTM0.BIT.RFOSTM0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICOSTM0.BIT.MKOSTM0 = _INT_PROCESSING_ENABLED;
}

void r_Config_OSTM0_interrupt_disable_interrupt(void)
{
    /* Disable INTOSTM0 operation and clear request */
    INTC2.ICOSTM0.BIT.MKOSTM0 = _INT_PROCESSING_DISABLED;
    INTC2.ICOSTM0.BIT.RFOSTM0 = _INT_REQUEST_NOT_OCCUR;
}

void r_Config_INTP3_FOR_OS_DISPATCH_interrupt_init(void)
{
	/* Disable INTP0 operation and clear request */
	INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_DISABLED;
	INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
	
	/* Set INTP0 setting */
	INTC2.ICP3.BIT.TBP3 = _INT_TABLE_VECTOR;
	INTC2.ICP3.UINT16 &= _INT_PRIORITY_LOWEST;
	INTC2.ICP3.BIT.CTP3 = 0x0;

	INTC2.ICP3.BIT.RFP3 = _INT_REQUEST_NOT_OCCUR;
	INTC2.ICP3.BIT.MKP3 = _INT_PROCESSING_ENABLED;
	
}

void r_Config_INTP3_FOR_OS_DISPATCH_interrupt_Set(void)
{
	INTC2.ICP3.BIT.RFP3 = (0x1U);
}
