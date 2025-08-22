/***********************************************************************************************************************
* File Name        : IoAdcModule.c
* Version          : 1.0.150
* Device(s)        : R7F701695
* Description      : This file implements main function.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "IoAdcModule.h"
#include "Rte.h"

//uint16_t		GetArrayCnt=0;
//uint16_t		GetArrayCnt_Temp=0;

static uint8_t					u8ModeSctOptionResult = MODE_SCTOPTION_DEFAULT;
static DATA_IN_PROC_RAW_VALUE			st_DIOProcTxRawData;
static AdcM_Raw_Data_t 				st_IoAdc_Data_Raw = {
									.AdcRawSamplingMode = ADC_RAW_EMA_SAMPLING_MODE 
								     };
/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: ADC_IO_Service
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void IoAdc_MainService_10ms_logic()
{
	/* SctOption Check */
	if(u8ModeSctOptionResult == MODE_SCTOPTION_DEFAULT)
	{
		//Check Mode
		u8ModeSctOptionResult = IoAdc_CheckModOption();
		//RTE Write!
		Rte_Write_IoAdcMM_DIOProcMod_SctOption_Data(u8ModeSctOptionResult);
		Rte_Write_IoAdcMM_CanMM_SctOption_Data(u8ModeSctOptionResult);
	}
	
	/* RTE Write -- IoAdcMM to DIOProcMod */
	if(st_IoAdc_Data_Raw.AdcRawSamplingMode == ADC_RAW_EMA_SAMPLING_MODE)
	{
		if(u8ModeSctOptionResult == MODE_SCTOPTION_HV)
		{
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_15VD_ADC];
			st_DIOProcTxRawData.HighVol_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_HVLV_MON];
			//st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_PCB_NTC];
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_IGBT_NTC_A];
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_IGBT_NTC_B];
			st_DIOProcTxRawData.DrCurr_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_CS_A];
			st_DIOProcTxRawData.PassCurr_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_CS_B];
			st_DIOProcTxRawData.DrHVDVol_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_HVD_A];
			st_DIOProcTxRawData.PassHVDVol_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_HVD_B];
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_CORE_NTC_A];
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_CORE_NTC_B];
		}else{
			//LV
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = 0U;
			st_DIOProcTxRawData.HighVol_Ad = 0U;
			st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcRaw_EMA[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = 0U;
			st_DIOProcTxRawData.DrCurr_Ad = 0U;
			st_DIOProcTxRawData.PassCurr_Ad = 0U;
			st_DIOProcTxRawData.DrHVDVol_Ad = 0U;
			st_DIOProcTxRawData.PassHVDVol_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = 0U;
		}
	}else if(st_IoAdc_Data_Raw.AdcRawSamplingMode == ADC_RAW_SAMPLED_AVG_MODE){
		if(u8ModeSctOptionResult == MODE_SCTOPTION_HV)
		{
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_15VD_ADC];
			st_DIOProcTxRawData.HighVol_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_HVLV_MON];
			//st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_PCB_NTC];
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_IGBT_NTC_A];
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_IGBT_NTC_B];
			st_DIOProcTxRawData.DrCurr_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_CS_A];
			st_DIOProcTxRawData.PassCurr_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_CS_B];
			st_DIOProcTxRawData.DrHVDVol_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_HVD_A];
			st_DIOProcTxRawData.PassHVDVol_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_HVD_B];
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_CORE_NTC_A];
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_CORE_NTC_B];
		}else{
			//LV
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = 0U;
			st_DIOProcTxRawData.HighVol_Ad = 0U;
			st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcAvgRaw[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = 0U;
			st_DIOProcTxRawData.DrCurr_Ad = 0U;
			st_DIOProcTxRawData.PassCurr_Ad = 0U;
			st_DIOProcTxRawData.DrHVDVol_Ad = 0U;
			st_DIOProcTxRawData.PassHVDVol_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = 0U;
		}
	}else{
		if(u8ModeSctOptionResult == MODE_SCTOPTION_HV)
		{
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_15VD_ADC];
			st_DIOProcTxRawData.HighVol_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_HVLV_MON];
			//st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_PCB_NTC];
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_IGBT_NTC_A];
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_IGBT_NTC_B];
			st_DIOProcTxRawData.DrCurr_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_CS_A];
			st_DIOProcTxRawData.PassCurr_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_CS_B];
			st_DIOProcTxRawData.DrHVDVol_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_HVD_A];
			st_DIOProcTxRawData.PassHVDVol_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_HVD_B];
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_CORE_NTC_A];
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_CORE_NTC_B];
		}else{
			//LV
			st_DIOProcTxRawData.LDO_15Vol_Mon_Ad = 0U;
			st_DIOProcTxRawData.HighVol_Ad = 0U;
			st_DIOProcTxRawData.LowVol_Ad = st_IoAdc_Data_Raw.AdcRaw[ACH_HVLV_MON];
			st_DIOProcTxRawData.PcbNTCTemp_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.IgbtNTCTemp_Pass_Ad = 0U;
			st_DIOProcTxRawData.DrCurr_Ad = 0U;
			st_DIOProcTxRawData.PassCurr_Ad = 0U;
			st_DIOProcTxRawData.DrHVDVol_Ad = 0U;
			st_DIOProcTxRawData.PassHVDVol_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Dr_Ad = 0U;
			st_DIOProcTxRawData.CoreNTCTemp_Pass_Ad = 0U;
		}
	}

	(void)Rte_Write_IoAdcMM_DIOProcMod_RawData(&st_DIOProcTxRawData);
}

