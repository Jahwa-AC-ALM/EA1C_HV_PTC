/***********************************************************************************************************************
* File Name        : Rte.c
* Version          : 1.0
* Device(s)        : R7F701695
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "Rte.h"
#include "PWMTmrModule.h"
#include "IoAdcModule.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Module to Module */
static uint8_t					Rte_IoAdcMM_CanMM_SctOption_Data = 0U;

/* Module to SWC & SWC to Module --> */
static CAN_COMM_MOD				Rte_CanMM_CanCommMod_RxData;
static TxHVPPSta_t				Rte_CanCommMod_CanMM_TxData;
static DATA_IN_PROC_RAW_VALUE			Rte_IoAdcMM_DIOProcMod_RawData;
static uint8_t					Rte_IoAdcMM_DIOProcMod_SctOption_Data = 0U;
static SERIAL_COMM_HV_MOD			Rte_UartM_SerialCommMod_LV_RxData;
static SERIAL_COMM_LV_MOD			Rte_UartM_SerialCommMod_HV_RxData;
static SERIAL_COMM_HV_MOD			Rte_SerialCommMod_UartM_HV_TxData;
static SERIAL_COMM_LV_MOD			Rte_SerialCommMod_UartM_LV_TxData;


/* SWC to SWC */
static CAN_COMM_MOD				Rte_CanCommMod_SerialCommMod_Data;
static DATA_IN_PROC_MOD				Rte_DIOProcMod_HV_FailSafeMod_Data;
static DATA_IN_PROC_MOD				Rte_DIOProcMod_HV_SerialCommMod_Data;
static SERIAL_COMM_HV_MOD			Rte_SerialCommMod_LV_CanCommMod_Data;
static SERIAL_COMM_LV_MOD			Rte_SerialCommMod_HV_PTCModeMgntMod_Data;
static PTC_MODE_MGNT_MOD			Rte_PTCModeMgntMod_SerialCommMod_HV_Data;
static PTC_MODE_MGNT_MOD			Rte_PTCModeMgntMod_PTCPwrMgntMod_Data;
static PTC_PWR_MGNT_MOD				Rte_PTCPwrMgntMod_PTCModeMgntMod_Data;
static FAIL_SAFE_MOD				Rte_FailSafeMod_SerialCommMod_Data;

//uint8_t
static uint8_t					Rte_DIOProcMod_CanCommMod_SctOption_Data = 0U;
static uint8_t					Rte_DIOProcMod_PTCModMgntMod_SctOption_Data = 0U;
static uint8_t					Rte_DIOProcMod_SerialCommMod_SctOption_Data = 0U;
static uint8_t					Rte_DIOProcMod_PTCPwrMgntMod_SctOption_Data = 0U;
static uint8_t					Rte_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta = 0U;
static uint8_t					Rte_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect = 0U;
static uint8_t					Rte_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect = 0U;
static FAIL_SAFE_RESULRT			Rte_FailSafeMod_PTCModeMgntMod_FltResults = {0U, 0U};


//Read
void Rte_Read_CanMM_CanCommMod_RxData(CAN_COMM_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		//(void)memcpy(&(*(uint8_t*)&st_CanRxCCUSta.Frame.st), &CANFDRxFIFOData.DB[0], 8);
		(void)memcpy(Data, &Rte_CanMM_CanCommMod_RxData, sizeof(CAN_COMM_MOD));
	}
}

void Rte_Read_CanCommMod_CanMM_TxData(TxHVPP_Msg_DATA_t *Data)
{
	if (Data != NULL_PTR)
	{
		//(void)memcpy(&(*(uint8_t*)&st_CanRxCCUSta.Frame.st), &CANFDRxFIFOData.DB[0], 8);
		(void)memcpy(Data, &Rte_CanCommMod_CanMM_TxData, sizeof(TxHVPP_Msg_DATA_t));
	}
}

void Rte_Read_IoAdcMM_DIOProcMod_RawData(DATA_IN_PROC_RAW_VALUE *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_IoAdcMM_DIOProcMod_RawData, sizeof(DATA_IN_PROC_RAW_VALUE));
	}
}

