/*===========================================================================*/
/* Project:  F1x StarterKit V3 Sample Software                               */
/* Module :  r_rscanfd.c                                                     */
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
/* Source code for RSCAN-FD functions.                                       */
/*                                                                           */
/*===========================================================================*/

/*===========================================================================*/
/* Includes */
/*===========================================================================*/
#include "r_cg_macrodriver.h"

#include "r_typedefs.h"
#include "iodefine.h"
#include "r_device.h"
#include "r_rscanfd.h"
#include "r_canfd_table.h"


#define getFrame(p)        &(*((Canfd_FrameType *)(p)))




static void R_RSCANFD_SetRxRule(void);



//==================================== END_JDY_Insert ================================

/*****************************************************************************
** Function:    RS_CANFD_init
** Description: Configures the CAN3/CAN4 macros
** Parameter:   None
** Return:      None
******************************************************************************/

void R_RSCAN0FD_Init(void)
{

	/* switch mode to CANFD mode,reset the main registers */
	RCFDC0.CFDGCTR.UINT32 = 0x00000005U;
	RCFDC0.CFDGAFLCFG0.UINT32 = 0x00000000U;

	/* Wait while CAN RAM initialization is ongoing */
	while((RCFDC0.CFDGSTS.UINT32 & 0x00000008U) > 0u) 
	{}

	/* Switch to global/channel reset mode */

	RCFDC0.CFDGCTR.UINT32 &= 0xfffffffbu;	//set the 3rd bit to 0 -- clear CSLPR to 0  from STOP MODE to RESET mode
	RCFDC0.CFDGCTR.UINT32 |= 0x00000001u;  //GMDC[1:0]BIT = 01B  ---ensure from global operation mode to reset mode
	
	/* Wait while CAN RAM initialization is ongoing */
	while(RCFDC0.CFDGSTS.UINT32!=0x01U)
	{}

	RCFDC0.CFDC0CTR.UINT32 &= 0xfffffffbU;	//jdy_add

	//RCFDC0CFDGRMCFG=0x01;	//set to CAN FD mode

	/*ID priority,DLC check is disabled,clkc as CAN clock--PPLLCLK2, overflow stored, */
	RCFDC0.CFDGCFG.UINT32 = 0x00002020U;   //0B 0001 0000 0010 0000

	//clkc=PPLLCLK2=40M
	/*Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 40M/1/80 = 0.5Mbps(500Kbps) */
	RCFDC0.CFDC0NCFG.UINT32 = 0x133a9800u; //jdy_add NTS2=20; NTS1=59; NSJW=20; NBRP=0		// 10011+1 ==>20  111010+1 ==> 59  10011+1 ==>20

	//clkc=PPLLCLK2=80M
	//fcan=40M
	/*Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 40M/1/80 = 0.5Mbps(500Kbps) */
	//	RCFDC0.CFDC0NCFG.UINT32 = 0x133a9801; //jdy_add NTS2=20; NTS1=59; NSJW=20; NBRP=1		// 10011+1 ==>20  111010+1 ==> 59  10011+1 ==>20

	//Bitrate = fCAN/(BRP+1)/(1+TSEG1+TSEG2) = 40M/1/8 = 5Mbps
	//RCFDC0CFDC0DCFG = 0x01140000;            //jdy_add DSJW=2; DTS2=2; DTS1=5; DBRP=0

	R_RSCANFD_SetRxRule();

	/* ==== buffer setting ==== */ 
	//RCFDC0CFDRMNB = 0x0310; //20 bytes data size, 16 receive buffers
	RCFDC0.CFDRMNB.UINT32 = 0x00000003u; //8 bytes data size, 8 receive buffers

	/*Receive FIFO buffer setting*/
	//RCFDC0CFDRFCC0=0x0000F270; //8 buffer depth, 64 data length, FIFO 0 interrupt is disabled, FIFO enabled only in operation mode
    RCFDC0.CFDRFCC0.UINT32=0x00001202u; //8 MSG, 8 data length, FIFO 0 interrupt is enable, FIFO enabled only in operation mode
    RCFDC0.CFDRFCC1.UINT32=0x00001202u;
    RCFDC0.CFDRFCC2.UINT32=0x00001202u;

	/* Set CMPOFIE,THLEIE,MEIE,DEIE disabled*/
	RCFDC0.CFDGCTR.UINT32 &= 0xfffff0ffU;

	/* If GlobalChannel in halt or reset mode */
	if ((RCFDC0.CFDGSTS.UINT32 & 0x03U) != 0U) 
	{
		RCFDC0.CFDGCTR.UINT32 &= 0xfffffffcU; //Switch to communication mode
		
		while ((RCFDC0.CFDGSTS.UINT32 & 0x02U) == 2U) {
		/* While halt mode */
		}
		
		while ((RCFDC0.CFDGSTS.UINT32 & 0x01U) == 1U) {
		/* While reset mode */
		}
	}

	//set TDC in Globle operation mode, in Channel reset mode
	RCFDC0.CFDC0FDCFG.UINT32 |= 0x00050200U; //jdy_add TDC enable, 5 offset with measurement

	RCFDC0.CFDC0FDCFG.UINT32 |= 0x08000000U; //jdy_add enable CH3 TX buffer merged mode

	RCFDC0.CFDC0FDCFG.UINT32 |= 0x40000000U; // CLOE High, Classical CAN only Enable

	/* jdy_add If Channel0 in halt or reset mode */
	if ((RCFDC0.CFDC0STS.UINT32 & 0x03U) != 0U) 
	{
		RCFDC0.CFDC0CTR.UINT32 &= 0xfffffffcU;    //Switch to communication mode bus off 
		
		while ((RCFDC0.CFDC0STS.UINT32 & 0x02U) == 2U) {
		/* While halt mode */
		}
		
		while ((RCFDC0.CFDC0STS.UINT32 & 0x01U) == 1U) {
		/* While reset mode */
		}
	}

	//RSCAN0_CmCTR(CAN_CH) |= 0x00600800;    // Bus Error Interrupt Enable
	RCFDC0.CFDC0CTR.UINT32|= 0x00600800U;	// Bus Error Interrupt Enable		

	//RCFDC0CFDTMIEC0 = 0xFFFFFFFF;	// Transmit buffer Interrupt is enabled

	/*********************************************************************
	*
	*	2025. 08. 05  Interrupt Priority Level 2 --> Level 14 
	*
	**********************************************************************/
	
	/* Disable operation and clear request */
	INTC1.ICRCANGRECC0.BIT.MKRCANGRECC0 = _INT_PROCESSING_DISABLED;
	INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = _INT_REQUEST_NOT_OCCUR;
	
	/* Set TB & PRIORITY */
	INTC1.ICRCANGRECC0.BIT.TBRCANGRECC0 = _INT_TABLE_VECTOR;
	INTC1.ICRCANGRECC0.BIT.P0RCANGRECC0 = 1U;
	INTC1.ICRCANGRECC0.BIT.P1RCANGRECC0 = 1U;
	INTC1.ICRCANGRECC0.BIT.P2RCANGRECC0 = 1U;
	INTC1.ICRCANGRECC0.BIT.P3RCANGRECC0 = 1U;
	INTC1.ICRCANGRECC0.UINT16 &= _INT_PRIORITY_LEVEL14;
	
	/* Processing Enable */
//	INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = _INT_REQUEST_NOT_OCCUR;	// Request Flag Clear
//	INTC1.ICRCANGRECC0.BIT.MKRCANGRECC0 = _INT_PROCESSING_ENABLED;	// MK 0
	
//    INTC1.ICRCANGRECC0.UINT8[0] |= 0x40U;
//    INTC1.ICRCANGRECC0.UINT8[0] &= 0xF8U;
//    INTC1.ICRCANGRECC0.UINT8[0] |= 12U;
//    INTC1.ICRCANGRECC0.UINT8[0] &= 0x7FU;

	/* Disable operation and clear request */
	INTC1.ICRCANGERR0.BIT.MKRCANGERR0 = _INT_PROCESSING_DISABLED;
	INTC1.ICRCANGERR0.BIT.RFRCANGERR0 = _INT_REQUEST_NOT_OCCUR;
	
	/* Set TB & PRIORITY */
	INTC1.ICRCANGERR0.BIT.TBRCANGERR0 = _INT_TABLE_VECTOR;
	INTC1.ICRCANGERR0.UINT16 &= _INT_PRIORITY_LEVEL14;
	
	/* Processing Enable */
	//INTC1.ICRCANGERR0.BIT.RFRCANGERR0 = _INT_REQUEST_NOT_OCCUR;	// Request Flag Clear
	//INTC1.ICRCANGERR0.BIT.MKRCANGERR0 = _INT_PROCESSING_ENABLED;	// MK 0 
	
//    INTC1.ICRCANGERR0.UINT8[0] |= 0x40U;
//    INTC1.ICRCANGERR0.UINT8[0] &= 0xF8U;
//    INTC1.ICRCANGERR0.UINT8[0] |= 12U;
//    INTC1.ICRCANGERR0.UINT8[0] &= 0x7FU;
    
    	RCFDC0.CFDRFCC0.UINT32 |= 0x01u; //set RxFIFO0 to operation mode   
}



