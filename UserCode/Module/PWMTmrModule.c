/***********************************************************************************************************************
* File Name        : PWMTmrModule.c
* Version          : 1.0.150
* Device(s)        : R7F701695
* Description      : This file implements main function.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "PWMTmrModule.h"
#include "Config_PWMZ1.h"
#include "Config_PWMZ2.h"

PWM_TMR_GateCtrl_t	st_PwmTmrGateCtrl= {
				.st_ZoneDrCtrl = {
					.u8ZoneStatus = 0U,
					.fZoneCurrentDuty = 0.0F,
				},
				.st_ZonePsCtrl = {
					.u8ZoneStatus = 0U,
					.fZoneCurrentDuty = 0.0F,
				},
				.st_PwmModeSta = ZONE_CTRL_STANDBY,
				.u32ForceDischargeCnt = 0U
			};
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/


/***********************************************************************************************************************
* Function Name: PWM_ZoneASetDuty
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

PwmErr_t PWM_ZoneASetDuty(float fTgtDuty)
{
	PwmErr_t ret = PWM_CTRL_SUCCESS;
	
	if(fTgtDuty >= 0.0F && fTgtDuty <= 100.0F)
	{
		st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneTgtDuty = fTgtDuty;
	}else{
		ret = PWM_CTRL_OUTOFRANGE;
	}
	
	return ret;
}

/***********************************************************************************************************************
* Function Name: PWM_ZoneBSetDuty
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

PwmErr_t PWM_ZoneBSetDuty(float fTgtDuty)
{
	PwmErr_t ret = PWM_CTRL_SUCCESS;
	
	if(fTgtDuty >= 0.0F && fTgtDuty <= 100.0F)
	{
		st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneTgtDuty = fTgtDuty;

	}else{
		ret = PWM_CTRL_OUTOFRANGE;
	}

	return ret;
}

/***********************************************************************************************************************
* Function Name: PWM_MainService_10ms_logic
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void PWM_MainService_10ms_logic(void)
{
	//PwmErr_t ret = PWM_CTRL_SUCCESS;
	
	int	s32ZoneDuty = 0;
	static uint8_t u8PwmStart = 0U;
	
	if(st_PwmTmrGateCtrl.st_PwmModeSta == ZONE_CTRL_STANDBY)
	{
		/* ZONE CTRL STANDBY MODE -- SHIFT PWM TIMMING SETTING */
		u8PwmStart++;
		
		if(u8PwmStart == 1U)
		{
			R_Config_PWMZ1_Start();	
		}
		
		if(u8PwmStart == 11U){
			R_Config_PWMZ2_Start();	
			st_PwmTmrGateCtrl.st_PwmModeSta = ZONE_CTRL_MODE;
			u8PwmStart = 0;	
		}	
		
			
	}else if (st_PwmTmrGateCtrl.st_PwmModeSta == ZONE_CTRL_MODE){
		/* DR PWM Duty Change */
		if(st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneTgtDuty != st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneCurrentDuty)
		{
			if(st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneTgtDuty > 0.0F)
			{
				//Turn On
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.u8ZoneStatus = 1U;
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneCurrentDuty = st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneTgtDuty;
				s32ZoneDuty = st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneCurrentDuty * 100;
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.u16ZoneTgtDutyRawValue = (uint16_t)((uint32_t)(s32ZoneDuty * _TAUD0_CHANNEL8_COMPARE_VALUE)/10000U);
				TAUD0.CDR9 = st_PwmTmrGateCtrl.st_ZoneDrCtrl.u16ZoneTgtDutyRawValue;	
			}else{
				//Turn Off
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.u8ZoneStatus = 0U;
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneCurrentDuty = 0U;
				st_PwmTmrGateCtrl.st_ZoneDrCtrl.u16ZoneTgtDutyRawValue = 0U;
				TAUD0.CDR9 = 0U;
			}
		}
		
		/* PS PWM Change */
		if(st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneTgtDuty != st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneCurrentDuty)
		{
			if(st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneTgtDuty > 0.0F)
			{
				//Turn On
				st_PwmTmrGateCtrl.st_ZonePsCtrl.u8ZoneStatus = 1U;
				st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneCurrentDuty = st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneTgtDuty;
				s32ZoneDuty = st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneCurrentDuty * 100;
				st_PwmTmrGateCtrl.st_ZonePsCtrl.u16ZoneTgtDutyRawValue = (uint16_t)((uint32_t)(s32ZoneDuty * _TAUD0_CHANNEL10_COMPARE_VALUE)/10000U);
				TAUD0.CDR11 = st_PwmTmrGateCtrl.st_ZonePsCtrl.u16ZoneTgtDutyRawValue;
			}else{
				//Turn Off
				st_PwmTmrGateCtrl.st_ZonePsCtrl.u8ZoneStatus = 0U;
				st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneCurrentDuty = 0U;
				st_PwmTmrGateCtrl.st_ZonePsCtrl.u16ZoneTgtDutyRawValue = 0U;
				TAUD0.CDR11 = 0U;
			}
		}
	}else if (st_PwmTmrGateCtrl.st_PwmModeSta == FORCE_DISCHARGE_MODE_RUN){
		/* For Discharge RUN 1Sec */
		if(st_PwmTmrGateCtrl.u32ForceDischargeCnt == 0U)
		{
			//Start
			TAUD0.CDR9 = _TAUD0_CHANNEL8_COMPARE_VALUE;
			TAUD0.CDR11 = 0U;
			R_Config_PWMZ1_Start();
			R_Config_PWMZ2_Start();
		}
		
		if(st_PwmTmrGateCtrl.u32ForceDischargeCnt == 50U)
		{
			TAUD0.CDR9 = 0U;
			TAUD0.CDR11 = _TAUD0_CHANNEL10_COMPARE_VALUE;
			R_Config_PWMZ1_Start();
			R_Config_PWMZ2_Start();
		}
		
		if(st_PwmTmrGateCtrl.u32ForceDischargeCnt == 100U)
		{
			TAUD0.CDR9 = 0U;
			TAUD0.CDR11 = 0U;
			R_Config_PWMZ1_Start();
			R_Config_PWMZ2_Start();
			st_PwmTmrGateCtrl.st_PwmModeSta = FORCE_DISCHARGE_MODE_END;
			
		}
		
		st_PwmTmrGateCtrl.u32ForceDischargeCnt++;
	}else{
		/* FORCE_DISCHARGE_MODE_END */
		// Wait Delay And Re Standby
		st_PwmTmrGateCtrl.u32ForceDischargeCnt++;
		if( st_PwmTmrGateCtrl.u32ForceDischargeCnt == 105U)
		{
			st_PwmTmrGateCtrl.u32ForceDischargeCnt = 0U;
			
			st_PwmTmrGateCtrl.st_ZoneDrCtrl.u8ZoneStatus = 0U;
			st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneCurrentDuty = 0U;
			st_PwmTmrGateCtrl.st_ZoneDrCtrl.fZoneTgtDuty = 0U;
			st_PwmTmrGateCtrl.st_ZoneDrCtrl.u16ZoneTgtDutyRawValue = 0U;
			TAUD0.CDR9 = 0U;
			
			st_PwmTmrGateCtrl.st_ZonePsCtrl.u8ZoneStatus = 0U;
			st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneCurrentDuty = 0U;
			st_PwmTmrGateCtrl.st_ZonePsCtrl.fZoneTgtDuty = 0U;
			st_PwmTmrGateCtrl.st_ZonePsCtrl.u16ZoneTgtDutyRawValue = 0U;
			TAUD0.CDR11 = 0U;
			
			st_PwmTmrGateCtrl.st_PwmModeSta = ZONE_CTRL_STANDBY;	
		}
	}
}

PwmErr_t PWM_ForDisChargeRun()
{
	PwmErr_t ret = PWM_CTRL_SUCCESS;
	if( (st_PwmTmrGateCtrl.st_PwmModeSta == FORCE_DISCHARGE_MODE_RUN) ||
	(st_PwmTmrGateCtrl.st_PwmModeSta == FORCE_DISCHARGE_MODE_END))
	{
		ret = PWM_CTRL_DISCHARGE_RUN;
	}else{
		st_PwmTmrGateCtrl.st_PwmModeSta = FORCE_DISCHARGE_MODE_RUN;
	}
	return (ret);
}