void Rte_Read_IoAdcMM_DIOProcMod_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_IoAdcMM_DIOProcMod_SctOption_Data;
	}
}

void Rte_Read_UartM_SerialCommMod_LV_RxData(SERIAL_COMM_HV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_UartM_SerialCommMod_LV_RxData, sizeof(SERIAL_COMM_HV_MOD));
	}
}

void Rte_Read_UartM_SerialCommMod_HV_RxData(SERIAL_COMM_LV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_UartM_SerialCommMod_HV_RxData, sizeof(SERIAL_COMM_LV_MOD));
	}
}

void Rte_Read_SerialCommMod_UartM_HV_TxData(SERIAL_COMM_HV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_SerialCommMod_UartM_HV_TxData, sizeof(SERIAL_COMM_HV_MOD));
	}
}

void Rte_Read_SerialCommMod_UartM_LV_TxData(SERIAL_COMM_LV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_SerialCommMod_UartM_LV_TxData, sizeof(SERIAL_COMM_LV_MOD));
	}
}


void Rte_Read_IoAdcMM_CanMM_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_IoAdcMM_CanMM_SctOption_Data;
	}
}

void Rte_Read_CanCommMod_SerialCommMod_Data(CAN_COMM_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_CanCommMod_SerialCommMod_Data, sizeof(CAN_COMM_MOD));
	}
}

void Rte_Read_DIOProcMod_HV_FailSafeMod_Data(DATA_IN_PROC_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_DIOProcMod_HV_FailSafeMod_Data, sizeof(DATA_IN_PROC_MOD));
	}
}

void Rte_Read_DIOProcMod_HV_SerialCommMod_Data(DATA_IN_PROC_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_DIOProcMod_HV_SerialCommMod_Data, sizeof(DATA_IN_PROC_MOD));
	}
}

void Rte_Read_SerialCommMod_LV_CanCommMod_Data(SERIAL_COMM_HV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_SerialCommMod_LV_CanCommMod_Data, sizeof(SERIAL_COMM_HV_MOD));
	}
}

void Rte_Read_SerialCommMod_HV_PTCModeMgntMod_Data(SERIAL_COMM_LV_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_SerialCommMod_HV_PTCModeMgntMod_Data, sizeof(SERIAL_COMM_LV_MOD));
	}
}

void Rte_Read_PTCModeMgntMod_SerialCommMod_HV_Data(PTC_MODE_MGNT_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_PTCModeMgntMod_SerialCommMod_HV_Data, sizeof(PTC_MODE_MGNT_MOD));
	}
}

void Rte_Read_PTCModeMgntMod_PTCPwrMgntMod_Data(PTC_MODE_MGNT_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_PTCModeMgntMod_PTCPwrMgntMod_Data, sizeof(PTC_MODE_MGNT_MOD));
	}
}

void Rte_Read_PTCPwrMgntMod_PTCModeMgntMod_Data(PTC_PWR_MGNT_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_PTCPwrMgntMod_PTCModeMgntMod_Data, sizeof(PTC_PWR_MGNT_MOD));
	}
}

void Rte_Read_FailSafeMod_SerialCommMod_Data(FAIL_SAFE_MOD *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_FailSafeMod_SerialCommMod_Data, sizeof(FAIL_SAFE_MOD));
	}
}

void Rte_Read_DIOProcMod_CanCommMod_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_DIOProcMod_CanCommMod_SctOption_Data;
	}
}

void Rte_Read_DIOProcMod_PTCModMgntMod_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_DIOProcMod_PTCModMgntMod_SctOption_Data;
	}
}

void Rte_Read_DIOProcMod_SerialCommMod_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_DIOProcMod_SerialCommMod_SctOption_Data;
	}
}

void Rte_Read_DIOProcMod_PTCPwrMgntMod_SctOption_Data(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_DIOProcMod_PTCPwrMgntMod_SctOption_Data;
	}
}