/******************************************************************************
** Function:    R_RSCANFD_SetRxRule
** Description: Set all Rx rules for CANfd MODE
** Parameter:   None
** Return:      None
******************************************************************************/

static void R_RSCANFD_SetRxRule(void)
{    	
	
//	uint32_t RxRuleIdx ;
//	unsigned char PageRxRuleIdx;
//	volatile CANFD_RULE_Type* pCRE;
//	const canfd_cre_type CANFD_RX_RULE_TABLE_LIST[8] = {
//	/* CAN 0_CH0 reception rules */    
//	{{0x00000112UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000001UL}}, /* NO.007 : std data frm ID = H'10~1F will be accepted, 64 data length destination RX FIFO buffer0 */
//	{{0x80000801UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000003UL}}, /* NO.001 : std data frm ID = H'20~2F will be accepted, destination Rx Buffer 9 */
//	{{0x00000111UL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000005UL}}, /* NO.002 : std data frm ID = H'30~3F will be accepted, destination Rx Buffer 10 */
//	{{0x000007DFUL, 0xDFFFFFFFUL, 0x00000000UL, 0x00000007UL}}, /* NO.003 : std data frm ID = H'40~4F will be accepted, destination Rx Buffer 11 */
//	{{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}}, /* NO.004 : std data frm ID = H'50 will be accepted, destination Rx Buffer 12 */
//	{{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}}, /* NO.005 : std data frm ID = H'60 will be accepted, destination Rx Buffer 13 */
//	{{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}}, /* NO.006 : std data frm ID = H'70 will be accepted, destination Rx Buffer 14 */
//	{{0x00000000UL, 0x00000000UL, 0x00000000UL, 0x00000000UL}} /* NO.007 : std data frm ID = H'80 will be accepted, destination Rx Buffer 15 */
//	};

//	/* Set Rx rule number per channel */
//	//RCFDC0CFDGAFLCFG0 |= 0x00080000;   //Channel 1 8 rules
//	//RCFDC0CFDGAFLCFG0 |= 0x04000000U;   //jdy_Channel 0 8 rules Channel 1 8 rules
//	RCFDC0.CFDGAFLCFG0.UINT32 |= 0x04000000U; 
//	//RCFDC0CFDGAFLCFG1 |= 0x08000000;   //Channel 4 8rules

//	/* Get access base address of Rx rule */
//	//pCRE = (volatile CANFD_RULE_Type*)(0xFFD01000u);
//	RCFDC0.CFDGAFLECTR.UINT32 |= (0xFFD01000u);
//	//pCRE = (volatile CANFD_RULE_Type*)&(RCFDC0CFDGAFLID0);

//	/* Receive Rule Table Write Enable */
//	//RCFDC0CFDGAFLECTR |= 0x00000100U;	//set bit8 to 1, Receive rule table write is enabled
//	RCFDC0.CFDGAFLECTR.UINT32 |= (0xFFD01000u);

//	/* Copy Rx rule one by one */
//	for (RxRuleIdx = 0U; RxRuleIdx < 3U; RxRuleIdx++) //CAN_RX_RULE_NUM=12, refer to cab_table.h
//	//for (RxRuleIdx = 0U; RxRuleIdx < 16; RxRuleIdx++)	//if it is more than 16 rules, go to another page
//	{
//		PageRxRuleIdx = (uint8_t) (RxRuleIdx & 0x0FU); //CAN_PAGE_RX_RULE_IDX_MASK= 0xF

//		/* Update target Rx rule page if necessary. */
//		if (PageRxRuleIdx == 0U) //RxRuleIdx=0, page=0; RxRuleIdx=16, page=1; RxRuleIdx=32,page=2;...
//		{
//			//RCFDC0CFDGAFLECTR |= RxRuleIdx >> 4U; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
//			RCFDC0.CFDGAFLECTR.UINT32 |= RxRuleIdx >> 4U;
//		}

//		/* Set a single Rx rule.*/
//		pCRE[PageRxRuleIdx] = CANFD_RX_RULE_TABLE_LIST[RxRuleIdx];
//	}

//	/* Rx rule write disable */
//	//RCFDC0CFDGAFLECTR &= 0xfffffeffU;
//	RCFDC0.CFDGAFLECTR.UINT32 &= 0xfffffeffU;

	uint16_t RxRuleIdx ;
    unsigned char PageRxRuleIdx;
    volatile CANFD_RULE_Type* pCRE;

    /* Set Rx rule number per channel */
    //RCFDC0CFDGAFLCFG0 |= 0x00080000;   //Channel 1 8 rules
    RCFDC0.CFDGAFLCFG0.UINT32 |= 0x04000000u;   //jdy_Channel 0 8 rules Channel 1 8 rules
    //RCFDC0CFDGAFLCFG1 |= 0x08000000;   //Channel 4 8rules
    
    /* Get access base address of Rx rule */
    //pCRE = (volatile CANFD_RULE_Type*)&(RCFDC0.CFDGAFLID0.UINT32);
    pCRE = (volatile CANFD_RULE_Type*)(0xFFD01000U);

    /* Receive Rule Table Write Enable */
    RCFDC0.CFDGAFLECTR.UINT32 |= 0x00000100u;	//set bit8 to 1, Receive rule table write is enabled

    /* Copy Rx rule one by one */
    for (RxRuleIdx = 0U; RxRuleIdx < 3U; RxRuleIdx++) //CAN_RX_RULE_NUM=12, refer to cab_table.h
    //for (RxRuleIdx = 0U; RxRuleIdx < 16; RxRuleIdx++)	//if it is more than 16 rules, go to another page
    {
        PageRxRuleIdx = (uint8_t) (RxRuleIdx & 0x0Fu); //CAN_PAGE_RX_RULE_IDX_MASK= 0xF

        /* Update target Rx rule page if necessary. */
        if (PageRxRuleIdx == 0U) //RxRuleIdx=0, page=0; RxRuleIdx=16, page=1; RxRuleIdx=32,page=2;...
        {
            RCFDC0.CFDGAFLECTR.UINT32 |= RxRuleIdx >> 4U; //CAN_RX_RULE_PAGE_IDX_BIT_POS= 4U
        }

        /* Set a single Rx rule.*/
        pCRE[PageRxRuleIdx] = CANFD_RX_RULE_TABLE[RxRuleIdx];
    }

    /* Rx rule write disable */
    RCFDC0.CFDGAFLECTR.UINT32 &= 0xfffffeffu;
}


