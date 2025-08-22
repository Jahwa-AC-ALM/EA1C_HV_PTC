
#ifndef PWMTmrModule_H
#define PWMTmrModule_H
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_device.h"
#include "r_typedefs.h"
/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

typedef enum {
	PWM_CTRL_SUCCESS = 0, 
	PWM_CTRL_DISCHARGE_RUN,
	PWM_CTRL_OUTOFRANGE
}PwmErr_t;

typedef enum {
	ZONE_CTRL_STANDBY = 0U,
	ZONE_CTRL_MODE,
	FORCE_DISCHARGE_MODE_RUN,
	FORCE_DISCHARGE_MODE_END
}PWM_RUN_MODE;


typedef struct {
	uint8_t				u8ZoneStatus;			
	float				fZoneCurrentDuty;		
	float				fZoneTgtDuty;
	uint16_t			u16ZoneTgtDutyRawValue;
}PWM_TMR_ZONE_STA;

typedef struct {
	PWM_TMR_ZONE_STA		st_ZoneDrCtrl;
	PWM_TMR_ZONE_STA		st_ZonePsCtrl;
	PWM_RUN_MODE			st_PwmModeSta;
	uint32_t			u32ForceDischargeCnt;
}PWM_TMR_GateCtrl_t;


/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

//USER DEFINE
//void PWM_GateCtrlServiceIsr(void);
void PWM_MainService_10ms_logic(void);
PwmErr_t PWM_ZoneASetDuty(float fTgtDuty);
PwmErr_t PWM_ZoneBSetDuty(float fTgtDuty);
PwmErr_t PWM_ForDisChargeRun();

#endif