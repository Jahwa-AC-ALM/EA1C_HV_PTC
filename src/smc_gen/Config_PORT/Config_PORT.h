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
* File Name        : Config_PORT.h
* Component Version: 1.7.0
* Device(s)        : R7F701695
* Description      : This file implements device driver for Config_PORT.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_port.h"

#ifndef CFG_Config_PORT_H
#define CFG_Config_PORT_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _PORT_JPM0_DEFAULT_VALUE                  (0xC0U) /* JPM0 default value */
#define _PORT_PM0_DEFAULT_VALUE                   (0xFFF0U) /* PM0 default value */
#define _PORT_PM8_DEFAULT_VALUE                   (0xFFFCU) /* PM8 default value */
#define _PORT_PM9_DEFAULT_VALUE                   (0xFFFCU) /* PM9 default value */
#define _PORT_PM10_DEFAULT_VALUE                  (0xF800U) /* PM10 default value */
#define _PORT_JPIS0_DEFAULT_VALUE                 (0xD0U) /* JPIS0 default value */
#define _PORT_PIS0_DEFAULT_VALUE                  (0xFFF0U) /* PIS0 default value */
#define _PORT_PIS8_DEFAULT_VALUE                  (0xFFFCU) /* PIS8 default value */
#define _PORT_PIS9_DEFAULT_VALUE                  (0xFFFCU) /* PIS9 default value */
#define _PORT_PIS10_DEFAULT_VALUE                 (0xF800U) /* PIS10 default value */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_PORT_Create(void);
void R_Config_PORT_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