/*****************************************************************************
** Function:    Canfd_ReadRxFIFOBuffer
** Description: This code shows how to read message from Rx FIFO buffer
** Parameter:   Canfd_FrameType* pFrame - the data will be stored to
** Return:      void  
******************************************************************************/
void R_RSCANFD_ReadRxFIFOBuffer(Canfd_FrameType* pFrame)
{
    const Canfd_FrameType* pRxFIFOBuffer ;
    
    /*check data to RX FIFO buffer 0 */
    if((RCFDC0.CFDRFSTS0.UINT32 & 0x00000001u) == 0x0u)	//
    {   
        pRxFIFOBuffer = (Canfd_FrameType*)(0xFFD06000U);
        *pFrame = pRxFIFOBuffer[0];        

    }
}

/*****************************************************************************
** Function:    Can_ReadRx_buffer
** Description: This code shows how to read message from Rx buffer
** Parameter:   pRxBufIdx - Pointer to Rx buffer that receives frame
** Return:      void   
******************************************************************************/
void Canfd_ReadRxBuffer(Canfd_REC_FrameType* pFrame)
{    
    uint8_t BufIdx;
    uint8_t CRBRCFiBufIdx;
    uint8_t OverwrittenFlag;
    uint32_t TempCRBRCF0;
    
    const Canfd_REC_FrameType* pRxBuffer;
    volatile uint32_t* pCRBRCF;
    //Can_RtnType RtnValue;
    
    /* Judge if new messages to RX buffer are available */
    TempCRBRCF0 = RCFDC0.CFDRMND0.UINT32;	//Receive Buffer New Data Register, if it is true, new data is coming
    
    //TempCRBRCF2 = RCFDC0CFDRMND2;
    //if ((TempCRBRCF0 == CAN_CLR) && (TempCRBRCF1 == CAN_CLR)&& (TempCRBRCF2 == CAN_CLR)) //CAN_CLR==0
    if(TempCRBRCF0 == CAN_CLR) //CAN_CLR==0
    {
        //RtnValue = CAN_RTN_BUFFER_EMPTY;	// buffer empty, no new data
    }
    else
    {
            /* Get Rx buffer that has new message */
            if (TempCRBRCF0 != CAN_CLR) 
            {
                pCRBRCF = (volatile uint32_t *)(0xFFD000A8U);                
                for (BufIdx = 0U; BufIdx < CAN_CRBRCF0_RX_BUF_NUM; ++BufIdx) //CAN_CRBRCF0_RX_BUF_NUM=32
                {
                    if ((TempCRBRCF0 & CAN_1_BIT_MASK) == CAN_SET) //CAN_1_BIT_MASK==0x1; CAN_SET=0x1
                    {
                        break;	//if checked bit is 1, that means there is a new message in corresponding receive buffer 
                    }
                    TempCRBRCF0 = TempCRBRCF0 >> CAN_B1_BIT_POS; //CAN_B1_BIT_POS=0x1
                }
            }
            
            /* Calculate index value in CRBRCFi */
            CRBRCFiBufIdx = BufIdx & CAN_5_BIT_MASK;	//CAN_5_BIT_MASK  0x1fU  0B11111

            do 
            {
                /* Clear Rx complete flag of corresponding Rx buffer */
                do 
                {
                    CLR_BIT(*pCRBRCF, CRBRCFiBufIdx);	//To clear a flag to 0, the program must write 0 to the flag
                } while (GET_BIT(*pCRBRCF, CRBRCFiBufIdx) == CAN_SET);

                /* Read out message from Rx buffer */
                     

                pRxBuffer = (Canfd_REC_FrameType*) (0xFFD02000U);

                *pFrame = pRxBuffer[BufIdx];

                /* Judge if current message is overwritten */
                OverwrittenFlag = (uint8_t)GET_BIT(*pCRBRCF, CRBRCFiBufIdx);
                /* message is overwritten */
                if (OverwrittenFlag == CAN_SET) 
                {
                    /* User process for message overwritten */
                    //Usr_HandleRxBufOverwritten(BufIdx);
                }
            } while (OverwrittenFlag == CAN_SET);

           // RtnValue = CAN_RTN_OK;
    }

   // return RtnValue;
}

