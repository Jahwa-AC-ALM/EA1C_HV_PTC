/***********************************************************************************************************************
* File Name        : UartCtrlModule.c
* Version          : 
* Device(s)        : R7F701695
* Description      : This file implements main function.
***********************************************************************************************************************/
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "r_smc_entry.h"
#include "r_typedefs.h"
#include "UartCtrlModule.h"
#include "Rte.h"



/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
static UartBufferSta_t			st_UartMod_RxRingBuffer = {
								.UartReceivedFlag = 0U,
								.UartBufferStartCursor = 0U,
								.UartBufferEndCursor = 0U
								   };
								   
static UartBufferSta_t			st_UartMod_TxRingBuffer = {
								.UartReceivedFlag = 0U,
								.UartBufferStartCursor = 0U,
								.UartBufferEndCursor = 0U
								   };
							
static UartMsgBuffer_t			UartRxParseBuffer;
static UartMsgBuffer_t			UartTxParseBuffer = {
						.u8MsgHeader = UART_MSG_HEADER,
						.u8MsgTail = UART_MSG_TAIL
					};

//static SERIAL_COMM_HV_MOD		UartMMsg_HV_Tx_LV_Rx;
//static SERIAL_COMM_LV_MOD		UartMMsg_LV_Tx_HV_Rx;
						

static uint8_t			UartRxParserBufferStartFlag = 0U;
static uint8_t			UartRxParserBufferCnt = 0U;
static UART_COM_MODE		UartMComMode = UARTM_TX_OFF_RX_OFF;


static UartErr_t UartM_SendMessage();


/***********************************************************************************************************************
* Function Name: UartRxServiceIsr()
* Description  : This function handles the UartRx interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void UartM_RxServiceIsr()
{
	uint8_t  rx_data_8;
	rx_data_8 = RLN30.LURDR.UINT16;
	
	if(st_UartMod_RxRingBuffer.UartBufferEndCursor == st_UartMod_RxRingBuffer.UartBufferStartCursor)
	{
		st_UartMod_RxRingBuffer.UartBufferEndCursor = 0U;
		st_UartMod_RxRingBuffer.UartBufferStartCursor = 0U;
	}
	
	st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferEndCursor] = rx_data_8;
	st_UartMod_RxRingBuffer.UartBufferEndCursor++;
	
	if(st_UartMod_RxRingBuffer.UartBufferEndCursor == UART_RX_BUFFER_SIZE)
	{
		st_UartMod_RxRingBuffer.UartBufferEndCursor = 0U;
	}
	
	st_UartMod_RxRingBuffer.UartReceivedFlag = 1U;
	
}

/***********************************************************************************************************************
* Function Name: UartTxServiceIsr()
* Description  : This function handles the UartRx interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void UartM_TxServiceIsr()
{
	if(st_UartMod_TxRingBuffer.UartBufferEndCursor - st_UartMod_TxRingBuffer.UartBufferStartCursor > 0U)
	{
		RLN30.LUTDR.UINT16 = st_UartMod_TxRingBuffer.UartBuffer[st_UartMod_TxRingBuffer.UartBufferStartCursor];
		st_UartMod_TxRingBuffer.UartBufferStartCursor++;
	}else{
		st_UartMod_TxRingBuffer.UartBufferEndCursor = 0U;
		st_UartMod_TxRingBuffer.UartBufferStartCursor = 0U;
	}
}
/***********************************************************************************************************************
* Function Name: UartM_SendMessage
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
UartErr_t UartM_MainService_5ms_logic(void)
{
	UartErr_t ret = ERR_URARTM_SUCCESS;
	// 1. Message Buffer Check And Parse;
	if((UartMComMode == UARTM_LV_TX_ON_RX_ON) || (UartMComMode ==UARTM_HV_TX_ON_RX_ON))
	{
		if(st_UartMod_RxRingBuffer.UartReceivedFlag == 1U)
		{
			/* Flag Clear & RingBuffer to UartMsgBuffer_t */
			st_UartMod_RxRingBuffer.UartReceivedFlag = 0U;
			while(st_UartMod_RxRingBuffer.UartBufferEndCursor - st_UartMod_RxRingBuffer.UartBufferStartCursor > 0U)
			{
				if(UartRxParserBufferStartFlag == 0U)
				{
					//Check Header
					if( st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor] == UART_MSG_HEADER)
					{
						UartRxParseBuffer.u8MsgHeader = st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor];
						UartRxParserBufferStartFlag = 1U;
						
					}
				}else if(UartRxParserBufferStartFlag == 1U){
					//Length
					if(st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor] < UART_MSG_OVERFLOW_LENGTH)
					{
						UartRxParseBuffer.u8MsgLength = st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor];
						UartRxParserBufferStartFlag = 2U;
					}else{
						UartRxParserBufferStartFlag = 0U;
					}
					
				}else if(UartRxParserBufferStartFlag == 2U){
					//Msg Type
					if((st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor] == UART_MSG_TYPE_LV2HV)||
					   (st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor] == UART_MSG_TYPE_HV2LV))
					   {
						   UartRxParseBuffer.u8MsgType = st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor];
						   UartRxParserBufferStartFlag = 3U;
					   }else{
						   UartRxParserBufferStartFlag = 0U;
					   }
						   
				}else{
					//Check OverFlag & Tail Check.
					if(st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor] == UART_MSG_TAIL)
					{
						//Received Length Check
						if(UartRxParserBufferCnt == UartRxParseBuffer.u8MsgLength)
						{
							//Parser Success
							if(UartMComMode == UARTM_LV_TX_ON_RX_ON)
							{
								if(UartRxParseBuffer.u8MsgLength ==sizeof(SERIAL_COMM_HV_MOD))
								{
									(void)Rte_Write_UartM_SerialCommMod_LV_RxData((SERIAL_COMM_HV_MOD *)UartRxParseBuffer.au8MsgBuffer);
								}
							}
							
							if(UartMComMode == UARTM_HV_TX_ON_RX_ON){
								if(UartRxParseBuffer.u8MsgLength ==sizeof(SERIAL_COMM_LV_MOD))
								{
									(void)Rte_Write_UartM_SerialCommMod_HV_RxData((SERIAL_COMM_LV_MOD *)UartRxParseBuffer.au8MsgBuffer);
								}
							}
			
							//Call Write
						}else{
							//Fail 
						}
						UartRxParserBufferStartFlag = 0U;
						UartRxParserBufferCnt = 0U;
					}else{
						UartRxParseBuffer.au8MsgBuffer[UartRxParserBufferCnt] = st_UartMod_RxRingBuffer.UartBuffer[st_UartMod_RxRingBuffer.UartBufferStartCursor];
						UartRxParserBufferCnt++;
					}
					
					if(UartRxParserBufferCnt >= UART_MSG_OVERFLOW_LENGTH)
					{
						//OverFlow
						UartRxParserBufferCnt = 0U;
						UartRxParserBufferStartFlag = 0U;
					}
				}
				
				st_UartMod_RxRingBuffer.UartBufferStartCursor++;
			}//while
		}else{
			// Uart Rx Timeout Check
			
		}
		
		// 2.Periodic Uart Tx For 5ms
		if(UartMComMode == UARTM_LV_TX_ON_RX_ON)
		{
			//Read
			UartTxParseBuffer.u8MsgLength = sizeof(SERIAL_COMM_LV_MOD);
			(void)Rte_Read_SerialCommMod_UartM_LV_TxData((SERIAL_COMM_LV_MOD *)UartTxParseBuffer.au8MsgBuffer);
			//Send
			UartM_SendMessage();
		}
						
		if(UartMComMode == UARTM_HV_TX_ON_RX_ON)
		{
			UartTxParseBuffer.u8MsgLength = sizeof(SERIAL_COMM_HV_MOD);
			(void)Rte_Read_SerialCommMod_UartM_HV_TxData((SERIAL_COMM_HV_MOD *)UartTxParseBuffer.au8MsgBuffer);
			UartM_SendMessage();
		}
	}
	
	return (ret);
}

