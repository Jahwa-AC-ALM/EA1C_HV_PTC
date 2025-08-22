/*******************************************************************************
**                         MULTIPLE INCLUSION PROTECTION                      **
*******************************************************************************/
#ifndef RTE_TYPE_H
#define RTE_TYPE_H

/*******************************************************************************
**                  Include Section                                           **
*******************************************************************************/
#include "OsTypes.h"

/*******************************************************************************
* MACROS USED FOR Data Conversion for Application Datatypes                   **
*******************************************************************************/
#define 	NULL_PTR					((void *)0)
#define 	GPIO_LOW					0U
#define		GPIO_HIGH					1U

#define 	MODE_SCTOPTION_DEFAULT				0U
#define 	MODE_SCTOPTION_LV				1U
#define 	MODE_SCTOPTION_HV				2U
/*******************************************************************************
* MACROS USED FOR Range Datatypes                                             **
*******************************************************************************/

/*******************************************************************************
* MACROS USED FOR Invalid Value Datatypes                                     **
*******************************************************************************/

/*******************************************************************************
** Type Definitions for  data types                                           **
*******************************************************************************/
typedef struct {
	//L_ATCU_12 or L_ATCU_13
	uint8_t 			OpPrmssnSta;
	uint8_t 			DrvrSdTyp;
	uint8_t 			DrTrgtDty;
	uint8_t 			PsTrgtDty;
	uint8_t 			DischrgReq;
	uint8_t 			FltMsgTmOutFHPTC1;
	uint8_t 			FltMsgTmOutFHPTC2;
	uint8_t 			FltMsgTmOutFHPTC3;
	uint8_t 			FltMsgTmOutFHPTC4;
	uint8_t 			BlwLvl;
	uint8_t 			BlwLvlSigVaildSta;
	uint8_t 			BlwFltSta;
	uint8_t 			PassBlwLvl;
} CAN_COMM_PROC_RXDATA;

typedef struct {
	//L_FHPTC_01
	uint8_t				DrRdySta;
	uint8_t				DrOpSta;
	uint8_t 			DrCoreTemp_C;
	uint16_t 			DrCnsmptPwr_W;
	uint8_t				DrCurrent_A;
	uint8_t				DrDutyFB_Pec;
	uint8_t				DrDutyFB_IGBT;
	uint8_t				DrCtrlTyp;
	uint8_t				DrVoltage_V;
	//L_FHPTC_02
	uint8_t				DrFlt;
	uint8_t				DrFltLVLow;
	uint8_t				DrFltLVHigh;
	uint8_t				DrFltHVLow;
	uint8_t				DrFltHVHigh;
	uint8_t				DrFltOverCurrent;
	uint8_t				DrFltThermalShutDn;
	uint8_t				DrFltPcbThermalShutDn;
	uint8_t				DrFltMsgTmOutATCU;
	uint8_t				DrFailHVSnr;
	uint8_t				DrFailLVSnr;
	uint8_t 			DrFailCurrentSnr;
	uint8_t				DrFailCoreTempSnr;
	uint8_t				DrFailPcbTempSnr;
	uint8_t				DrFailIGBT;
	uint8_t				DrFailOpenLoad;
	uint8_t				DrLtdOpCause;
	uint8_t				DrSwVer;
	uint16_t			CnsmptPwrTtl_W;
	uint8_t				IntlkSta;
	//L_FHPTC_03
	uint8_t				PassRdySta;
	uint8_t				PassOpSta;
	uint8_t				PassCtrlTyp;
	uint8_t				PassCoreTemp_C;
	uint16_t			PassCnsmptPwr_W;
	uint8_t				PassVoltage_V;
	uint8_t				PassCurrent_A;
	uint8_t				PassDutyFB_Pec;
	uint8_t				PassDutyFB_IGBT;
	//L_FHPTC_04
	uint8_t				PassFlt;
	uint8_t				PassFltLVLow;
	uint8_t				PassFltLVHigh;
	uint8_t				PassFltHVLow;
	uint8_t				PassFltHVHigh;
	uint8_t				PassFltOverCurrent;
	uint8_t				PassFltThermalShutDn;
	uint8_t				PassFltPcbThermalShutDn;
	uint8_t				PassFltMsgTmOutATCU;
	uint8_t				PassFailHVSnr;
	uint8_t				PassFailLVSnr;
	uint8_t 			PassFailCurrentSnr;
	uint8_t				PassFailCoreTempSnr;
	uint8_t				PassFailPcbTempSnr;
	uint8_t				PassFailIGBT;
	uint8_t				PassFailOpenLoad;
	uint8_t				PassLtdOpCause;
	uint8_t				PassSwVer;
}CAN_COMM_PROC_TXDATA;