/*****************************************************************************
** Function:    R_RSCAN0fd_C3TrmByTxBuf
** Description: This code shows how to transmit message by channel 1.
** Parameter:   TxBufIdx - Pointer to Tx buffer for transmission
                Canfd_FrameType* pFrame: data to be transmitted
** Return:      CAN_RTN_OK   
******************************************************************************/
void R_RSCAN0FD_C0TrmByTxBuf(uint8_t TxBufIdx, const Canfd_FrameType* pFrame)
{  
	volatile uint8_t* pTBSR;
	Canfd_FrameType* pTxBuffer;
	volatile uint8_t* pTBCR;
	uint8_t waitCnt = 10u;

	pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS0);
	pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC0);

	/* ---- Return if Tx Buffer is transmitting. ---- */    
	while( (pTBSR[TxBufIdx] & (uint8_t)0x01u) == 0x01u ) //CAN_TBTST_TRANSMITTING = 1 : Transmission is in progress.
	{
		break;
	}

	/* Clear Tx buffer status */
	// do 
	// {
	//     pTBSR[TxBufIdx] = CAN_CLR;  //CAN_CLR =0 
	// } while (pTBSR[TxBufIdx] != CAN_CLR);

	while(waitCnt != 0u)
	{
		if(pTBSR[0] != CAN_CLR) 
		{
			pTBSR[0] = CAN_CLR;
		}
		waitCnt--;
	}

	/* Store message to tx buffer */
	pTxBuffer = (Canfd_FrameType*)(0xFFD08000U);
	pTxBuffer[TxBufIdx] = *pFrame;
	//RCFDC0CFDTMDF0_0 is msg 0byte

	/* Set transmission request */
	pTBCR[TxBufIdx] = 0x01u; //CAN_TBCR_TRM;

}


