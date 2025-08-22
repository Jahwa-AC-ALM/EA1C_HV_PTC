
#ifndef Rte_H
#define Rte_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Rte_Type.h"
#include "CanModule.h"
#include "UartCtrlModule.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/* SRI_Read(Receiver) */
void Rte_Read_CanMM_CanCommMod_RxData(CAN_COMM_MOD *Data);
void Rte_Read_CanCommMod_CanMM_TxData(TxHVPP_Msg_DATA_t *Data);
void Rte_Read_IoAdcMM_DIOProcMod_RawData(DATA_IN_PROC_RAW_VALUE *Data);
void Rte_Read_IoAdcMM_DIOProcMod_SctOption_Data(uint8_t *Data);
void Rte_Read_IoAdcMM_CanMM_SctOption_Data(uint8_t *Data);
void Rte_Read_UartM_SerialCommMod_LV_RxData(SERIAL_COMM_HV_MOD *Data);
void Rte_Read_UartM_SerialCommMod_HV_RxData(SERIAL_COMM_LV_MOD *Data);
void Rte_Read_SerialCommMod_UartM_HV_TxData(SERIAL_COMM_HV_MOD *Data);
void Rte_Read_SerialCommMod_UartM_LV_TxData(SERIAL_COMM_LV_MOD *Data);

void Rte_Read_CanCommMod_SerialCommMod_Data(CAN_COMM_MOD *Data);
void Rte_Read_DIOProcMod_HV_FailSafeMod_Data(DATA_IN_PROC_MOD *Data);
void Rte_Read_DIOProcMod_HV_SerialCommMod_Data(DATA_IN_PROC_MOD *Data);
void Rte_Read_SerialCommMod_LV_CanCommMod_Data(SERIAL_COMM_HV_MOD *Data);
void Rte_Read_SerialCommMod_HV_PTCModeMgntMod_Data(SERIAL_COMM_LV_MOD *Data);
void Rte_Read_PTCModeMgntMod_SerialCommMod_HV_Data(PTC_MODE_MGNT_MOD *Data);
void Rte_Read_PTCModeMgntMod_PTCPwrMgntMod_Data(PTC_MODE_MGNT_MOD *Data);
void Rte_Read_PTCPwrMgntMod_PTCModeMgntMod_Data(PTC_PWR_MGNT_MOD *Data);
void Rte_Read_FailSafeMod_SerialCommMod_Data(FAIL_SAFE_MOD *Data);
void Rte_Read_DIOProcMod_CanCommMod_SctOption_Data(uint8_t *Data);
void Rte_Read_DIOProcMod_PTCModMgntMod_SctOption_Data(uint8_t *Data);
void Rte_Read_DIOProcMod_SerialCommMod_SctOption_Data(uint8_t *Data);
void Rte_Read_DIOProcMod_PTCPwrMgntMod_SctOption_Data(uint8_t *Data);
void Rte_Read_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta(uint8_t *Data);
void Rte_Read_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect(uint8_t *Data);
void Rte_Read_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect(uint8_t *Data);
void Rte_Read_FailSafeMod_PTCModeMgntMod_FltResults(FAIL_SAFE_RESULRT *Data);

/* SRI_Write(Sender) */
void Rte_Write_CanMM_CanCommMod_RxData(CAN_COMM_MOD *Data);
void Rte_Write_CanCommMod_CanMM_TxData(TxHVPPSta_t *Data);
void Rte_Write_IoAdcMM_DIOProcMod_RawData(DATA_IN_PROC_RAW_VALUE *Data);
void Rte_Write_IoAdcMM_DIOProcMod_SctOption_Data(uint8_t Data);
void Rte_Write_IoAdcMM_CanMM_SctOption_Data(uint8_t Data);
void Rte_Write_UartM_SerialCommMod_LV_RxData(SERIAL_COMM_HV_MOD *Data);
void Rte_Write_UartM_SerialCommMod_HV_RxData(SERIAL_COMM_LV_MOD *Data);
void Rte_Write_SerialCommMod_UartM_HV_TxData(SERIAL_COMM_HV_MOD *Data);
void Rte_Write_SerialCommMod_UartM_LV_TxData(SERIAL_COMM_LV_MOD *Data);

void Rte_Write_CanCommMod_SerialCommMod_Data(CAN_COMM_MOD *Data);
void Rte_Write_DIOProcMod_HV_FailSafeMod_Data(DATA_IN_PROC_MOD *Data);
void Rte_Write_DIOProcMod_HV_SerialCommMod_Data(DATA_IN_PROC_MOD *Data);
void Rte_Write_SerialCommMod_LV_CanCommMod_Data(SERIAL_COMM_HV_MOD *Data);
void Rte_Write_SerialCommMod_HV_PTCModeMgntMod_Data(SERIAL_COMM_LV_MOD *Data);
void Rte_Write_PTCModeMgntMod_SerialCommMod_HV_Data(PTC_MODE_MGNT_MOD *Data);
void Rte_Write_PTCModeMgntMod_PTCPwrMgntMod_Data(PTC_MODE_MGNT_MOD *Data);
void Rte_Write_PTCPwrMgntMod_PTCModeMgntMod_Data(PTC_PWR_MGNT_MOD *Data);
void Rte_Write_FailSafeMod_SerialCommMod_Data(FAIL_SAFE_MOD *Data);
void Rte_Write_DIOProcMod_CanCommMod_SctOption_Data(uint8_t Data);
void Rte_Write_DIOProcMod_PTCModMgntMod_SctOption_Data(uint8_t Data);
void Rte_Write_DIOProcMod_SerialCommMod_SctOption_Data(uint8_t Data);
void Rte_Write_DIOProcMod_PTCPwrMgntMod_SctOption_Data(uint8_t Data);
void Rte_Write_SerialCommMod_HV_FailSafeMod_CanRxTimeoutSta(uint8_t Data);
void Rte_Write_PTCPwrMgntMod_FailSafeMod_IGBTShortDetect(uint8_t Data);
void Rte_Write_PTCPwrMgntMod_FailSafeMod_CoreOpenDetect(uint8_t Data);
void Rte_Write_FailSafeMod_PTCModeMgntMod_FltResults(FAIL_SAFE_RESULRT *Data);

//CS_Call(Client Server Call)
void Rte_Call_PwmTmrMM_SetdutyZoneA(float fTgtDuty);
void Rte_Call_PwmTmrMM_SetdutyZoneB(float fTgtDuty);
uint8_t Rte_Call_PwmTmrMM_FordisChargeRun();

void Rte_Call_IoAdcM_SetHighSideIgbt();
void Rte_Call_IoAdcM_ClearHighSideIgbt();
void Rte_Call_IoAdcM_SetExtWdgEn();
void Rte_Call_IoAdcM_ClearExtWdgEn();


void Rte_Call_CanMM_SetComMode(CANMM_COM_MODE mode);
void Rte_Call_UartM_SetComMode(UART_COM_MODE mode);

#endif