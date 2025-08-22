
#ifndef UartCtrlModule_H
#define UartCtrlModule_H
/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_device.h"
#include "r_typedefs.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define UART_RX_BUFFER_SIZE			256U
#define UART_TX_BUFFER_SIZE			256U

#define UART_MSG_HEADER				0xAA
#define UART_MSG_TAIL				0x55
#define	UART_MSG_TYPE_LV2HV			0xEA
#define UART_MSG_TYPE_HV2LV			0xAE
#define UART_MSG_RX_TIMEOUT			20U		//20ms
#define UART_MSG_OVERFLOW_LENGTH		64U
/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum {
	ERR_URARTM_SUCCESS = 0U, 
	ERR_URARTM_FAIL,
	ERR_URARTM_BUSY,
	ERR_URARTM_BUFFEROVF
}UartErr_t;

typedef enum {
	UARTM_TX_OFF_RX_OFF = 0U,
	UARTM_LV_TX_ON_RX_ON,
	UARTM_HV_TX_ON_RX_ON
}UART_COM_MODE;

typedef struct
{
	uint8_t			u8MsgHeader;
	uint8_t			u8MsgLength;
	uint8_t			u8MsgType;
	uint8_t			au8MsgBuffer[UART_MSG_OVERFLOW_LENGTH];
	uint8_t			u8MsgTail;
}UartMsgBuffer_t;


typedef struct
{
	uint8_t				UartReceivedFlag;
	uint8_t				UartBuffer[UART_RX_BUFFER_SIZE];
	uint8_t				UartBufferStartCursor;
	uint8_t				UartBufferEndCursor;
}UartBufferSta_t;




/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Isr Service Routine */
void UartM_RxServiceIsr();
void UartM_TxServiceIsr();

/*  */
UartErr_t UartM_MainService_5ms_logic(void);
UartErr_t UartMSetMode(UART_COM_MODE mode);




#endif