void R_CAN0_Tx(uint8_t TxBufferNum, uint32_t Tx_ID, uint8_t* pMSG)
{  
    volatile uint8_t* pTBSR;
    Canfd_FrameType* pTxBuffer;
    volatile uint8_t* pTBCR;
    uint8_t waitCnt = 10;
    //r_CANRtn_t rtnval = CAN_RTN_OK;

    if(TxBufferNum == 0U)
    {
        pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS0);
        pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC0);
    }
    else if(TxBufferNum == 1U)
    {
        pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS1);
        pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC1);
    }
    else if(TxBufferNum == 2U)
    {
        pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS2);
        pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC2);
    }
    else if(TxBufferNum == 3U)
    {
        pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS3);
        pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC3);
    }
    else
    {
        pTBSR = (volatile uint8_t *)&(RCFDC0.CFDTMSTS0);
        pTBCR = (volatile uint8_t *)&(RCFDC0.CFDTMC0);
    }

    /* ---- Return if Tx Buffer is transmitting. ---- */    
    while( (pTBSR[0] & (uint8_t)0x01) == 0x01U ) //CAN_TBTST_TRANSMITTING = 1 : Transmission is in progress.
    {
        //rtnval = CAN_RTN_ERR;
    }

    /* Clear Tx buffer status */
    // do 
    // {
    //     pTBSR[0] = CAN_CLR;  //CAN_CLR =0 
    // } while (pTBSR[0] != CAN_CLR);
    while(waitCnt > 0U)
    {
        if(pTBSR[0] != CAN_CLR)
        {
            pTBSR[0] = CAN_CLR;
        }
        waitCnt--;
    }
    
    
    /* Store message to tx buffer */
    if(TxBufferNum == 0U)
    {
        pTxBuffer = getFrame(0xFFD08000u);
    }
    else if(TxBufferNum == 1U)
    {        
        pTxBuffer = getFrame(0xFFD08080u);
    }
    else if(TxBufferNum == 2U)
    {     
        pTxBuffer = getFrame(0xFFD08100u);
    }
    else if(TxBufferNum == 3U)
    {     
        pTxBuffer = getFrame(0xFFD08180u);
    }
    else
    {     
        pTxBuffer = getFrame(0xFFD08000u);
    }
    //pTxBuffer = (Canfd_FrameType*) &(RCFDC0CFDTMID0);
    pTxBuffer->ID = Tx_ID;
    pTxBuffer->IDE = 0U;
    pTxBuffer->DLC = 8U;
    pTxBuffer->DB[0] = *(uint8_t*)&pMSG[0];
    pTxBuffer->DB[1] = *(uint8_t*)&pMSG[1];
    pTxBuffer->DB[2] = *(uint8_t*)&pMSG[2];
    pTxBuffer->DB[3] = *(uint8_t*)&pMSG[3];
    pTxBuffer->DB[4] = *(uint8_t*)&pMSG[4];
    pTxBuffer->DB[5] = *(uint8_t*)&pMSG[5];
    pTxBuffer->DB[6] = *(uint8_t*)&pMSG[6];
    pTxBuffer->DB[7] = *(uint8_t*)&pMSG[7];
 
    /* Set transmission request */
    pTBCR[0] = 0x01U; //CAN_TBCR_TRM;


}

void R_RSCAN_Interrupt_Receive_Disable_interrupt(void)
{
	INTC1.ICRCANGRECC0.BIT.MKRCANGRECC0 = _INT_PROCESSING_DISABLED;
	INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = _INT_REQUEST_NOT_OCCUR;
}

void R_RSCAN_Interrupt_Receive_Enable_interrupt(void)
{
	/* Processing Enable */
	INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = _INT_REQUEST_NOT_OCCUR;	// Request Flag Clear
	INTC1.ICRCANGRECC0.BIT.MKRCANGRECC0 = _INT_PROCESSING_ENABLED;	// MK 0
}