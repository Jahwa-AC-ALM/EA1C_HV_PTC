/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_canfd.c                                                       */
/* Version:  V1.00                                                           */
/*===========================================================================*/
/*                                  COPYRIGHT                                */
/*===========================================================================*/
/* Copyright (c) 2016 by Renesas Electronics Europe GmbH,                    */
/*               a company of the Renesas Electronics Corporation            */
/*===========================================================================*/
/* In case of any question please do not hesitate to contact:                */
/*                                                                           */
/*        ABG Software Tool Support                                          */
/*                                                                           */
/*        Renesas Electronics Europe GmbH                                    */
/*        Arcadiastrasse 10                                                  */
/*        D-40472 Duesseldorf, Germany                                       */
/*                                                                           */
/*        e-mail: software_support-eu@lm.renesas.com                         */
/*        FAX:   +49 - (0)211 / 65 03 - 11 31                                */
/*                                                                           */
/*===========================================================================*/
/* Warranty Disclaimer                                                       */
/*                                                                           */
/* Because the Product(s) is licensed free of charge, there is no warranty   */
/* of any kind whatsoever and expressly disclaimed and excluded by Renesas,  */
/* either expressed or implied, including but not limited to those for       */
/* non-infringement of intellectual property, merchantability and/or         */
/* fitness for the particular purpose.                                       */
/* Renesas shall not have any obligation to maintain, service or provide bug */
/* fixes for the supplied Product(s) and/or the Application.                 */
/*                                                                           */
/* Each User is solely responsible for determining the appropriateness of    */
/* using the Product(s) and assumes all risks associated with its exercise   */
/* of rights under this Agreement, including, but not limited to the risks   */
/* and costs of program errors, compliance with applicable laws, damage to   */
/* or loss of data, programs or equipment, and unavailability or             */
/* interruption of operations.                                               */
/*                                                                           */
/* Limitation of Liability                                                   */
/*                                                                           */
/* In no event shall Renesas be liable to the User for any incidental,       */
/* consequential, indirect, or punitive damage (including but not limited    */
/* to lost profits) regardless of whether such liability is based on breach  */
/* of contract, tort, strict liability, breach of warranties, failure of     */
/* essential purpose or otherwise and even if advised of the possibility of  */
/* such damages. Renesas shall not be liable for any services or products    */
/* provided by third party vendors, developers or consultants identified or  */
/* referred to the User by Renesas in connection with the Product(s) and/or  */
/* the Application.                                                          */
/*                                                                           */
/*===========================================================================*/
/* History:                                                                  */
/*              V1.00: Initial version                                       */
/*                                                                           */
/*===========================================================================*/
/*                                                                           */
/* Functions for CAN-FD initialization and testing.                          */
/*                                                                           */
/*===========================================================================*/


/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_device.h"
#include "iodefine.h"
//#include "rscanfd/r_rscanfd.h"
#include "r_rscanfd.h"
//#include "r_canfd.h"
/* Peripheral Includes */
//#include "port/r_port.h"
#include "r_port.h"
#include <string.h>

//#define CAN_CH                              1
/******************************************************************************
* MACRO DEFINITIONS
******************************************************************************/

    
#define RSCAN0_TMSTSp(p)        (*((volatile uint8_t  *)(p)))

/*===========================================================================*/
/* Variables */
/*===========================================================================*/
/* Create Can_FrameType for send and receive data */
 
//Canfd_FrameType CANFDRxFIFOData;





//uint8_t g_canrxFlag;
//uint8_t g_busoffFlag;

void INTRCAN0TRX(void);

void R_CANFD_Deinit(void);

void R_CANFD_Init(void)
{
	
#if 0	
	R_PORT_SetAltFunc(Port0,  0, Alt2, Output); /* CAN0 TX */
	R_PORT_SetAltFunc(Port0,  1, Alt2, Input);  /* CAN0 RX*/
#else
	//CAN Tx
	PORT.PFCAE10 &= 0xFFFDU;
	PORT.PFCE10 &= 0xFFFDU;
	PORT.PFC10 |= 0x0002U;
	PORT.PM10 &= 0xFFFDU;
	PORT.PMC10 |= 0x0002U;

	//CAN Rx
	PORT.PFCAE10 &= 0xFFFEU;
	PORT.PFCE10 &= 0xFFFEU;
	PORT.PFC10 |= 0x0001U;
	PORT.PM10 |= 0x0001U;
	PORT.PMC10 |= 0x0001U;	
#endif
	
	/* Initialize CAN1 and CAN4 into CANFD mode*/
	R_RSCAN0FD_Init(); 
	
}

