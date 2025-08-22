#include "TCB.h"
#include "r_smc_interrupt.h"
#include "CanModule.h"
#include "IoAdcModule.h"
#include "App_Comm.h"
#include "App_CanCommMod.h"
#include "App_DIOProcMod.h"
#include "App_FailSafeMod.h"
#include "App_PTCModeMgntMod.h"
#include "App_PTCPwrMgntMod.h"
#include "App_SerialCommMod.h"


//#include"OsAPIs.h"

#define TASK_TIMER_PRIODIC_5MS				5U
#define TASK_TIMER_PRIODIC_15MS				10U

static uint32 Task_5msComRun = 0U;
static uint32 Task_Bsw_Fg10msRun = 0U;
static uint32 Task_Asw_Fg10msRun = 0U;

float		duty=0.0f;

void app_main(void)
{
	OS_StartOS(APP_MODE_DEFAULT);		
}

TASK(OsTask_BSW_FG1_5ms_Com)
{

	const OsEventMaskType OsWaitEventMask = (OsEventMaskType) TE_EVT_BSW_CAN_COM_5MS;
	
	(void)OS_SetRelAlarm(OsAlarm_BSW_FG1_5ms_Com, 0U, 40U);
	
	/* CAN COM Main Function Rx/Tx */
	/* UART COM Main Function Rx/Tx */
	
	for(;;)
  	{
		OsEventMaskType Events = (OsEventMaskType) 0U;
		if(E_OK == OS_WaitEvent(OsWaitEventMask))
    		{
			
			(void) OS_GetEvent((OsTaskType)OsTask_BSW_FG1_5ms_Com, &Events);

			if((Events & TE_EVT_BSW_CAN_COM_5MS) == TE_EVT_BSW_CAN_COM_5MS)
			{
				Task_5msComRun++;
				
				// CAN
				{	
					//Receive
					(void)L_ATCU_Receive(TASK_TIMER_PRIODIC_5MS);
					//Send
					(void)L_RHPTC_MessageSend(TASK_TIMER_PRIODIC_5MS);
				}
				
				// UART
				{
					(void)UartM_MainService_5ms_logic();
				}
				
				(void)OS_ClearEvent(OsWaitEventMask);
			}
		}else{
			(void)OS_TerminateTask(); /* In case of error we switch off the task */
		}
	}
}

TASK(OsTask_BSW_FG1_10ms)
{

	const OsEventMaskType OsWaitEventMask = (OsEventMaskType) TE_EVT_BSW_10MS;
	// BswM_Main
	// WdgM
	// DeviceDriver Here.. 
	// PID Logic?? (BSW or ASW?)
	(void)OS_SetRelAlarm(OsAlarm_BSW_FG1_10ms, 0U, 80U);
	for(;;)
  	{
		OsEventMaskType Events = (OsEventMaskType) 0U;
		if(E_OK == OS_WaitEvent(OsWaitEventMask))
    		{
			
			(void) OS_GetEvent((OsTaskType)OsTask_BSW_FG1_10ms, &Events);

			if((Events & TE_EVT_BSW_10MS) == TE_EVT_BSW_10MS)
			{
				Task_Bsw_Fg10msRun++;
				
				// ADC
				(void)IoAdc_MainService_10ms_logic();
				(void)OS_ClearEvent(OsWaitEventMask);
				(void)PWM_MainService_10ms_logic();
				
				
				
			}
		}else{
			(void)OS_TerminateTask(); /* In case of error we switch off the task */
		}
	}
}

TASK(OsTask_ASW_FG1_10ms)
{
	
	const OsEventMaskType OsWaitEventMask = (OsEventMaskType) TE_EVT_ASW_10MS;
	
	(void)OS_SetRelAlarm(OsAlarm_ASW_FG1_10ms, 0U, 80U);
	// TE_SWC_
	for(;;)
  	{
		OsEventMaskType Events = (OsEventMaskType) 0U;
		if(E_OK == OS_WaitEvent(OsWaitEventMask))
    		{
			
			(void) OS_GetEvent((OsTaskType)OsTask_ASW_FG1_10ms, &Events);

			if((Events & TE_EVT_ASW_10MS) == TE_EVT_ASW_10MS)
			{
				Task_Asw_Fg10msRun++;
				
				//ASW Service Run
				(void)CanCommMod_MainLogic_10ms();
				(void)DIOProcMod_MainLogic_10ms();
				(void)FailSafeMod_MainLogic_10ms();
				(void)PTCModeMgntMod_MainLogic_10ms();
				(void)PTCPwrMgntMod_MainLogic_10ms();
				(void)SerialCommMod_MainLogic_10ms();
				
				(void)OS_ClearEvent(TE_EVT_ASW_10MS);
				
			}
		}else{
			(void)OS_TerminateTask(); /* In case of error we switch off the task */
		}
	}
}