/***********************************************************************************************************************
* File Name        : App_CanCommMod.c
* Version          : 1.0
* Device(s)        : R7F701695
* Description      : 
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "App_CanCommMod.h"
#include "r_typedefs.h"
#include "Rte.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static uint8_t				CanComm_SctOption_Data = MODE_SCTOPTION_DEFAULT;


/*FUNCTION**********************************************************************
 *
 * Function Name : CanCommMod_MainLogic_10ms
 * Description   :
 *
 *END**************************************************************************/
void CanCommMod_MainLogic_10ms(void)
{
	/*  */
	if(CanComm_SctOption_Data == MODE_SCTOPTION_DEFAULT)
	{
		Rte_Read_DIOProcMod_CanCommMod_SctOption_Data(&CanComm_SctOption_Data);
	}else if(CanComm_SctOption_Data == MODE_SCTOPTION_HV){
		/* Mode Select End - [MODE_SCTOPTION_HV] */
		Rte_Call_CanMM_SetComMode(CANMM_TX_OFF_RX_OFF);
	}else{
		/* Mode Select End - [MODE_SCTOPTION_LV] */
		Rte_Call_CanMM_SetComMode(CANMM_TX_ON_RX_ON);
	}
	
}