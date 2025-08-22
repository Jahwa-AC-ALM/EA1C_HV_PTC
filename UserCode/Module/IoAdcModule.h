
#ifndef IoAdcModule_H
#define IoAdcModule_H

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_device.h"
#include "r_typedefs.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
/**************************************************************
* 	1. ADC Define
***************************************************************/
/* ADC RAW Filter Mode */
#define ADC_CH_BUFFER					20U
#define ADC_RAW_EMA_ALPHA				0.9F

#define ADC_RAW_LOW_SAMPLING_MODE			0U
#define ADC_RAW_EMA_SAMPLING_MODE			1U
#define ADC_RAW_SAMPLED_AVG_MODE			2U

/**************************************************************
* 	2. GPIO Define
***************************************************************/

/* GPIO INPUT PORT CONTROL*/
// -- JP0.3
#define READ_GPIO_BOOT_OPTION1()			((JTAG.JPPR0)&(1U << 3))

// -- JP0.4
#define READ_GPIO_BOOT_OPTION2()			((JTAG.JPPR0)&(1U << 4))

/* GPIO OUTPUT PORT CONTROL*/
// -- P10.3 High Side Gate EN
#define SET_GPIO_IGBT_HS_EL()				((PORT.P10) |= (1U << 3))
#define CLEAR_GPIO_IGBT_HS_EL()				((PORT.P10) &= ~(1U << 3))

// -- P10.4 For PWM
#define SET_GPIO_IGBT_A_LS()				((PORT.P10) |= (1U << 4))
#define CLEAR_GPIO_IGBT_A_LS()				((PORT.P10) &= ~(1U << 4))

// -- P10.5 For PWM
#define SET_GPIO_IGBT_B_LS()				((PORT.P10) |= (1U << 5))
#define CLEAR_GPIO_IGBT_B_LS()				((PORT.P10) &= ~(1U << 5))

// -- P10.6
#define SET_GPIO_EXT_WDG_EN()				((PORT.P10) |= (1U << 6))
#define CLEAR_GPIO_EXT_WDG_EN()				((PORT.P10) &= ~(1U << 6))

// -- P10.7
#define SET_GPIO_EXT_WDG()				((PORT.P10) |= (1U << 7))
#define CLEAR_GPIO_EXT_WDG()				((PORT.P10) &= ~(1U << 7))


// #define EL PORT10_3 Output
/*
JP04 option 1 input
JP03 Option 2 input


P10 3 IGBT HIGH SIDE CTRL GPIO OUTPUT	(High High IGBT)
P10 4 IGBT 1 PWM CTRL GPIO OUTPUT
P10 5 IGBT 2 PWM CTRL GPIO OUTPUT
P10 6 EXTERNAL WATCHDOG_EN GPIO OUTPUT

*/

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum 
{
	//TEMP_PCB = 0,		// 0 -- ADCA0I0 [ Not Assigned ] 
	ACH_15VD_ADC = 1,	// 1 -- ADCA0I1 [ 15VD_ADC ]
	ACH_HVLV_MON,	   	// 2 -- ADCA0I2 [ HV/LV MON ]
	ACH_PCB_NTC,	   	// 3 -- ADCA0I3 [ PCB Temperature ]
	ACH_IGBT_NTC_B,	   	// 4 -- ADCA0I4 [ IGBT 2(Zone B) Temperature ]
	ACH_IGBT_NTC_A, 	// 5 -- ADCA0I5 [ IGBT 1 Temperature ]
	ACH_CS_B, 		// 6 -- ADCA0I6 [ Current Sensor 2(Zone B) ]
	ACH_CS_A,	   	// 7 -- ADCA0I7 [ Current Sensor 1(Zone A) ]
	ACH_HVD_A,	   	// 8 -- ADCA0I0S [ HVD ADC 1(Zone A) ]
	ACH_HVD_B,	   	// 9 -- ADCA0I1S [ HVD ADC 2(Zone B) ]
	ACH_CORE_NTC_A,	   	// 10 -- ADCA0I2S [ Core Temperature 1(Zone A) ]
	ACH_CORE_NTC_B	   	// 11 -- ADCA0I3S [ Core Temperature 2(Zone B) ]
}ADC_CH;

typedef struct
{
	uint8_t 	AdcRawSamplingMode;
	uint16_t	AdcRaw[ADC_CH_BUFFER];
	uint16_t	AdcRaw_EMA[ADC_CH_BUFFER];
	uint32_t	SumAdcRaw[ADC_CH_BUFFER];
	uint32_t	AdcAvgRaw[ADC_CH_BUFFER];
	uint16_t	AdcAvgMod_Cnt;
}AdcM_Raw_Data_t;


/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
//ADC
void IoAdc_Get_ADCA0_ScanGroupIsr();
void IoAdc_MainService_10ms_logic();


//GPIO
uint8_t IoAdc_CheckModOption();


#endif