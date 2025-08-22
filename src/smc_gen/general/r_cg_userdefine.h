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
* File Name        : r_cg_userdefine.h
* Version          : 1.0.150
* Device(s)        : R7F701695
* Description      : User header file for code generation.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

#ifndef USER_DEF_H
#define USER_DEF_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/
/* Start user code for register. Do not edit comment generated here */

#define GATE_ELon		PORT.P10 |= 0x0008U// P10.3
#define GATE_ELoff		PORT.P10 &= 0xFFF7U// P10.3

//#define GATE_ENon		PORT.P0  |= 0x0002U// P0.1
//#define GATE_ENoff		PORT.P0  &= 0xFFFDU// P0.1

#define GATE_Z1on		PORT.P10 |= 0x0010U// P10.4
#define GATE_Z1off		PORT.P10 &= 0xFFEFU// P10.4

#define GATE_Z2on		PORT.P10 |= 0x0020U// P10.5
#define GATE_Z2off		PORT.P10 &= 0xFFDFU// P10.5

#define ZONE_A 			0U
#define ZONE_B 			1U

#define GATE_OFF 		0U
#define GATE_ON  		1U



#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)




//void run(void);
//void calculateADC(void);

	/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/* Start user code for macro define. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
/* Start user code for type define. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
/* Start user code for function. Do not edit comment generated here */

//void allzoneoff(void);
void timer_2_5ms(void);
//void error_check_and_move_root(void);
void CAN_MSG_TX(void);
//void test_zone_error_check_root(void);
void app_main(void);
void adc_timer(void);
void allzoneoff(void);
void zone_control1(void);
void zone_control2(void);

void r_Config_TAUD0_3_interrupt(void);
void r_Config_TAUD0_2_interrupt(void);
void r_Config_TAUD0_1_interrupt(void);
void r_Config_TAUD0_0_interrupt(void);
void r_Config_OSTM0_interrupt(void);
void r_Config_INTC_intp0_interrupt(void);
void r_Config_ADCA0_scan_group1_end_interrupt(void);
/* End user code. Do not edit comment generated here */
#endif