//#pragma ghs interrupt
void INTRCAN0TRX(void)
{
	uint32_t i ;  
    uint32_t add;
  
    for (i = 0U; i < 255U; i++)
    {
        add = 0xFFD00350U +(0x01U * i);
        if (RSCAN0_TMSTSp(add) != 0x00U)
        {
            RSCAN0_TMSTSp(add) &= 0x00U;
        }
    }
	NOP();
}

//#pragma ghs interrupt
/*
#pragma interrupt R_RSCAN_ReadRx(enable=false, channel=23, fpu=true, callt=false) //eiint23
void R_RSCAN_ReadRx(void)
{
	
	static uint8_t CAN_rxmsg1_backup[8];
	static uint8_t CAN_rxmsg2_backup[8];
	uint8_t back_up_flag=0,i;
	RCFDC0.CFDRFSTS0.UINT32 &= 0xFFFFFFF7U;
	R_RSCANFD_ReadRxFIFOBuffer(&CANFDRxFIFOData); //CANFD CH4 receiving
	RCFDC0.CFDRFPCTR0.UINT32 = 0xff;		//RCFDC0CFDRFPCTR0

	if(CANFDRxFIFOData.ID == 0x111UL)
	{
		g_canrxFlag = 1;
		back_up_flag=0;
		i=0;
		while(i<8u)
		{
			if(CAN_rxmsg1_backup[i] !=CANFDRxFIFOData.DB[i])
			{
				back_up_flag=1u;
			}
			i++;
		}
	
		if(back_up_flag ==0u)
		{
			i=0;
			while(i<8u)
			{				
				//(void)memcpy(&(*(uint8_t*)&CAN_rxmsg1.st), &CANFDRxFIFOData.DB[0], 8);
				i++;
			}
		}else{
			i=0;
			while(i<8u)
			{
				CAN_rxmsg1_backup[i] = CANFDRxFIFOData.DB[i];
				i++;
			}
		}
		//gbl_p.CommTimeout = 400u; // 400 * 2.5 = 1000ms
	}
	else 
	{

		if( CANFDRxFIFOData.ID == 0x115u)
		{
			g_canrxFlag = 1u;
			back_up_flag=0u;
			i=0;
			while(i<8u)
			{
				if(CAN_rxmsg2_backup[i] !=CANFDRxFIFOData.DB[i])
				{
					back_up_flag=1u;
				}
			i++;
			}
			
			if(back_up_flag ==0u)
			{
				i=0u;
				while(i<8u)
				{					
					//(void)memcpy(&(*(uint8_t*)&CAN_rxmsg2.st), &CANFDRxFIFOData.DB[0], 8);
					i++;
				}
			}else{
				i=0u;
				while(i<8u)
				{
					CAN_rxmsg2_backup[i] = CANFDRxFIFOData.DB[i];
					i++;
				}
			}
		}//end if( CANFDRxFIFOData.ID == 0x115u)

		//gbl_p.CommTimeout1 = 400u; // 400 * 2.5 = 1000ms
		
	}//end if(CANFDRxFIFOData.ID == 0x111UL)
	
	if( CANFDRxFIFOData.ID == 0x800u)
	{
		g_canrxFlag = 1u;
	}else{
		CANFDRxFIFOData.ID = 0u;
		CANFDRxFIFOData.DB[0] = 0u;
	}
	
}

//#pragma ghs interrupt
//#pragma interrupt R_RSCAN_Error(enable=false, channel=24, fpu=true, callt=false) //eiint24
void R_RSCAN_Error(void)
{
	//RCFDC0CFDC0ERFL &= ~0x00000018;    
	//RCFDC0CFDC0ERFL &= 0xFFFFFFE7;
    if((RCFDC0.CFDC0STS.UINT32  & 0x00000010u) != 0u)		// RCFDC0CFDC0STS
    {
        g_busoffFlag = 1u;
    }
    RCFDC0.CFDC0ERFL.UINT32 &= 0xFFFF8000u;  //RCFDC0CFDC0ERFL &= 0xFFFF8000;
}

*/

void R_CANFD_Deinit(void)
{
	PORT.PIBC10 &= 0xFCU;
	PORT.PM10 |= 0x03U;
}

void R_CANFD_FIFOCheck(void)
{
	if((RCFDC0.CFDC0STS.UINT32 & 0x00000006U) > 0U)
	{
		R_CANFD_Init();
	}   
}