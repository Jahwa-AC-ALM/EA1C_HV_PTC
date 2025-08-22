//------------------------------------------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------------------------------------------
//#include"OsAPIs.h"
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_OSTM0.h"
#include "TCB.h"
#include "r_smc_interrupt.h"

//#define OsGetPSW __OsGetPSW

#define EXCEPTION_CODE_MASK  (uint32_t)(1<<5)		//ID

//#include"SysTickTimer.h"

//------------------------------------------------------------------------------------------------------------------
// Static function prototypes
//------------------------------------------------------------------------------------------------------------------
static void OS_InitTimer(void);
static void OS_StartTimer(void);
static void OS_IdleLoop(void);
static void OsCreateNewContext(uint32 StackFramePtr, pFunc TaskFuncPtr, void * pvParameters);






//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_StartOS
///
/// \descr  The user can call this system service to start the operating system in a specific mode
///
/// \param  OsAppModeType Mode
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_StartOS(OsAppModeType Mode)
{
	static int tcbIdx = 0;
	static uint32 Idx=0u;
	
	(void) Mode;

	if(TRUE == OsIsInterruptContext())
	{
		return;
	}
	
	/* Save the system stack ptr */
	OsGetCurrentSP(&OCB_Cfg.OsSystemStackPtr);
	pxCurrentStackPoint = &OCB_Cfg.OsSystemStackPtr;
	
	
	
	if(NB_OF_TASKS > 0)
	{
		/* INIT TCBs */
		for(tcbIdx = 0; tcbIdx < NB_OF_TASKS; tcbIdx++)
		{
			/* Init all stacks with marker 0xAA */
			const uint32 stack_size = OCB_Cfg.pTcb[tcbIdx]->pstack_top - OCB_Cfg.pTcb[tcbIdx]->pstack_bot + sizeof(uint32);
			for(Idx=0u;Idx < stack_size;Idx+=sizeof(uint32))
			{
				*(uint32*)((OCB_Cfg.pTcb[tcbIdx]->pstack_bot) + Idx) = (uint32)0xAAAAAAAAu;
			}

			/* Set default tasks priorities */
			OCB_Cfg.pTcb[tcbIdx]->Prio = OCB_Cfg.pTcb[tcbIdx]->FixedPrio;
		}
		
		//pxCurrentTcbStackPoint = ((*OCB_Cfg.pTcb[NB_OF_TASKS-1]).pCurrentStackPointer);
		
		
		
		
		
		
		/* Init system tick timer */
		OS_InitTimer();
		
		/* Start all autostart task */
		for(tcbIdx = 0; tcbIdx < NB_OF_TASKS; tcbIdx++)
		{
			if(OCB_Cfg.pTcb[tcbIdx]->Autostart == OS_AUTOSTART && OCB_Cfg.pTcb[tcbIdx]->TaskStatus == SUSPENDED)
			{
				/* Switch to PRE_READY state*/
				OCB_Cfg.pTcb[tcbIdx]->TaskStatus = PRE_READY;

				/* Update number of activation */
				OCB_Cfg.pTcb[tcbIdx]->NbOfActiv--;
			}
		}
		
		/* Call startup hook function */
		#if(STARTUPHOOK)
		StartupHook();
		#endif
		
		//OCB_Cfg.CurrentTaskIdx = NB_OF_TASKS;
		
		/* Start system tick timer */
		OS_StartTimer();
		
		/* Lock the dispatcher */
		OCB_Cfg.OsLockDispatcher = 1;
		
		/* Call Scheduler */
		(void)OS_Schedule();

		/* Unlock the dispatcher */
		OCB_Cfg.OsLockDispatcher = 0;
		

		
		/* Call the dispatcher */
		OS_DISPATCH();
	}
	
	/* Infinite loop */
	for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_Schedule
///
/// \descr  If a higher-priority task is ready, the internal resource of the task is released, 
///         the current task is put into the ready state, its context is saved and the higher-priority task
///         is executed. Otherwise the calling task is continued.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
OsStatusType OS_Schedule(void)
{
	static int tcbIdx = 0;
	
	if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS && 
		OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->CeilingPrio != 0 &&
		OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio != OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->FixedPrio &&
		FALSE == OsIsCat2IntContext())
	{
		return(E_OS_RESOURCE);
	}
	else if(TRUE == OsIsInterruptContext() && FALSE == OsIsCat2IntContext()) /* Cat1 Interrupt */
	{
		return(E_OS_CALLEVEL);
	}
	else
	{
		sint32 HighPrio = -1;
		OCB_Cfg.HighPrioReadyTaskIdx = INVALID_TASK;
		
		/* Starting a critical section */
		__DI();
		
		for(tcbIdx = 0; tcbIdx < NB_OF_TASKS; tcbIdx++)
		{
			if(OCB_Cfg.pTcb[tcbIdx]->TaskStatus == PRE_READY || 
				OCB_Cfg.pTcb[tcbIdx]->TaskStatus == READY     || 
				OCB_Cfg.pTcb[tcbIdx]->TaskStatus == RUNNING)
			{
				if((sint32)OCB_Cfg.pTcb[tcbIdx]->Prio > HighPrio)
				{
					HighPrio = (sint32) OCB_Cfg.pTcb[tcbIdx]->Prio;
					OCB_Cfg.HighPrioReadyTaskIdx = (uint32) tcbIdx;
				}
			}
		}
		
		/* Ending the critical section */
		__EI();
		
		if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS && OCB_Cfg.HighPrioReadyTaskIdx < NB_OF_TASKS)
		{
			if(	HighPrio > (sint32)(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->Prio)		||
				(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == WAITING            ||
				OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == SUSPENDED))
			{
				/* Call PostTaskHook */
				#if(POSTTASKHOOK)
				PostTaskHook();
				#endif

				if(OCB_Cfg.OsIsrInterruptLevel == 0 && OCB_Cfg.OsLockDispatcher == 0)
				{
					/* Call the dispatcher */
					OS_DISPATCH();
				}
				else if(OCB_Cfg.OsLockDispatcher == 1)
				{
					return(E_OK);
				}
				else
				{
					/*  OS_Schedule is called in interrupt context  */
					/*  the Dispatcher will be executed later after */
					/*  the execution of the ISR                    */

					OCB_Cfg.OsIsrCallDispatcher = 1;
				}
			}else{
				/* No task is active or ready */
				/* Kernel will switch to system stack and run OS_IdleLoop */

				/* Call PostTaskHook */
				if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
				{
					#if(POSTTASKHOOK)
					PostTaskHook();
					#endif
				}

				if(OCB_Cfg.OsIsrInterruptLevel == 0)
				{
					/* OS_Schedule is called outside an interrupt context */
					/* Call the dispatcher */
					OS_DISPATCH();
				}
				else
				{
					/*  OS_Schedule is called in interrupt context  */
					/*  the Dispatcher will be executed later after */
					/*  the execution of the ISR                    */
					OCB_Cfg.OsIsrCallDispatcher = 1;

				}
			}
		
		}
		return(E_OK);
	}
}


