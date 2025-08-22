
#ifndef CanModule_H
#define CanModule_H

#include "r_device.h"
#include "r_typedefs.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

#define L_RHPTC_01_ID		0x150U			//HVPP1Sta Tx ID
#define L_RHPTC_02_ID		0x151U			//HVPP2flt Tx ID
#define L_RHPTC_03_ID		0x152U			//HVPP3Sta Tx ID
#define L_RHPTC_04_ID		0x153U			//HVPP3flt Tx ID

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
	CANMM_TX_OFF_RX_OFF = 0,
	CANMM_TX_ON_RX_OFF,
	CANMM_TX_OFF_RX_ON,
	CANMM_TX_ON_RX_ON
}CANMM_COM_MODE;

/* RX Message Bit Struct */
typedef struct 
{
    struct 
    {    
        uint64_t PTCOpPermission:1;
        uint64_t rsvd0:3;
        uint64_t PTCZone1TgtDty:8; 
        uint64_t PTCZone2TgtDty:8; 
        uint64_t PTCDischrgReq:1;
        uint64_t FltMsgTimeOutFHPTC1:1;
        uint64_t FltMsgTimeOutFHPTC2:1;
        uint64_t FltMsgTimeOutFHPTC3:1;
        uint64_t FltMsgTimeOutFHPTC4:1;
	
        uint64_t FrBlowLevel:4;
        uint64_t FrBlowLevelSigValid:8;
        uint64_t rsvd1:8;
        uint64_t FrBlowFlt:1;      
        uint64_t rsvd2:2;
        uint64_t rsvd3:8; 
        uint64_t rsvd4:8; 
    }st;
}CCUFrame_t;

/* Tx Message Bit Struct */
typedef struct 
{
    struct 
    {
        uint64_t Ready:1;
        uint64_t OpState:2;
		uint64_t rsvd:1;
		uint64_t CtrlType:4;
        uint64_t CoreTemp:8;
        uint64_t Consumption:16;
		uint64_t Voltage:8;
        uint64_t CurrentA:8;
        uint64_t DutyFB:8;
        uint64_t DutyFB_IGBT:8;        
    }st_dr;
}HVPP1Frame_t;

typedef struct 
{
    struct
    {
        uint8_t Flt:1;
        uint8_t FltLV_Low:1;
        uint8_t FltLV_High:1;
        uint8_t FltHV_Low:1;
        uint8_t FltHV_High:1;
        uint8_t FltOverCurrent:1;
        uint8_t FltThermalShutdown:1;
        uint8_t FltPCBTheramalShutdown:1;
        uint8_t FltMsgTimeOutATCU:1;
        uint8_t FailHVSensor:1;
        uint8_t FailLVSensor:1;
        uint8_t FailCurrentSensor:1;
        uint8_t FailCoreTempSensor:1;
        uint8_t FailPCBTempSensor:1;
        uint8_t FailIGBT:1;
        uint8_t FailOpenLoad:1;
        uint8_t LtdOpCause;
        uint8_t SWVer;
        uint16_t TotalConsumtionPWR;
        uint16_t Interlock:2;
        uint16_t rsvd:14;
    }st_dr;
}HVPP2Frame_t;

typedef struct 
{
    struct
    {
        uint64_t Ready:1;
        uint64_t OpState:2;
        uint64_t CtrlType:4;
        uint64_t CoreTemp:8;
        uint64_t Consumption:16;
        uint64_t Voltage:8;
        uint64_t CurrentA:8;
        uint64_t DutyFB:8;
        uint64_t DutyFB_IGBT:8;
        uint64_t rsvd:1;
    }st_ps;
}HVPP3Frame_t;

typedef struct 
{
    struct
    {
        uint8_t Flt:1;
        uint8_t FltLV_Low:1;
        uint8_t FltLV_High:1;
        uint8_t FltHV_Low:1;
        uint8_t FltHV_High:1;
        uint8_t FltOverCurrent:1;
        uint8_t FltThermalShutdown:1;
        uint8_t FltPCBTheramalShutdown:1;

        uint8_t FltMsgTimeOutATCU:1;
        uint8_t FailHVSensor:1;
        uint8_t FailLVSensor:1;
        uint8_t FailCurrentSensor:1;
        uint8_t FailCoreTempSensor:1;
        uint8_t FailPCBTempSensor:1;
        uint8_t FailIGBT:1;
        uint8_t FailOpenLoad:1;

        uint8_t LtdOpCause;

        uint8_t SWVer;
        
        uint16_t rsvd0;
        uint16_t rsvd1;
    }st_ps;    
}HVPP4Frame_t;

/* RX Message Ctrl Struct */
typedef struct
{
	CCUFrame_t 	Frame;
	uint8_t		ReceivedFlag;
	uint8_t		TimeoutFlag;
	uint16_t 	TimeoutCnt;
	uint16_t	TimeoutThreshold;
}RxCCUSta_t;

/* TX Message Ctrl Struct */

typedef struct {
	HVPP1Frame_t 		st_CanHVPP1StaTxData;
	HVPP2Frame_t		st_CanHVPP2FltTxData;
	HVPP3Frame_t 		st_CanHVPP3StaTxData;
	HVPP4Frame_t		st_CanHVPP4FltTxData;
}TxHVPP_Msg_DATA_t;

typedef struct
{
	TxHVPP_Msg_DATA_t	stHVPPMsgData;
	uint8_t 		HVPP1StaInterval;
	uint8_t 		HVPP1StaCnt;
	uint8_t 		HVPP2StaInterval;
	uint8_t 		HVPP2StaCnt;
	uint8_t 		HVPP3StaInterval;
	uint8_t 		HVPP3StaCnt;
	uint8_t 		HVPP4StaInterval;
	uint8_t 		HVPP4StaCnt;
}TxHVPPSta_t;


//extern RxCCUSta_t	st_CanRxCCUSta;

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
void CanMMReceiveIsr(void);
void CanMMChangeComMode(CANMM_COM_MODE mode);

void L_ATCU_Receive(uint8_t interval);
void L_RHPTC_MessageSend(uint8_t interval);



#endif