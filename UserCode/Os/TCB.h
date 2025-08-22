#ifndef __TCB_H__
#define __TCB_H__

#include"OsTypes.h"

/***************************************************/
/*            X Macro System Generation            */
/***************************************************/
//Gen Macro를 통해 Enum 만들어 놓음. (Task/event/Alarm/Resource/Interrupt)
//#define OS_GEN_ENUM
//#include"OsCfg.h"
//#undef OS_GEN_ENUM

#define NB_OF_TASKS		3
#define NB_OF_ALARMS		3
#define NB_OF_RESOURCE		1
#define NB_OF_ISR		5

// Task
enum{
	OsTask_BSW_FG1_5ms_Com,
	OsTask_BSW_FG1_10ms,
	OsTask_ASW_FG1_10ms,
	INVALID_TASK
};

// Event
enum{
	OSEVT_BSW_MEM_PROCESS = 0x01,
	TE_EVT_BSW_CAN_COM_5MS = 0x02,
	TE_EVT_BSW_10MS = 0x04,
	TE_EVT_ASW_10MS = 0x08,
	INVALID_EVENT
};

//Alarm
enum{
	OsAlarm_BSW_FG1_5ms_Com,
	OsAlarm_BSW_FG1_10ms,
	OsAlarm_ASW_FG1_10ms,
	INVALID_ALARM
};
//Resource 
enum{
	RES_SCHEDULER,
	INVALID_RESOURCE
};
//Interrupt Cat2 
enum{
	SysTickTimer,
	INVALID_ISR
};

//Gen Macro를 통해서 Proto Function 만들어 놓음. (Task/event/Alarm/Resource/Interrupt)
//#define OS_GEN_FUNC_PROTO
//#include"OsCfg.h"
//#undef OS_GEN_FUNC_PROTO
//Interrupt Cat2 (Proto Function
extern Isr_t IsrLookupTable[];
extern void OsSysTickTimerIsr(void);
extern void OsRCANGRECC0Isr(void);
extern void OsRCAN0ERRIsr(void);
extern void OsADCA0GRPSCANIsr(void);
//extern void OsPWMGATECTRLIsr(void);
extern void OsINTC0Isr(void);
extern void OsINTC1Isr(void);
extern void OsUART0SENDIsr(void);
extern void OsUART0RECVIsr(void);
extern void OsUART0ERRIsr(void);

/* OS Config */
extern volatile Ocb_t OCB_Cfg;
extern volatile uint32 * pxCurrentStackPoint;
extern volatile uint32 * pxCurrentStackPoint_top;
extern volatile StackType_t usCriticalNesting;

#define STARTUPHOOK   0
#define ERRORHOOK     0
#define SHUTDOWNHOOK  0
#define PRETASKHOOK   0
#define POSTTASKHOOK  0

#define RES_SCHEDULER_PRIO (uint32)0x7FFFFFFFu
#define RES_TRACE_PRIO     (uint32)1u

#endif