/***********************************************************************************************************************
* Function Name: UartM_SendMessage
* Description  : 
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
UartErr_t UartM_SendMessage()
{
	UartErr_t ret = ERR_URARTM_SUCCESS;
	if(UartTxParseBuffer.u8MsgLength < 1U)
	{
		ret = ERR_URARTM_FAIL;
	}else{
		st_UartMod_TxRingBuffer.UartBuffer[st_UartMod_TxRingBuffer.UartBufferEndCursor++] = UartTxParseBuffer.u8MsgHeader;
		st_UartMod_TxRingBuffer.UartBuffer[st_UartMod_TxRingBuffer.UartBufferEndCursor++] = UartTxParseBuffer.u8MsgLength;
		(void)memcpy(&(*(uint8_t*)&st_UartMod_TxRingBuffer.UartBuffer[st_UartMod_TxRingBuffer.UartBufferEndCursor]), UartTxParseBuffer.au8MsgBuffer, UartTxParseBuffer.u8MsgLength);
		//(void)memcpy(&(*(uint8_t*)&st_UartMod_TxSta.UartTxBuffer[st_UartMod_TxSta.UartTxBufferStartCursor]), tx_msg, msg_length);
		st_UartMod_TxRingBuffer.UartBufferEndCursor += UartTxParseBuffer.u8MsgLength;
		
		if ((RLN30.LST & _UART_TRANSMISSION_OPERATED) == 0U)
		{
			/* Clear ICRLIN30UR0 request and Disable operation */
			INTC2.ICRLIN30UR0.BIT.MKRLIN30UR0 = _INT_PROCESSING_DISABLED;
			INTC2.ICRLIN30UR0.BIT.RFRLIN30UR0 = _INT_REQUEST_NOT_OCCUR;
			RLN30.LUTDR.UINT16 = st_UartMod_TxRingBuffer.UartBuffer[st_UartMod_TxRingBuffer.UartBufferStartCursor];
			st_UartMod_TxRingBuffer.UartBufferStartCursor++;
			/* Clear ICRLIN30UR0 requestt and enable operation */
			INTC2.ICRLIN30UR0.BIT.RFRLIN30UR0 = _INT_REQUEST_NOT_OCCUR;
			INTC2.ICRLIN30UR0.BIT.MKRLIN30UR0 = _INT_PROCESSING_ENABLED;
		}
		else
		{
			st_UartMod_TxRingBuffer.UartBufferStartCursor = 0U;
			st_UartMod_TxRingBuffer.UartBufferEndCursor = 0U;
			ret = ERR_URARTM_BUSY;
		}
		
	}
	return (ret);
}

UartErr_t UartMSetMode(UART_COM_MODE mode)
{
	UartErr_t ret = ERR_URARTM_SUCCESS;
	
	if(mode == UARTM_TX_OFF_RX_OFF)
	{
		UartMComMode = mode;
		
	}else if(mode == UARTM_LV_TX_ON_RX_ON){
		UartMComMode = mode;
	}else if(mode == UARTM_HV_TX_ON_RX_ON){
		UartMComMode = mode;
	}else{
		ret = ERR_URARTM_FAIL;
	}

	return (ret);
}