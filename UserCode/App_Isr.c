//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
//#include"OsAPIs.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "TCB.h"

#include "CanModule.h"
#include "IoAdcModule.h"
//#include "Config_PWMTMR.h"
#include "PWMTmrModule.h"
#include "UartCtrlModule.h"



uint32	g_canrxFlag=0;
uint16_t getadc[20];

ISR(RCANGRECC0)
{
	(void)CanMMReceiveIsr();
}

ISR(RCAN0ERR)
{
	if((RCFDC0.CFDC0STS.UINT32 & 0x00000010U) > 0U)
	{
		//g_busoffFlag = 1;
	}
	RCFDC0.CFDGERFL.UINT32 &= 0xFFFF8000U;
	//__asm("nop");
}

ISR(ADCA0GRPSCAN)
{
	/* Scan Timer 30us Called */
	(void)IoAdc_Get_ADCA0_ScanGroupIsr();
}


//ISR(PWMGATECTRL)
//{
//	/* 100us Timer Call */
//	(void)PWM_GateCtrlServiceIsr();
//}

ISR(INTC0)
{
	//External IO Interrupt ISR
	// CS Fault
}

ISR(INTC1)
{
	//External IO Interrupt ISR
	// 15VD Fault
}

ISR(UART0SEND)
{
	(void)UartM_TxServiceIsr();
}

ISR(UART0RECV)
{
	(void)UartM_RxServiceIsr();
}

ISR(UART0ERR)
{
	
}