typedef struct{
	CAN_COMM_PROC_RXDATA		st_CanCommModRxData;
	uint8_t				RxDataTimeoutSta;
}CAN_COMM_MOD;


typedef struct{
	float				LDO_15Vol_Mon_V;
	float				HighVol_Mon_V;
	float				LowVol_Mon_V;
	float				PcbNTCTemp_C;
	float				IgbtNTCTemp_Dr_C;
	float				IgbtNTCTemp_Pass_C;
	float				DrCurr_A;
	float				PassCurr_A;
	float				DrHVDVol_IO;
	float				PassHVDVol_IO;
	float				CoreNTCTemp_Dr_C;
	float				CoreNTCTemp_Pass_C;
}DATA_IN_PROC_SENS;

typedef struct{
	//ADC
	uint16_t			LDO_15Vol_Mon_Ad;
	uint16_t			HighVol_Ad;
	uint16_t			LowVol_Ad;
	uint16_t			PcbNTCTemp_Ad;
	uint16_t			IgbtNTCTemp_Dr_Ad;
	uint16_t			IgbtNTCTemp_Pass_Ad;
	uint16_t			DrCurr_Ad;
	uint16_t			PassCurr_Ad;
	uint16_t			DrHVDVol_Ad;
	uint16_t			PassHVDVol_Ad;
	uint16_t			CoreNTCTemp_Dr_Ad;
	uint16_t			CoreNTCTemp_Pass_Ad;
	//

}DATA_IN_PROC_RAW_VALUE;

typedef struct {
	DATA_IN_PROC_SENS		st_DIOProcModSens;
	uint8_t				LvHvSctOption;
	uint8_t				IntlkSta;
	uint8_t				INTP0Fault;	
	uint8_t				INTP1Fault;
}DATA_IN_PROC_MOD;

typedef struct {
	uint8_t				FltLvLow;
	uint8_t				FltLvHigh;
	uint8_t				FltHvLow;
	uint8_t				FltHvHigh;
	uint8_t				FltOverCurrent;
	uint8_t				FltThermalShutDn;
	uint8_t				FltPcbTermalShutDn;
	uint8_t				FailHvSnr;
	uint8_t				FailLvSnr;
	uint8_t				FailCurrentSnr;
	uint8_t				FailCoreTempSnr;
	uint8_t				FailPcbTempSnr;
	uint8_t				FailIGBT;
	uint8_t				FailOpenLoad;
	uint8_t				FltMsgTmoutATCU;
}FAIL_SAFE_RESULRT_DETAIL;

typedef struct{
	uint8_t 			DrFlt;
	uint8_t				PassFlt;
}FAIL_SAFE_RESULRT;

typedef struct {
	FAIL_SAFE_RESULRT_DETAIL	st_Dr_FailSafeResults;
	FAIL_SAFE_RESULRT_DETAIL	st_Ps_FailSafeResults;
	FAIL_SAFE_RESULRT		st_FltSta;
	
}FAIL_SAFE_MOD;

typedef struct
{
	uint8_t				IgbtShortDetectOccured;
	uint8_t				CoreOpenDetectOccured;
}PTC_PWR_MGNT_FAIL_DETECT;

typedef struct
{
	//PTC_PWR_MGNT_FAIL_DETECT	st_FailDetectLogicResults;
	uint8_t				DrLtdOpControlSta;
	uint8_t				PassLtdOpControlSta;
	float				DrCurrentDutyFB;
	float				PassCurrentDutyFB;
	float				DisChrgRunSta;
}PTC_PWR_MGNT_MOD;

typedef struct
{
	uint8_t				DrRdySta;
	uint8_t				PassRdySta;
	uint8_t            	 	DrOpSta; 	// 2025.08.19 Added
	uint8_t             		PassOpSta; 	// 2025.08.19 Added
	uint8_t				DrLtdOpCause;
	uint8_t				PassLtdOpCause;
	float				DrTrgtWatt;
	float				PassTrgtWatt;
	uint8_t				DischrgCmd;
	float				DrDutyFB_IGBT;
	float				PassDutyFB_IGBT;
	float				DrDutyFB_Per;
	float				PassDutyFB_Per;
	
}PTC_MODE_MGNT_MOD;

typedef struct 
{
	uint8_t 			OpPrmssnSta;
	uint8_t 			DrvrSdTyp;
	uint8_t 			DrTrgtDty;
	uint8_t 			PsTrgtDty;
	uint8_t 			DischrgReq;
	uint8_t				RxDataTimeoutSta;
	uint16_t			LowVol_Ad;
	uint8_t				IntlkSta;
}SERIAL_COMM_LV_MOD;

typedef struct 
{
	FAIL_SAFE_MOD			st_PtcFaultSta;
	PTC_MODE_MGNT_MOD		st_PtcModMgnSta;
}SERIAL_COMM_HV_MOD;


#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/