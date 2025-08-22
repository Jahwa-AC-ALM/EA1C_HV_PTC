/***********************************************************************************************************************
* File Name        : CanModule.c
* Version          : 1.0.150
* Device(s)        : R7F701695
* Description      : This file implements main function.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "r_rscanfd.h"
#include "r_canfd.h"
#include "CanModule.h"
#include "Rte.h"
#include "r_rscanfd.h"
#include "r_canfd.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

static CAN_COMM_MOD		st_CanMM_Rx_Data;
//static uint8_t			CanMM_ModeSctOptionResult = MODE_SCTOPTION_DEFAULT;
static CANMM_COM_MODE		CanMMComMode = CANMM_TX_OFF_RX_OFF;


static RxCCUSta_t		st_CanRxCCUSta = {
						.TimeoutThreshold = 500U		//Timeout 500ms
						 };
static TxHVPPSta_t		st_CanTxHvppSta = {
						    .HVPP1StaInterval = 20U,		//Periodic 20ms
						    .HVPP2StaInterval = 20U,		//Periodic 20ms
						    .HVPP3StaInterval = 20U,		//Periodic 20ms
						    .HVPP4StaInterval = 20U		//Periodic 20ms
					  	};
					  


void CanMMReceiveIsr(void)
{
	/*RX ISR*/
	static Canfd_FrameType CANFDRxFIFOData;
	
	//while ((RCFDC0.CFDRFSTS0.UINT32 & 0x00000100u) != 0x0u)
	{
		RCFDC0.CFDRFSTS0.UINT32 = 0x00000001u; // CF0 플래그를 0으로 설정
		
		R_RSCANFD_ReadRxFIFOBuffer(&CANFDRxFIFOData);
		switch(CANFDRxFIFOData.ID)
		{
			case 0x111U:
				//L_ATCU_12
				st_CanRxCCUSta.ReceivedFlag = 1;
				(void)memcpy(&(*(uint8_t*)&st_CanRxCCUSta.Frame.st), &CANFDRxFIFOData.DB[0], 8);
				break;
			case 0x113U:
				//L_ATCU_13
				break;
			case 0x115U:
				//L_ATCU_16
			default:
				break;
		}
		
		INTC1.ICRCANGRECC0.BIT.RFRCANGRECC0 = 0U;
		RCFDC0.CFDC0STS.UINT32 &= 0xFFFFFFF7U;
		RCFDC0.CFDRFPCTR0.UINT32 = 0xffU;
	}
}

void L_ATCU_Receive(uint8_t interval)
{
	if(CanMMComMode == CANMM_TX_OFF_RX_ON || CanMMComMode ==CANMM_TX_ON_RX_ON){
		
		/* st_CanConnMod_RxData [ATCU_12_Receive] */
		if(st_CanRxCCUSta.ReceivedFlag == 1)
		{
			//Recevied
			st_CanRxCCUSta.ReceivedFlag = 0U;
			st_CanRxCCUSta.TimeoutCnt = 0U;
			st_CanRxCCUSta.TimeoutFlag = 0U;  // Timeout Clear
			//Message Set;
			st_CanMM_Rx_Data.st_CanCommModRxData.OpPrmssnSta = st_CanRxCCUSta.Frame.st.PTCOpPermission;
			//st_CanMM_Rx_Data.DrvrSdTyp = st_CanRxCCUSta.Frame.st.rsvd0 ;
			st_CanMM_Rx_Data.st_CanCommModRxData.DrTrgtDty = st_CanRxCCUSta.Frame.st.PTCZone1TgtDty ;
			st_CanMM_Rx_Data.st_CanCommModRxData.PsTrgtDty = st_CanRxCCUSta.Frame.st.PTCZone2TgtDty ;
			st_CanMM_Rx_Data.st_CanCommModRxData.DischrgReq = st_CanRxCCUSta.Frame.st.PTCDischrgReq ;
			st_CanMM_Rx_Data.st_CanCommModRxData.FltMsgTmOutFHPTC1 = st_CanRxCCUSta.Frame.st.FltMsgTimeOutFHPTC1 ;
			st_CanMM_Rx_Data.st_CanCommModRxData.FltMsgTmOutFHPTC2 = st_CanRxCCUSta.Frame.st.FltMsgTimeOutFHPTC2 ;
			st_CanMM_Rx_Data.st_CanCommModRxData.FltMsgTmOutFHPTC3 = st_CanRxCCUSta.Frame.st.FltMsgTimeOutFHPTC3 ;
			st_CanMM_Rx_Data.st_CanCommModRxData.FltMsgTmOutFHPTC4 = st_CanRxCCUSta.Frame.st.FltMsgTimeOutFHPTC4 ;
			st_CanMM_Rx_Data.st_CanCommModRxData.BlwLvl = st_CanRxCCUSta.Frame.st.FrBlowLevel ;
			st_CanMM_Rx_Data.st_CanCommModRxData.BlwLvlSigVaildSta = st_CanRxCCUSta.Frame.st.FrBlowLevelSigValid ;
			st_CanMM_Rx_Data.st_CanCommModRxData.BlwFltSta = st_CanRxCCUSta.Frame.st.FrBlowFlt ;
			//st_CanMM_Rx_Data.PassBlwLvl = st_CanRxCCUSta.Frame.st.PTCZone1TgtDty ;
			st_CanMM_Rx_Data.RxDataTimeoutSta = st_CanRxCCUSta.TimeoutFlag;
			
			(void)Rte_Write_CanMM_CanCommMod_RxData(&st_CanMM_Rx_Data);
			
		}else{
			/* Time Out Check */
			if(st_CanRxCCUSta.TimeoutFlag == 0U)
			{
				st_CanRxCCUSta.TimeoutCnt += interval;
				if(st_CanRxCCUSta.TimeoutCnt > st_CanRxCCUSta.TimeoutThreshold)
				{
					st_CanRxCCUSta.TimeoutFlag = 1U;
					st_CanMM_Rx_Data.RxDataTimeoutSta = st_CanRxCCUSta.TimeoutFlag;
					(void)Rte_Write_CanMM_CanCommMod_RxData(&st_CanMM_Rx_Data);
				}
			}
		}
	}	
}

