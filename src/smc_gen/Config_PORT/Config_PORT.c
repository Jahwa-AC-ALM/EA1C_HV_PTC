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
* File Name        : Config_PORT.c
* Component Version: 1.7.0
* Device(s)        : R7F701695
* Description      : This file implements device driver for Config_PORT.
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
#include "Config_PORT.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_PORT_Create
* Description  : This function initializes the PORT
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_PORT_Create(void)
{
    JTAG.JPIBC0 = _PORT_JPIBC_INIT;
    PORT.PIBC0 = _PORT_PIBC_INIT;
    PORT.PIBC8 = _PORT_PIBC_INIT;
    PORT.PIBC9 = _PORT_PIBC_INIT;
    PORT.PIBC10 = _PORT_PIBC_INIT;
    JTAG.JPBDC0 = _PORT_JPBDC_INIT;
    PORT.PBDC0 = _PORT_PBDC_INIT;
    PORT.PBDC8 = _PORT_PBDC_INIT;
    PORT.PBDC9 = _PORT_PBDC_INIT;
    PORT.PBDC10 = _PORT_PBDC_INIT;
    JTAG.JPM0 = _PORT_JPM_INIT;
    PORT.PM0 = _PORT_PM_INIT;
    PORT.PM8 = _PORT_PM_INIT;
    PORT.PM9 = _PORT_PM_INIT;
    PORT.PM10 = _PORT_PM_INIT;
    JTAG.JPMC0 = _PORT_JPMC_INIT;
    PORT.PMC0 = _PORT_PMC_INIT;
    PORT.PMC8 = _PORT_PMC_INIT;
    PORT.PMC9 = _PORT_PMC_INIT;
    PORT.PMC10 = _PORT_PMC_INIT;
    PORT.PIPC0 = _PORT_PIPC_INIT;
    PORT.PIPC10 = _PORT_PIPC_INIT;
    /* JPORT0 setting */
    JTAG.JPU0 = _PORT_JPUn0_PULLUP_OFF | _PORT_JPUn1_PULLUP_OFF | _PORT_JPUn2_PULLUP_OFF | _PORT_JPUn3_PULLUP_OFF | 
                _PORT_JPUn5_PULLUP_OFF;
    JTAG.JPD0 = _PORT_JPDn0_PULLDOWN_OFF | _PORT_JPDn1_PULLDOWN_OFF | _PORT_JPDn2_PULLDOWN_OFF | 
                _PORT_JPDn3_PULLDOWN_OFF | _PORT_JPDn4_PULLDOWN_ON | _PORT_JPDn5_PULLDOWN_OFF;
    JTAG.JPIS0 = _PORT_JPIS0_DEFAULT_VALUE | _PORT_JPISn0_TYPE_SHMT4 | _PORT_JPISn1_TYPE_SHMT4 | 
                 _PORT_JPISn2_TYPE_SHMT4 | _PORT_JPISn3_TYPE_SHMT4 | _PORT_JPISn5_TYPE_SHMT4;
    JTAG.JPISA0 = _PORT_JPISAn0_TYPE_SHMT1_OR_SHMT4 | _PORT_JPISAn2_TYPE_SHMT1_OR_SHMT4 | 
                  _PORT_JPISAn3_TYPE_SHMT1_OR_SHMT4;
    JTAG.JPM0 = _PORT_JPM0_DEFAULT_VALUE | _PORT_JPMn0_MODE_UNUSED | _PORT_JPMn1_MODE_UNUSED | 
                _PORT_JPMn2_MODE_UNUSED | _PORT_JPMn3_MODE_INPUT | _PORT_JPMn4_MODE_INPUT | _PORT_JPMn5_MODE_UNUSED;
    JTAG.JPIBC0 = _PORT_JPIBCn3_INPUT_BUFFER_ENABLE | _PORT_JPIBCn4_INPUT_BUFFER_ENABLE;
    /* PORT0 setting */
    PORT.PU0 = _PORT_PUn0_PULLUP_ON | _PORT_PUn1_PULLUP_ON | _PORT_PUn2_PULLUP_ON | _PORT_PUn3_PULLUP_ON;
    PORT.PIS0 = _PORT_PIS0_DEFAULT_VALUE | _PORT_PISn0_TYPE_SHMT4 | _PORT_PISn1_TYPE_SHMT4 | _PORT_PISn2_TYPE_SHMT4 | 
                _PORT_PISn3_TYPE_SHMT4;
    PORT.PM0 = _PORT_PM0_DEFAULT_VALUE | _PORT_PMn0_MODE_INPUT | _PORT_PMn1_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | 
               _PORT_PMn3_MODE_UNUSED;
    PORT.PIBC0 = _PORT_PIBCn0_INPUT_BUFFER_ENABLE;
    /* PORT8 setting */
    PORT.PU8 = _PORT_PUn0_PULLUP_ON | _PORT_PUn1_PULLUP_ON;
    PORT.PM8 = _PORT_PM8_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED;
    /* PORT9 setting */
    PORT.PU9 = _PORT_PUn0_PULLUP_ON | _PORT_PUn1_PULLUP_ON;
    PORT.PM9 = _PORT_PM9_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED;
    /* PORT10 setting */
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PDSC10 = _PORT_PDSCn3_SLOW_MODE_SELECT | _PORT_PDSCn4_SLOW_MODE_SELECT | _PORT_PDSCn5_SLOW_MODE_SELECT | 
                  _PORT_PDSCn6_SLOW_MODE_SELECT;
    PORT.PDSC10 = (uint32_t) ~(_PORT_PDSCn3_SLOW_MODE_SELECT | _PORT_PDSCn4_SLOW_MODE_SELECT | 
                  _PORT_PDSCn5_SLOW_MODE_SELECT | _PORT_PDSCn6_SLOW_MODE_SELECT);
    PORT.PDSC10 = _PORT_PDSCn3_SLOW_MODE_SELECT | _PORT_PDSCn4_SLOW_MODE_SELECT | _PORT_PDSCn5_SLOW_MODE_SELECT | 
                  _PORT_PDSCn6_SLOW_MODE_SELECT;
    PORT.PPCMD10 = _WRITE_PROTECT_COMMAND;
    PORT.PODC10 = _PORT_PODCn3_PUSH_PULL | _PORT_PODCn4_PUSH_PULL | _PORT_PODCn5_PUSH_PULL | _PORT_PODCn6_PUSH_PULL;
    PORT.PODC10 = (uint32_t) ~(_PORT_PODCn3_PUSH_PULL | _PORT_PODCn4_PUSH_PULL | _PORT_PODCn5_PUSH_PULL | 
                  _PORT_PODCn6_PUSH_PULL);
    PORT.PODC10 = _PORT_PODCn3_PUSH_PULL | _PORT_PODCn4_PUSH_PULL | _PORT_PODCn5_PUSH_PULL | _PORT_PODCn6_PUSH_PULL;
    PORT.PBDC10 = _PORT_PBDCn3_MODE_DISABLED | _PORT_PBDCn4_MODE_DISABLED | _PORT_PBDCn5_MODE_DISABLED | 
                  _PORT_PBDCn6_MODE_DISABLED;
    PORT.PU10 = _PORT_PUn0_PULLUP_OFF | _PORT_PUn1_PULLUP_OFF | _PORT_PUn2_PULLUP_OFF | _PORT_PUn7_PULLUP_ON | 
                _PORT_PUn8_PULLUP_OFF | _PORT_PUn9_PULLUP_OFF | _PORT_PUn10_PULLUP_OFF;
    PORT.PD10 = _PORT_PDn0_PULLDOWN_OFF | _PORT_PDn1_PULLDOWN_OFF | _PORT_PDn2_PULLDOWN_OFF | 
                _PORT_PDn8_PULLDOWN_OFF | _PORT_PDn9_PULLDOWN_OFF | _PORT_PDn10_PULLDOWN_OFF;
    PORT.PIS10 = _PORT_PIS10_DEFAULT_VALUE | _PORT_PISn0_TYPE_SHMT4 | _PORT_PISn1_TYPE_SHMT4 | 
                 _PORT_PISn2_TYPE_SHMT4 | _PORT_PISn7_TYPE_SHMT4 | _PORT_PISn8_TYPE_SHMT4 | _PORT_PISn9_TYPE_SHMT4 | 
                 _PORT_PISn10_TYPE_SHMT1;
    PORT.P10 = _PORT_Pn3_OUTPUT_LOW | _PORT_Pn4_OUTPUT_LOW | _PORT_Pn5_OUTPUT_LOW | _PORT_Pn6_OUTPUT_LOW;
    PORT.PM10 = _PORT_PM10_DEFAULT_VALUE | _PORT_PMn0_MODE_UNUSED | _PORT_PMn1_MODE_UNUSED | _PORT_PMn2_MODE_UNUSED | 
                _PORT_PMn3_MODE_OUTPUT | _PORT_PMn4_MODE_OUTPUT | _PORT_PMn5_MODE_OUTPUT | _PORT_PMn6_MODE_OUTPUT | 
                _PORT_PMn7_MODE_INPUT | _PORT_PMn8_MODE_UNUSED | _PORT_PMn9_MODE_UNUSED | _PORT_PMn10_MODE_UNUSED;
    PORT.PIBC10 = _PORT_PIBCn7_INPUT_BUFFER_ENABLE;
    /* Synchronization processing */
    g_cg_sync_read = JTAG.JPM0;
    __syncp();

    R_Config_PORT_Create_UserInit();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
