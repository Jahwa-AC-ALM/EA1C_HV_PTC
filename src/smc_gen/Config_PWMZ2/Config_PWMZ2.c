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
* File Name        : Config_PWMZ2.c
* Component Version: 1.7.0
* Device(s)        : R7F701695
* Description      : This file implements device driver for Config_PWMZ2.
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
#include "Config_PWMZ2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PWMZ2_Create
* Description  : This function initializes the TAUD0 channel.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PWMZ2_Create(void)
{
    /* Disable channel counter operation */
    TAUD0.TT |= (_TAUD_CHANNEL11_COUNTER_STOP | _TAUD_CHANNEL10_COUNTER_STOP);
    /* Disable INTTAUD0I10 operation and clear request */
    INTC1.ICTAUD0I10.BIT.MKTAUD0I10 = _INT_PROCESSING_DISABLED;
    INTC1.ICTAUD0I10.BIT.RFTAUD0I10 = _INT_REQUEST_NOT_OCCUR;
    /* Disable INTTAUD0I11 operation and clear request */
    INTC2.ICTAUD0I11.BIT.MKTAUD0I11 = _INT_PROCESSING_DISABLED;
    INTC2.ICTAUD0I11.BIT.RFTAUD0I11 = _INT_REQUEST_NOT_OCCUR;
    TAUD0.TPS &= _TAUD_CK0_PRS_CLEAR;
    TAUD0.TPS |= _TAUD_CK0_PRE_PCLK_8;
    /* Set channel 10 setting */
    TAUD0.CMOR10 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_MASTER_CHANNEL | 
                   _TAUD_START_TRIGGER_SOFTWARE | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_INTERVAL_TIMER_MODE | 
                   _TAUD_START_INT_GENERATED;
    /* Set compare match register */
    TAUD0.CMUR10 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR10 = _TAUD0_CHANNEL10_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE &= _TAUD_CHANNEL10_DISABLES_OUTPUT_MODE;
    /* Set channel 11 setting */
    TAUD0.CMOR11 = _TAUD_SELECTION_CK0 | _TAUD_COUNT_CLOCK_PCLK | _TAUD_SLAVE_CHANNEL | 
                   _TAUD_START_TRIGGER_MASTER_INT | _TAUD_OVERFLOW_AUTO_CLEAR | _TAUD_ONE_COUNT_MODE | 
                   _TAUD_START_TRIGGER_ENABLE;
    /* Set compare match register */
    TAUD0.CMUR11 = _TAUD_INPUT_EDGE_UNUSED;
    TAUD0.CDR11 = _TAUD0_CHANNEL11_COMPARE_VALUE;
    /* Set output mode setting */
    TAUD0.TOE |= _TAUD_CHANNEL11_ENABLES_OUTPUT_MODE;
    TAUD0.TOM |= _TAUD_CHANNEL11_SYNCHRONOUS_OUTPUT_MODE;
    TAUD0.TOC &= _TAUD_CHANNEL11_OPERATION_MODE1;
    TAUD0.TOL &= _TAUD_CHANNEL11_POSITIVE_LOGIC;
    TAUD0.TDE &= _TAUD_CHANNEL11_DISABLE_DEAD_TIME_OPERATE;
    TAUD0.TDM &= _TAUD_CHANNEL11_DETECTING_DUTY_CYCLE;
    TAUD0.TDL &= _TAUD_CHANNEL11_NORMAL_PHASE;
    TAUD0.TRE &= _TAUD_CHANNEL11_REAL_TIME_OUTPUT_DISABLES;
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TPS;
    __syncp();

    /* Set TAUD0O11 pin */
    PORT.PIBC10 &= _PORT_CLEAR_BIT5;
    PORT.PBDC10 &= _PORT_CLEAR_BIT5;
    PORT.PM10 |= _PORT_SET_BIT5;
    PORT.PMC10 &= _PORT_CLEAR_BIT5;
    PORT.PIPC10 &= _PORT_CLEAR_BIT5;
    PORT.PFC10 &= _PORT_CLEAR_BIT5;
    PORT.PFCE10 &= _PORT_CLEAR_BIT5;
    PORT.PFCAE10 &= _PORT_CLEAR_BIT5;
    PORT.PMC10 |= _PORT_SET_BIT5;
    PORT.PM10 &= _PORT_CLEAR_BIT5;

    R_Config_PWMZ2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_PWMZ2_Start
* Description  : This function starts the TAUD0 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PWMZ2_Start(void)
{
    /* Enable channel counter operation */
    TAUD0.TS |= (_TAUD_CHANNEL11_COUNTER_START | _TAUD_CHANNEL10_COUNTER_START);
}

/***********************************************************************************************************************
* Function Name: R_Config_PWMZ2_Stop
* Description  : This function stop the TAUD0 channel counter.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PWMZ2_Stop(void)
{
    /* Disable channel counter operation */
    TAUD0.TT |= (_TAUD_CHANNEL11_COUNTER_STOP | _TAUD_CHANNEL10_COUNTER_STOP);
    /* Synchronization processing */
    g_cg_sync_read = TAUD0.TT;
    __syncp();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
