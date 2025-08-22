/***********************************************************************************************************************
* File Name        : App_DIOProcMod.c
* Version          : 1.0
* Device(s)        : R7F701695
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "App_DIOProcMod.h"
#include "Rte.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static uint8_t				DIoMod_SctOption_Data = MODE_SCTOPTION_DEFAULT;
/*FUNCTION**********************************************************************
 *
 * Function Name : FailSafeMod_MainLogic_10ms
 * Description   :
 *
 *END**************************************************************************/
void DIOProcMod_MainLogic_10ms(void)
{
	/*  */
	if(DIoMod_SctOption_Data == MODE_SCTOPTION_DEFAULT)
	{
		(void)Rte_Read_IoAdcMM_DIOProcMod_SctOption_Data(&DIoMod_SctOption_Data);
		
		if(DIoMod_SctOption_Data !=MODE_SCTOPTION_DEFAULT)
		{
			/* Write Other Module */
			(void)Rte_Write_DIOProcMod_CanCommMod_SctOption_Data(DIoMod_SctOption_Data);
			(void)Rte_Write_DIOProcMod_PTCModMgntMod_SctOption_Data(DIoMod_SctOption_Data);
			(void)Rte_Write_DIOProcMod_SerialCommMod_SctOption_Data(DIoMod_SctOption_Data);
			(void)Rte_Write_DIOProcMod_PTCPwrMgntMod_SctOption_Data(DIoMod_SctOption_Data);
		}
	}else if(DIoMod_SctOption_Data == MODE_SCTOPTION_HV){
		/* Mode Select End - [MODE_SCTOPTION_HV] */
		
	
	}else{
		/* Mode Select End - [MODE_SCTOPTION_LV] */
	}
	
}