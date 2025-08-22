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
* File Name        : Config_INTC.c
* Component Version: 1.6.0
* Device(s)        : R7F701695
* Description      : This file implements device driver for Config_INTC.
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
#include "Config_INTC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_INTC_Create
* Description  : This function initializes the INTC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_Create(void)
{
    /* Disable INTP0 operation and clear request */
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_DISABLED;
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTP1 operation and clear request */
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_DISABLED;
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    /* Set INTP0 setting */
    INTC2.ICP0.BIT.TBP0 = _INT_TABLE_VECTOR;
    INTC2.ICP0.UINT16 &= _INT_PRIORITY_LEVEL14;
    FCLA0.CTL0_INTPL = _INTC_EDGE_FALLING;
    /* Set INTP1 setting */
    INTC2.ICP1.BIT.TBP1 = _INT_TABLE_VECTOR;
    INTC2.ICP1.UINT16 &= _INT_PRIORITY_LEVEL14;
    FCLA0.CTL1_INTPL = _INTC_EDGE_FALLING;
    /* Synchronization processing */
    g_cg_sync_read = FCLA0.CTL1_INTPL;
    __syncp();
    /* Set INTP0 pin */
    PORT.PIBC0 &= _PORT_CLEAR_BIT1;
    PORT.PBDC0 &= _PORT_CLEAR_BIT1;
    PORT.PM0 |= _PORT_SET_BIT1;
    PORT.PMC0 &= _PORT_CLEAR_BIT1;
    PORT.PFC0 &= _PORT_CLEAR_BIT1;
    PORT.PFCE0 |= _PORT_SET_BIT1;
    PORT.PFCAE0 &= _PORT_CLEAR_BIT1;
    PORT.PMC0 |= _PORT_SET_BIT1;
    /* Set INTP1 pin */
    JTAG.JPIBC0 &= _JPORT_CLEAR_BIT1;
    JTAG.JPBDC0 &= _JPORT_CLEAR_BIT1;
    JTAG.JPM0 |= _JPORT_SET_BIT1;
    JTAG.JPMC0 &= _JPORT_CLEAR_BIT1;
    JTAG.JPFC0 &= _JPORT_CLEAR_BIT1;
    JTAG.JPFCE0 &= _JPORT_CLEAR_BIT1;
    JTAG.JPMC0 |= _JPORT_SET_BIT1;

    R_Config_INTC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Start
* Description  : This function enables INTP0 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Start(void)
{
    /* Clear INTP0 request and enable operation */
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP0_Stop
* Description  : This function disables INTP0 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP0_Stop(void)
{
    /* Disable INTP0 operation and clear request */
    INTC2.ICP0.BIT.MKP0 = _INT_PROCESSING_DISABLED;
    INTC2.ICP0.BIT.RFP0 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP0.UINT16;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP1_Start
* Description  : This function enables INTP1 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP1_Start(void)
{
    /* Clear INTP1 request and enable operation */
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_Config_INTC_INTP1_Stop
* Description  : This function disables INTP1 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_INTC_INTP1_Stop(void)
{
    /* Disable INTP1 operation and clear request */
    INTC2.ICP1.BIT.MKP1 = _INT_PROCESSING_DISABLED;
    INTC2.ICP1.BIT.RFP1 = _INT_REQUEST_NOT_OCCUR;
    /* Synchronization processing */
    g_cg_sync_read = INTC2.ICP1.UINT16;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