//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_Dispatcher
///
/// \descr  Context switch engine
///
/// \param  uint32 StackPtr: Current stack pointer of the active task
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
uint32 OS_Dispatcher(uint32 StackPtr)
{
	uint32 NewStackFramePtr;
	pFunc   NewThread;
	
	/**/
	pxCurrentStackPoint_top = &StackPtr;
	
	/* Save the current stack pointer of the running task before switching the context */
	if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
	{
		OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = StackPtr;
		//pxCurrentTcbStackPoint = &OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer;
	}
	


	/* Set the new current task */
	OCB_Cfg.CurrentTaskIdx = OCB_Cfg.HighPrioReadyTaskIdx;

	if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
	{
		/* check if we need to create a new stack frame for the new task */
		if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == PRE_READY)
		{
			/* cupdate the current task state */
			OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = RUNNING;

			/* Call PreTaskHook */
			#if(PRETASKHOOK)
			PreTaskHook();
			#endif

			/* Create Stack Frame for the 1st execution */
			NewStackFramePtr = OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_top;
			NewThread = OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->function;

			/* CREATE NEW CONTEXT */
			OsCreateNewContext(NewStackFramePtr, NewThread, 0);

			/* Calculate the new stack ptr */
			NewStackFramePtr = (uint32)((uint32)(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pstack_top) - (uint32)0x84);  

			/* Save the new stack ptr */    
			OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = NewStackFramePtr;
			//pxCurrentStackPoint = &(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
		}
		else if(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == READY)
		{
			OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus = RUNNING;

			/* Call PreTaskHook */
			#if(PRETASKHOOK)
			PreTaskHook();
			#endif
		}
	}
	else
	{
		/* Create new context for os Idle loop and switch to it using the system stack */
		OsCreateNewContext((uint32)OCB_Cfg.OsSystemStackPtr, OS_IdleLoop, 0);

		return(OCB_Cfg.OsSystemStackPtr - 0x84);
	}

	return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsCreateNewContext
///
/// \descr  This function create and fill the new task context
///
/// \param  uint32 StackFramePtr: Current stack pointer of the active task
///            pFunc TaskFuncPtr: task function pointer
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void OsCreateNewContext(uint32 StackFramePtr, pFunc TaskFuncPtr, void * pvParameters)
{
	*(volatile uint32*)(StackFramePtr - 0x00) = (uint32)TaskFuncPtr;   		 // LP
	*(volatile uint32*)(StackFramePtr - 0x04) = (uint32)TaskFuncPtr;  		 // EIPC
	*(volatile uint32*)(StackFramePtr - 0x08) = ( StackType_t )0x00018001;		 /* Initial PSW value */
	*(volatile uint32*)(StackFramePtr - 0x0C) = ( StackType_t )0x00000000;		 /* Initial 0 value */
	*(volatile uint32*)(StackFramePtr - 0x10) = ( StackType_t )0x20202020;          /* Initial Value of R20 */
	*(volatile uint32*)(StackFramePtr - 0x14) = ( StackType_t )0x30303030;           /* Initial Value of R30 */
	*(volatile uint32*)(StackFramePtr - 0x18) = ( StackType_t )0x29292929;           /* Initial Value of R29 */
	*(volatile uint32*)(StackFramePtr - 0x1C) = ( StackType_t )0x28282828;           /* Initial Value of R28 */
	*(volatile uint32*)(StackFramePtr - 0x20) = ( StackType_t )0x27272727;           /* Initial Value of R27 */
	*(volatile uint32*)(StackFramePtr - 0x24) = ( StackType_t )0x26262626;           /* Initial Value of R26 */
	*(volatile uint32*)(StackFramePtr - 0x28) = ( StackType_t )0x25252525;           /* Initial Value of R25 */
	*(volatile uint32*)(StackFramePtr - 0x2C) = ( StackType_t )0x24242424;           /* Initial Value of R24 */
	*(volatile uint32*)(StackFramePtr - 0x30) = ( StackType_t )0x23232323;           /* Initial Value of R23 */
	*(volatile uint32*)(StackFramePtr - 0x34) = ( StackType_t )0x22222222;           /* Initial Value of R22 */
	*(volatile uint32*)(StackFramePtr - 0x38) = ( StackType_t )0x21212121;           /* Initial Value of R21 */
	*(volatile uint32*)(StackFramePtr - 0x3C) = ( StackType_t )0x19191919;           /* Initial Value of R19 */
	*(volatile uint32*)(StackFramePtr - 0x40) = ( StackType_t )0x18181818;           /* Initial Value of R18 */  
	*(volatile uint32*)(StackFramePtr - 0x44) = ( StackType_t )0x17171717;           /* Initial Value of R17 */
	*(volatile uint32*)(StackFramePtr - 0x48) = ( StackType_t )0x16161616;           /* Initial Value of R16 */
	*(volatile uint32*)(StackFramePtr - 0x4C) = ( StackType_t )0x15151515;           /* Initial Value of R15 */
	*(volatile uint32*)(StackFramePtr - 0x50) = ( StackType_t )0x14141414;           /* Initial Value of R14 */
	*(volatile uint32*)(StackFramePtr - 0x54) = ( StackType_t )0x13131313;           /* Initial Value of R13 */
	*(volatile uint32*)(StackFramePtr - 0x58) = ( StackType_t )0x12121212;           /* Initial Value of R12 */
	*(volatile uint32*)(StackFramePtr - 0x5C) = ( StackType_t )0x11111111;           /* Initial Value of R11 */
	*(volatile uint32*)(StackFramePtr - 0x60) = ( StackType_t )0x10101010;           /* Initial Value of R10 */
	*(volatile uint32*)(StackFramePtr - 0x64) = ( StackType_t )0x99999999;           /* Initial Value of R09 */
	*(volatile uint32*)(StackFramePtr - 0x68) = ( StackType_t )0x88888888;           /* Initial Value of R08 */
	*(volatile uint32*)(StackFramePtr - 0x6C) = ( StackType_t )0x77777777;           /* Initial Value of R07 */
	*(volatile uint32*)(StackFramePtr - 0x70) = ( StackType_t )pvParameters;           /* R6 is expected to hold the function parameter*/
	*(volatile uint32*)(StackFramePtr - 0x74) = ( StackType_t )0x55555555;           /* Initial Value of R02 */
	*(volatile uint32*)(StackFramePtr - 0x78) = ( StackType_t )0x44444444;          /* Initial Value of R01 */
	*(volatile uint32*)(StackFramePtr - 0x7C) = ( StackType_t )0x22222222;           /* Initial Value of R02 */
	*(volatile uint32*)(StackFramePtr - 0x80) = ( StackType_t )0x11111111;          /* Initial Value of R01 */
	*(volatile uint32*)(StackFramePtr - 0x84) = ( StackType_t )usCriticalNesting;
	     
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  Interrupt service routine
///
/// \descr  ISR of system tick interrupt
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
ISR(SysTickTimer)  
{
	static int AlarmID = 0;
	
	//OsSysTickCount ¡ı∞°
	OCB_Cfg.OsSysTickCounter++;
	
	//Alarm Check
	for(AlarmID =0; AlarmID < NB_OF_ALARMS; AlarmID++)
  	{
		if(OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint <= (uint32)OCB_Cfg.OsSysTickCounter)
		{
			/* Update Timers */
			if(OCB_Cfg.pAlarm[AlarmID]->AlarmCategory == ALARM_RELATIVE &&  OCB_Cfg.pAlarm[AlarmID]->Alarmtype == ALARM_ONE_SHOT)
			{
				OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint = 0;
			}
			else if(OCB_Cfg.pAlarm[AlarmID]->AlarmCategory == ALARM_RELATIVE &&  OCB_Cfg.pAlarm[AlarmID]->Alarmtype == ALARM_CYCLIC)
			{
				OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint = OCB_Cfg.pAlarm[AlarmID]->InitTicks + OCB_Cfg.pAlarm[AlarmID]->InitCycles + (uint32)OCB_Cfg.OsSysTickCounter;
			}
			else if(OCB_Cfg.pAlarm[AlarmID]->AlarmCategory == ALARM_ABSOLUTE &&  OCB_Cfg.pAlarm[AlarmID]->Alarmtype == ALARM_ONE_SHOT)
			{
				OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint = 0;
			}
			else if(OCB_Cfg.pAlarm[AlarmID]->AlarmCategory == ALARM_ABSOLUTE &&  OCB_Cfg.pAlarm[AlarmID]->Alarmtype == ALARM_CYCLIC)
			{
				OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint = OCB_Cfg.pAlarm[AlarmID]->InitCycles;
			}
			else
			{
				/* Do Nothing */
			}
		      
			/* Execute Action */
			if(OCB_Cfg.pAlarm[AlarmID]->Action == ALARM_SET_EVENT)
			{
				OS_SetEvent((OsTaskType)OCB_Cfg.pAlarm[AlarmID]->TaskId, (OsEventMaskType)OCB_Cfg.pAlarm[AlarmID]->Event);
			}
			else if(OCB_Cfg.pAlarm[AlarmID]->Action == ALARM_ACTIVE_TASK)
			{
				OS_ActivateTask((OsTaskType)OCB_Cfg.pAlarm[AlarmID]->TaskId);
			}
			else if(OCB_Cfg.pAlarm[AlarmID]->Action == ALARM_CALLBACK)
			{
				if(OCB_Cfg.pAlarm[AlarmID]->CallBackFunc != (void*)0)
				{
					//OCB_Cfg.pAlarm[AlarmID]->CallBackFunc();
				}
				else
				{
					/* NULL function pointer -> HookError could be called */
				}
			}
			else
			{
				/* Do nothing */
			}
		      
		}// if(OCB_Cfg.pAlarm[AlarmID]->AlarmCheckPoint <= (uint32)OCB_Cfg.OsSysTickCounter)
	}
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsRunCat2Isr
///
/// \descr  This function is the entry point of all category 2 interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsRunCat2Isr(void)
{
	/* Start user code for r_Config_OSTM0_interrupt. Do not edit comment generated here */
	/* End user code. Do not edit comment generated here */
	uint32 getEIIC;
	uint32 IsrIdx;

	//ISR Category 2 Wrapper Call
	//asm
	getEIIC = __stsr_rh(13, 0) & 0xfff; /* EIIC */
	
	//if(source == 84)
	//{
		//test++;  
	//	OsSysTickTimerIsr();
	//}//else{
		//test1++;  
	//}
	for(IsrIdx=0; IsrIdx < NB_OF_ISR; IsrIdx++)
  	{
		if(IsrLookupTable[IsrIdx].IsrNum == (uint32)getEIIC )
		{
			IsrLookupTable[IsrIdx].IsrFunc();
			return;
		}
	}
}
//------------------------------------------------------------------------------------------------------------------
/// \brief  OsStoreStackPointer
///
/// \descr  Store the current stack pointer in case of category 2 interrupt
///
/// \param  uint32 StackPtrValue: Current stack pointer
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OsStoreStackPointer(uint32 StackPtrValue)
{
	OCB_Cfg.OsIsrInterruptLevel = 1;

	if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
	{
		OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer = StackPtrValue;
	}
	else
	{
		OCB_Cfg.OsCurrentSystemStackPtr = StackPtrValue;
	}
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsGetSavedStackPointer
///
/// \descr  return the saved stack pointer in case of category 2 interrupt
///
/// \param  void
///
/// \return uint32 : saved stack pointer
//------------------------------------------------------------------------------------------------------------------
uint32 OsGetSavedStackPointer(void)
{
	OCB_Cfg.OsIsrInterruptLevel = 0;

	if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
	{
		return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
	}
	else
	{
		return(OCB_Cfg.OsCurrentSystemStackPtr);
	}
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsrCallDispatch
///
/// \descr  Call the dispatcher to switch the context if needed after an category 2 interrupt 
///
/// \param  uint32 StackPtr: Current stack pointer
///
/// \return uint32 : The new stack pointer after switching the context otherwise the last saved stack pointer
//------------------------------------------------------------------------------------------------------------------
uint32 OsIsrCallDispatch(uint32 StackPtr)
{
	if(OCB_Cfg.OsIsrCallDispatcher == 1)
	{
		if(	OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->TaskStatus == RUNNING && 
			OCB_Cfg.pTcb[OCB_Cfg.HighPrioReadyTaskIdx]->TaskStatus == READY)
		{
			return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
		}else{
			OCB_Cfg.OsIsrCallDispatcher = 0;
			return (uint32)OS_Dispatcher(StackPtr);
		}
	}else{
	
		if(OCB_Cfg.CurrentTaskIdx < NB_OF_TASKS)
		{
			return(OCB_Cfg.pTcb[OCB_Cfg.CurrentTaskIdx]->pCurrentStackPointer);
			//return(StackPtr);
		}
		else
		{
			return(StackPtr);
		}
	}
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_InitTimer
///
/// \descr  Init the HW timer used as system tick timer
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void OS_InitTimer(void)
{
	R_Config_OSTM0_Create();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_IdleLoop
///
/// \descr  This function is called by the dispatcher when no active task is found.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void OS_IdleLoop(void)
{
  /* No active task found */
  for(;;);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_StartTimer
///
/// \descr  Start the HW timer used as system tick timer
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
static void OS_StartTimer(void)
{
  R_Config_OSTM0_Start();
}


//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsInterruptContext
///
/// \descr  This function check the cpu mode (thread or interrupt).
///
/// \param  void
///
/// \return boolean: TRUE -> Cpu in interrupt context, FALSE -> Cpu not in interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsInterruptContext(void)
{
  uint32 CurrentPsw = 0U;

  OsGetPSW(&CurrentPsw);

  return((CurrentPsw & EXCEPTION_CODE_MASK) == 0U ? FALSE : TRUE);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OsIsCat2IntContext
///
/// \descr  This function check if the cpu is executing a category 2 interrupt.
///
/// \param  void
///
/// \return boolean: TRUE -> Category 2 interrupt context, FALSE -> none category 2 interrupt context
//------------------------------------------------------------------------------------------------------------------
boolean OsIsCat2IntContext(void)
{
  return((boolean)OCB_Cfg.OsIsrInterruptLevel);
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_DisableAllInterrupts
///
/// \descr  Disable all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_DisableAllInterrupts(void)
{
	__DI();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_EnableAllInterrupts
///
/// \descr  enable all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_EnableAllInterrupts(void)
{
	__EI();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_SuspendAllInterrupts
///
/// \descr  Suspend all interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_SuspendAllInterrupts(void)
{
	__DI();
}
//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ResumeAllInterrupts
///
/// \descr  Resume all suspended interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_ResumeAllInterrupts(void)
{
	__EI();
}
//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_ResumeOSInterrupts
///
/// \descr  Resume all suspended OS interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_ResumeOSInterrupts(void)
{
	__EI();
}

//------------------------------------------------------------------------------------------------------------------
/// \brief  OS_SuspendOSInterrupts
///
/// \descr  Suspend all OS interrupts.
///
/// \param  void
///
/// \return void
//------------------------------------------------------------------------------------------------------------------
void OS_SuspendOSInterrupts(void)
{
	__DI();
}