void Rte_Read_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta;
	}
}

void Rte_Read_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect;
	}
}

void Rte_Read_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect(uint8_t *Data)
{
	if (Data != NULL_PTR)
	{
		*Data = Rte_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect;
	}
}

void Rte_Read_FailSafeMod_PTCModeMgntMod_FltResults(FAIL_SAFE_RESULRT *Data)
{
	if (Data != NULL_PTR)
	{
		(void)memcpy((uint8_t*)Data, (uint8_t*)&Rte_FailSafeMod_PTCModeMgntMod_FltResults, sizeof(FAIL_SAFE_RESULRT));
	}
}

/********************************************************************************************************* 
*						SRI_Write(Sender) 
**********************************************************************************************************/
void Rte_Write_CanMM_CanCommMod_RxData(CAN_COMM_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_CanMM_CanCommMod_RxData, (uint8_t*)Data, sizeof(CAN_COMM_MOD));
}

void Rte_Write_CanCommMod_CanMM_TxData(CAN_COMM_PROC_TXDATA *Data)
{
	(void)memcpy((uint8_t*)&Rte_CanCommMod_CanMM_TxData, (uint8_t*)Data, sizeof(CAN_COMM_PROC_TXDATA));
}

void Rte_Write_IoAdcMM_DIOProcMod_RawData(DATA_IN_PROC_RAW_VALUE *Data)
{
	(void)memcpy((uint8_t*)&Rte_IoAdcMM_DIOProcMod_RawData, (uint8_t*)Data, sizeof(DATA_IN_PROC_RAW_VALUE));
}

void Rte_Write_IoAdcMM_DIOProcMod_SctOption_Data(uint8_t Data)
{
	Rte_IoAdcMM_DIOProcMod_SctOption_Data = Data;
}

void Rte_Write_IoAdcMM_CanMM_SctOption_Data(uint8_t Data)
{
	Rte_IoAdcMM_CanMM_SctOption_Data = Data;
}

void Rte_Write_UartM_SerialCommMod_LV_RxData(SERIAL_COMM_HV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_UartM_SerialCommMod_LV_RxData, (uint8_t*)Data, sizeof(SERIAL_COMM_HV_MOD));
}

void Rte_Write_UartM_SerialCommMod_HV_RxData(SERIAL_COMM_LV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_UartM_SerialCommMod_HV_RxData, (uint8_t*)Data, sizeof(SERIAL_COMM_LV_MOD));
}

void Rte_Write_SerialCommMod_UartM_HV_TxData(SERIAL_COMM_HV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_SerialCommMod_UartM_HV_TxData, (uint8_t*)Data, sizeof(SERIAL_COMM_HV_MOD));
}

void Rte_Write_SerialCommMod_UartM_LV_TxData(SERIAL_COMM_LV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_SerialCommMod_UartM_LV_TxData, (uint8_t*)Data, sizeof(SERIAL_COMM_LV_MOD));
}



void Rte_Write_CanCommMod_SerialCommMod_Data(CAN_COMM_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_CanCommMod_SerialCommMod_Data, (uint8_t*)Data, sizeof(CAN_COMM_MOD));
}

void Rte_Write_DIOProcMod_HV_FailSafeMod_Data(DATA_IN_PROC_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_DIOProcMod_HV_FailSafeMod_Data, (uint8_t*)Data, sizeof(DATA_IN_PROC_MOD));
}

void Rte_Write_DIOProcMod_HV_SerialCommMod_Data(DATA_IN_PROC_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_DIOProcMod_HV_SerialCommMod_Data, (uint8_t*)Data, sizeof(DATA_IN_PROC_MOD));
}

void Rte_Write_SerialCommMod_LV_CanCommMod_Data(SERIAL_COMM_HV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_SerialCommMod_LV_CanCommMod_Data, (uint8_t*)Data, sizeof(SERIAL_COMM_HV_MOD));
}

