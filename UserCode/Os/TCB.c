

#include"TCB.h"


//#if !defined(__GNUC__)
//#pragma diag_suppress 1296,1,191,188
//#endif

/***************************************************/
/*            X Macro System Generation            */
/***************************************************/

/******************************************************************
		//#define OS_GEN_DATA_STRUCT
		//#include"OsCfg.h"
		//#undef OS_GEN_DATA_STRUCT
******************************************************************/

//		(Name,Prio,StackSize,NbOfActiv,AutoStart,TaskType,SchedType)
//    OS_TASK_DEF(OsTask_BSW_FG1_5ms_Com ,100 ,512 ,1 ,OS_AUTOSTART    ,EXTENDED ,FULL_PREEMPT)
//    OS_TASK_DEF(OsTask_BSW_FG1_10ms   ,101 ,512 ,1 ,OS_AUTOSTART    ,EXTENDED ,FULL_PREEMPT)
//    OS_TASK_DEF(OsTask_ASW_FG1_10ms   ,200 ,512 ,1 ,OS_AUTOSTART    ,EXTENDED ,FULL_PREEMPT)
//	OsTask_BSW_FG1_5ms_Com,
//	OsTask_BSW_FG1_10ms,
//	OsTask_ASW_FG1_10ms,
//

//Task(x);
TASK(OsTask_BSW_FG1_5ms_Com);
//#define STACK(x,y) uint32 Stack_T_##x[(y/4)]; const uint32 Stack_T_##x##_Size = y
uint32 Stack_T_OsTask_BSW_FG1_5ms_Com[128];
const uint32 Stack_T_OsTask_BSW_FG1_5ms_Com_Size = 512;
//STACK(OsTask_BSW_FG1_5ms_Com, 512);
static Tcb_t Tcb_t_OsTask_BSW_FG1_5ms_Com = { pTASK(OsTask_BSW_FG1_5ms_Com) ,	 
						100 ,				 
						OS_AUTOSTART ,			 
						(uint32)(&Stack_T_OsTask_BSW_FG1_5ms_Com[127]), 
						(uint32)(&Stack_T_OsTask_BSW_FG1_5ms_Com[0]) , 
						(uint32)(&Stack_T_OsTask_BSW_FG1_5ms_Com[127]),  
						SUSPENDED ,0 ,0 ,0 ,TE_EVT_BSW_CAN_COM_5MS ,		 
						1, EXTENDED, FULL_PREEMPT};
						
//Task(x);
TASK(OsTask_BSW_FG1_10ms);
//#define STACK(x,y) uint32 Stack_T_##x[(y/4)]; const uint32 Stack_T_##x##_Size = y
uint32 Stack_T_OsTask_BSW_FG1_10ms[128];
const uint32 Stack_T_OsTask_BSW_FG1_10ms_Size = 512;
//STACK(OsTask_BSW_FG1_5ms_Com, 512);
static Tcb_t Tcb_t_OsTask_BSW_FG1_10ms = { pTASK(OsTask_BSW_FG1_10ms) ,	 
						101 ,				 
						OS_AUTOSTART ,			 
						(uint32)(&Stack_T_OsTask_BSW_FG1_10ms[127]), 
						(uint32)(&Stack_T_OsTask_BSW_FG1_10ms[0]) , 
						(uint32)(&Stack_T_OsTask_BSW_FG1_10ms[127]),  
						SUSPENDED ,0 ,0 ,0 ,TE_EVT_BSW_10MS ,		 
						1, EXTENDED, FULL_PREEMPT};
						
//Task(x);						
TASK(OsTask_ASW_FG1_10ms);
//#define STACK(x,y) uint32 Stack_T_##x[(y/4)]; const uint32 Stack_T_##x##_Size = y
uint32 Stack_T_OsTask_ASW_FG1_10ms[128];
const uint32 Stack_T_OsTask_ASW_FG1_10ms_Size = 512;
//STACK(OsTask_BSW_FG1_5ms_Com, 512);
static Tcb_t Tcb_t_OsTask_ASW_FG1_10ms = { pTASK(OsTask_ASW_FG1_10ms) ,	 
						201 ,				 
						OS_AUTOSTART ,			 
						(uint32)(&Stack_T_OsTask_ASW_FG1_10ms[127]), 
						(uint32)(&Stack_T_OsTask_ASW_FG1_10ms[0]) , 
						(uint32)(&Stack_T_OsTask_ASW_FG1_10ms[127]),  
						SUSPENDED ,0 ,0 ,0 ,TE_EVT_ASW_10MS ,		 
						1, EXTENDED, FULL_PREEMPT};
												
