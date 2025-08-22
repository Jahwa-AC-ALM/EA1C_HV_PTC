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
* File Name        : Config_DataCRC.c
* Component Version: 1.6.0
* Device(s)        : R7F701695
* Description      : This file implements device driver for Config_DataCRC.
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
#include "Config_DataCRC.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_DataCRC_Create
* Description  : This function initializes the Config_DataCRC module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_DataCRC_Create(void)
{
    DCRA0.CTL = _DCRA_INPUT_32BIT | _DCRA_32_ETHERNET;
    DCRA0.COUT = _DCRA_INIT_DATA;
    /* Synchronization processing */
    g_cg_sync_read = DCRA0.CTL;
    __syncp();

    R_Config_DataCRC_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_DataCRC_InitializeCRCData
* Description  : This function initializes CRC data register with the initial start value
* Arguments    : crc_data -
*                    CRC data
* Return Value : None
***********************************************************************************************************************/
void R_Config_DataCRC_InitializeCRCData(uint32_t crc_data)
{
    DCRA0.COUT = crc_data;
}

/***********************************************************************************************************************
* Function Name: R_Config_DataCRC_Input32bitData
* Description  : This function inputs 32 bit CRC data.
* Arguments    : data -
*                    CRC data
*                data_num -
*                    the data size of CRC data inputed.
* Return Value : None
***********************************************************************************************************************/
void R_Config_DataCRC_Input32bitData(uint32_t * const data, uint32_t data_num)
{
    uint32_t i;
    uint32_t * p_data_address = (uint32_t *)data;

    for(i=0; i<data_num; i++)
    {
        DCRA0.CIN = *p_data_address;
        p_data_address++;
    }
}

/***********************************************************************************************************************
* Function Name: R_Config_DataCRC_GetResult_32bitData
* Description  : This function gets 32bit CRC data.
* Arguments    : data -
*                    CRC data
* Return Value : None
***********************************************************************************************************************/
void R_Config_DataCRC_GetResult_32bitData(uint32_t * const data)
{
    *data = (uint32_t)(DCRA0.COUT);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