void Rte_Write_SerialCommMod_HV_PTCModeMgntMod_Data(SERIAL_COMM_LV_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_SerialCommMod_HV_PTCModeMgntMod_Data, (uint8_t*)Data, sizeof(SERIAL_COMM_LV_MOD));
}

void Rte_Write_PTCModeMgntMod_SerialCommMod_HV_Data(PTC_MODE_MGNT_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_PTCModeMgntMod_SerialCommMod_HV_Data, (uint8_t*)Data, sizeof(PTC_MODE_MGNT_MOD));
}

void Rte_Write_PTCModeMgntMod_PTCPwrMgntMod_Data(PTC_MODE_MGNT_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_PTCModeMgntMod_PTCPwrMgntMod_Data, (uint8_t*)Data, sizeof(PTC_MODE_MGNT_MOD));
}

void Rte_Write_PTCPwrMgntMod_PTCModeMgntMod_Data(PTC_PWR_MGNT_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_PTCPwrMgntMod_PTCModeMgntMod_Data, (uint8_t*)Data, sizeof(PTC_PWR_MGNT_MOD));
}

void Rte_Write_FailSafeMod_SerialCommMod_Data(FAIL_SAFE_MOD *Data)
{
	(void)memcpy((uint8_t*)&Rte_FailSafeMod_SerialCommMod_Data, (uint8_t*)Data, sizeof(FAIL_SAFE_MOD));
}

void Rte_Write_DIOProcMod_CanCommMod_SctOption_Data(uint8_t Data)
{
	Rte_DIOProcMod_CanCommMod_SctOption_Data = Data;
}

void Rte_Write_DIOProcMod_PTCModMgntMod_SctOption_Data(uint8_t Data)
{
	Rte_DIOProcMod_PTCModMgntMod_SctOption_Data = Data;
}

void Rte_Write_DIOProcMod_SerialCommMod_SctOption_Data(uint8_t Data)
{
	Rte_DIOProcMod_SerialCommMod_SctOption_Data = Data;
}

void Rte_Write_DIOProcMod_PTCPwrMgntMod_SctOption_Data(uint8_t Data)
{
	Rte_DIOProcMod_PTCPwrMgntMod_SctOption_Data = Data;
}

void Rte_Write_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta(uint8_t Data)
{
	Rte_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta = Data;
}

void Rte_Write_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect(uint8_t Data)
{
	Rte_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect = Data;
}

void Rte_Write_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect(uint8_t Data)
{
	Rte_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect = Data;
}

void Rte_Write_FailSafeMod_PTCModeMgntMod_FltResults(FAIL_SAFE_RESULRT *Data)
{
	(void)memcpy((uint8_t*)&Rte_FailSafeMod_PTCModeMgntMod_FltResults, (uint8_t*)Data, sizeof(FAIL_SAFE_RESULRT));
}

/********************************************************************************************************* 
*					CS_Call(Client Server Call)
**********************************************************************************************************/

void Rte_Call_PwmTmrMM_SetdutyZoneA(float fTgtDuty)
{
	PWM_ZoneASetDuty(fTgtDuty);
}
void Rte_Call_PwmTmrMM_SetdutyZoneB(float fTgtDuty)
{
	PWM_ZoneBSetDuty(fTgtDuty);
}

uint8_t Rte_Call_PwmTmrMM_FordisChargeRun()
{
	return (uint8_t) PWM_ForDisChargeRun();
}

void Rte_Call_IoAdcM_SetHighSideIgbt()
{
	SET_GPIO_IGBT_HS_EL();
}

void Rte_Call_IoAdcM_ClearHighSideIgbt()
{
	CLEAR_GPIO_IGBT_HS_EL();
}

void Rte_Call_IoAdcM_SetExtWdgEn()
{
	SET_GPIO_EXT_WDG();
}

void Rte_Call_IoAdcM_ClearExtWdgEn()
{
	CLEAR_GPIO_EXT_WDG_EN();
}

void Rte_Call_CanMM_SetComMode(CANMM_COM_MODE mode)
{
	CanMMChangeComMode(mode);
}