/***********************************************************************************************************************
* Function Name: IoAdc_Get_ADCA0_ScanGroup()
* Description  : This function handles the INTADCA0I0 interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void IoAdc_Get_ADCA0_ScanGroupIsr()
{	
	if(st_IoAdc_Data_Raw.AdcRawSamplingMode == ADC_RAW_EMA_SAMPLING_MODE)
	{
		st_IoAdc_Data_Raw.AdcRaw_EMA[0] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20100U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[0]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[1] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20102U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[1]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[2] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20104U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[2]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[3] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20106U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[3]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[4] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20108U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[4]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[5] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF2010AU)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[5]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[6] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF2010CU)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[6]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[7] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF2010EU)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[7]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[8] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20110U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[8]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[9] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20112U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[9]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[10] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20114U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[10]);
		st_IoAdc_Data_Raw.AdcRaw_EMA[11] = (ADC_RAW_EMA_ALPHA*(float)((*(uint32_t*)(0xFFF20116U)) & 0xFFFFU) + (1 - ADC_RAW_EMA_ALPHA) * st_IoAdc_Data_Raw.AdcRaw_EMA[11]);
		
	}else if(st_IoAdc_Data_Raw.AdcRawSamplingMode == ADC_RAW_SAMPLED_AVG_MODE){
		
		st_IoAdc_Data_Raw.AdcAvgMod_Cnt++;
		
		if(st_IoAdc_Data_Raw.AdcAvgMod_Cnt >= 300)
		{
			st_IoAdc_Data_Raw.AdcAvgRaw[0] = st_IoAdc_Data_Raw.SumAdcRaw[0]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[1] = st_IoAdc_Data_Raw.SumAdcRaw[1]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[2] = st_IoAdc_Data_Raw.SumAdcRaw[2]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[3] = st_IoAdc_Data_Raw.SumAdcRaw[3]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[4] = st_IoAdc_Data_Raw.SumAdcRaw[4]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[5] = st_IoAdc_Data_Raw.SumAdcRaw[5]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[6] = st_IoAdc_Data_Raw.SumAdcRaw[6]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[7] = st_IoAdc_Data_Raw.SumAdcRaw[7]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[8] = st_IoAdc_Data_Raw.SumAdcRaw[8]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[9] = st_IoAdc_Data_Raw.SumAdcRaw[9]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[10] = st_IoAdc_Data_Raw.SumAdcRaw[10]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			st_IoAdc_Data_Raw.AdcAvgRaw[11] = st_IoAdc_Data_Raw.SumAdcRaw[11]/st_IoAdc_Data_Raw.AdcAvgMod_Cnt;
			
			st_IoAdc_Data_Raw.AdcAvgMod_Cnt = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[0] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[1] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[2] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[3] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[4] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[5] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[6] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[7] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[8] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[9] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[10] = 0;
			st_IoAdc_Data_Raw.SumAdcRaw[11] = 0;
		}
		
		st_IoAdc_Data_Raw.SumAdcRaw[0] += (uint16_t)(*(uint32_t*)(0xFFF20100U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[1] += (uint16_t)(*(uint32_t*)(0xFFF20102U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[2] += (uint16_t)(*(uint32_t*)(0xFFF20104U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[3] += (uint16_t)(*(uint32_t*)(0xFFF20106U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[4] += (uint16_t)(*(uint32_t*)(0xFFF20108U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[5] += (uint16_t)(*(uint32_t*)(0xFFF2010AU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[6] += (uint16_t)(*(uint32_t*)(0xFFF2010CU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[7] += (uint16_t)(*(uint32_t*)(0xFFF2010EU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[8] += (uint16_t)(*(uint32_t*)(0xFFF20110U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[9] += (uint16_t)(*(uint32_t*)(0xFFF20112U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[10] += (uint16_t)(*(uint32_t*)(0xFFF20114U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.SumAdcRaw[11] += (uint16_t)(*(uint32_t*)(0xFFF20116U)) & 0xFFFFU;
	
	}else{
		st_IoAdc_Data_Raw.AdcRaw[0] = (uint16_t)(*(uint32_t*)(0xFFF20100U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[1] = (uint16_t)(*(uint32_t*)(0xFFF20102U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[2] = (uint16_t)(*(uint32_t*)(0xFFF20104U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[3] = (uint16_t)(*(uint32_t*)(0xFFF20106U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[4] = (uint16_t)(*(uint32_t*)(0xFFF20108U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[5] = (uint16_t)(*(uint32_t*)(0xFFF2010AU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[6] = (uint16_t)(*(uint32_t*)(0xFFF2010CU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[7] = (uint16_t)(*(uint32_t*)(0xFFF2010EU)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[8] = (uint16_t)(*(uint32_t*)(0xFFF20110U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[9] = (uint16_t)(*(uint32_t*)(0xFFF20112U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[10] = (uint16_t)(*(uint32_t*)(0xFFF20114U)) & 0xFFFFU;
		st_IoAdc_Data_Raw.AdcRaw[11] = (uint16_t)(*(uint32_t*)(0xFFF20116U)) & 0xFFFFU;
	}
}

uint8_t IoAdc_CheckModOption()
{
	uint8_t option1, option2;
	uint8_t u8ModeCheckResults = MODE_SCTOPTION_DEFAULT;
	
	option1 = READ_GPIO_BOOT_OPTION1();
	option2 = READ_GPIO_BOOT_OPTION2();
	
	if(option1 == GPIO_HIGH && option2 == GPIO_LOW)
	{
		u8ModeCheckResults = MODE_SCTOPTION_LV;
		
	}else if(option1 == GPIO_LOW && option2 == GPIO_HIGH){
		
		u8ModeCheckResults = MODE_SCTOPTION_HV;
		
	}else{
		u8ModeCheckResults = MODE_SCTOPTION_DEFAULT;
	}
	
	return MODE_SCTOPTION_LV;//u8ModeCheckResults;
}