//OS_ALARM_DEF(Name,Action,Event,AutoStart,task,Callback) static Alarm_t Alarm_##Name = {0, 0,  Event,task, Action, AutoStart, ALARM_FREE, 0, 0, 0, Callback};
//OS_ALARM_DEF(OsAlarm_BSW_FG1_5ms_Com, ALARM_SET_EVENT ,INVALID_EVENT, ALARM_NO_AUTOSTART ,OsTask_BSW_FG1_5ms_Com   ,0)
//OS_ALARM_DEF(OsAlarm_BSW_FG1_10ms, ALARM_SET_EVENT ,INVALID_EVENT, ALARM_NO_AUTOSTART ,OsTask_BSW_FG1_10ms ,0)
//OS_ALARM_DEF(OsAlarm_ASW_FG1_10ms, ALARM_SET_EVENT ,INVALID_EVENT, ALARM_NO_AUTOSTART ,OsTask_ASW_FG1_10ms ,0)
static Alarm_t Alarm_OsAlarm_BSW_FG1_5ms_Com = {0, 0,  TE_EVT_BSW_CAN_COM_5MS, OsTask_BSW_FG1_5ms_Com, ALARM_SET_EVENT, TE_EVT_BSW_CAN_COM_5MS, ALARM_FREE, 0, 0, 0, 0};
static Alarm_t Alarm_OsAlarm_BSW_FG1_10ms = {0, 0,  TE_EVT_BSW_10MS, OsTask_BSW_FG1_10ms, ALARM_SET_EVENT, OsTask_BSW_FG1_10ms, ALARM_FREE, 0, 0, 0, 0};
static Alarm_t Alarm_OsAlarm_ASW_FG1_10ms = {0, 0,  TE_EVT_ASW_10MS, OsTask_ASW_FG1_10ms, ALARM_SET_EVENT, OsTask_ASW_FG1_10ms, ALARM_FREE, 0, 0, 0, 0};


//Resource
//OS_RESOURCE_DEF(RES_SCHEDULER ,RES_SCHEDULER_PRIO , {1,1})
//#define OS_RESOURCE_DEF(Name,CeilingPrio,AuthorizedTasks...) static uint32 AuthorizedTask_##Name[NB_OF_TASKS] = AuthorizedTasks; static Resource_t Resource_##Name = {CeilingPrio, INVALID_TASK, &AuthorizedTask_##Name[0]};
static uint32 AuthorizedTask_RES_SCHEDULER[INVALID_TASK] = {1,1};
static Resource_t Resource_RES_SCHEDULER = {RES_SCHEDULER_PRIO, INVALID_TASK, &AuthorizedTask_RES_SCHEDULER[0]};

//OS_INTERRUPT_CAT2_DEF(15,SysTickTimer)

//#define OS_INTERRUPT_BEGIN                                                       Isr_t IsrLookupTable[] = {
//#define OS_INTERRUPT_CAT2_DEF(IsrNbr,IsrFunc)                                    {IsrNbr,&Os##IsrFunc##Isr},
//#define OS_INTERRUPT_END                                                         {0,0}};
Isr_t IsrLookupTable[] = {{84,&OsSysTickTimerIsr},
			  {23,&OsRCANGRECC0Isr},
			  {24,&OsRCAN0ERRIsr},
			  {18,&OsADCA0GRPSCANIsr},
//			  {8,&OsPWMGATECTRLIsr},
			  {37,&OsINTC0Isr},
			  {38,&OsINTC1Isr},
			  {34,&OsUART0SENDIsr},
			  {35,&OsUART0RECVIsr},
			  {36,&OsUART0ERRIsr},
			  {0,0}};

/******************************************************************
			//#define OS_GEN_TCB
			//#include"OsCfg.h"
			//#undef OS_GEN_TCB
******************************************************************/
static Tcb_t* CCB_Cfg[NB_OF_TASKS + 1] = {
						&Tcb_t_OsTask_BSW_FG1_5ms_Com,
						&Tcb_t_OsTask_BSW_FG1_10ms,
						&Tcb_t_OsTask_ASW_FG1_10ms,
						0};
static Alarm_t* Alarm_Cfg[NB_OF_ALARMS + 1]={
						&Alarm_OsAlarm_BSW_FG1_5ms_Com,
						&Alarm_OsAlarm_BSW_FG1_10ms,
						&Alarm_OsAlarm_ASW_FG1_10ms,
						0};

static Resource_t* Res_Cfg[NB_OF_RESOURCE + 1]={
						&Resource_RES_SCHEDULER,
						0};
/******************************************************************
			//#define OS_GEN_OCB
			//#include"OsCfg.h"
			//#undef OS_GEN_OCB
******************************************************************/						
volatile Ocb_t OCB_Cfg = {
				&CCB_Cfg[0],
				&Alarm_Cfg[0],
				&Res_Cfg[0],
				0,0,0,0,0,0,0,0};
				
volatile uint32 * pxCurrentStackPoint;
volatile uint32 * pxCurrentStackPoint_top;
volatile StackType_t usCriticalNesting = (( StackType_t ) 10);