void L_RHPTC_MessageSend(uint8_t interval)
{
	
	if(CanMMComMode == CANMM_TX_ON_RX_OFF || CanMMComMode == CANMM_TX_ON_RX_ON)
	{
		
		//READ
		(void)Rte_Read_CanCommMod_CanMM_TxData(&(st_CanTxHvppSta.stHVPPMsgData));
		
		st_CanTxHvppSta.HVPP1StaCnt += interval;
		st_CanTxHvppSta.HVPP2StaCnt += interval;
		st_CanTxHvppSta.HVPP3StaCnt += interval;
		st_CanTxHvppSta.HVPP4StaCnt += interval;
		
		// For Periodic Message
		if((st_CanTxHvppSta.HVPP1StaInterval !=0U) &&(st_CanTxHvppSta.HVPP1StaCnt == st_CanTxHvppSta.HVPP1StaInterval))
		{
			//Cnt Clear
			st_CanTxHvppSta.HVPP1StaCnt = 0;
			
			//Send
			(void)R_CAN0_Tx(0, L_RHPTC_01_ID, (uint8_t *)&(st_CanTxHvppSta.stHVPPMsgData.st_CanHVPP1StaTxData));
		}
		
		if((st_CanTxHvppSta.HVPP2StaInterval !=0U) &&(st_CanTxHvppSta.HVPP2StaCnt == st_CanTxHvppSta.HVPP2StaInterval))
		{
			//Cnt Clear
			st_CanTxHvppSta.HVPP2StaCnt = 0;
			
			//Send
			(void)R_CAN0_Tx(1, L_RHPTC_02_ID, (uint8_t *)&(st_CanTxHvppSta.stHVPPMsgData.st_CanHVPP2FltTxData));
		}
		
		if((st_CanTxHvppSta.HVPP3StaInterval !=0U) &&(st_CanTxHvppSta.HVPP3StaCnt == st_CanTxHvppSta.HVPP3StaInterval))
		{
			//Cnt Clear
			st_CanTxHvppSta.HVPP3StaCnt = 0;
			
			//Send
			(void)R_CAN0_Tx(2, L_RHPTC_03_ID, (uint8_t *)&(st_CanTxHvppSta.stHVPPMsgData.st_CanHVPP3StaTxData));
		}
		
		if((st_CanTxHvppSta.HVPP4StaInterval !=0U) &&(st_CanTxHvppSta.HVPP4StaCnt == st_CanTxHvppSta.HVPP4StaInterval))
		{
			//Cnt Clear
			st_CanTxHvppSta.HVPP4StaCnt = 0;
			
			//Send
			(void)R_CAN0_Tx(3, L_RHPTC_04_ID, (uint8_t *)&(st_CanTxHvppSta.stHVPPMsgData.st_CanHVPP4FltTxData));
		}
	}else{
		/* Tx Off Mode -- Not Working*/
	}
}

void CanMMChangeComMode(CANMM_COM_MODE mode)
{
	CanMMComMode = mode;
	if((mode == CANMM_TX_OFF_RX_OFF)||(mode == CANMM_TX_ON_RX_OFF))
	{
		//RECV ISR OFF
		(void)R_RSCAN_Interrupt_Receive_Disable_interrupt();
	}else{ 
		/* (mode == CANMM_TX_OFF_RX_ON)||(mode == CANMM_TX_ON_RX_ON) */
		//RECV ISR ON
		(void)R_RSCAN_Interrupt_Receive_Enable_interrupt();
	}
}