
#ifndef __MODBUS_H
#define __MODBUS_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"


#define MODBUS_UART_BAUD_RATE                38400
#define MODBUS_TIMEOUT                       500

#define MODBUS_UART_STOPBITS                 USART_StopBits_2
#define MODBUS_UART_PARITY                   USART_Parity_No

   
#define MODBUS_UART                          UART4
#define MODBUS_UART_CLK                      RCC_APB1Periph_UART4

#define MODBUS_UART_TX_PIN                   GPIO_Pin_10
#define MODBUS_UART_TX_GPIO_PORT             GPIOC
#define MODBUS_UART_TX_GPIO_CLK              RCC_APB2Periph_GPIOC

#define MODBUS_UART_RX_PIN                   GPIO_Pin_11
#define MODBUS_UART_RX_GPIO_PORT             GPIOC
#define MODBUS_UART_RX_GPIO_CLK              RCC_APB2Periph_GPIOC

#define MODBUS_485_TR_PIN                    GPIO_Pin_0
#define MODBUS_485_TR_GPIO_PORT              GPIOD
#define MODBUS_485_TR_GPIO_CLK               RCC_APB2Periph_GPIOD

#define MODBUS_UART_IRQn                     UART4_IRQn



#define RXBUFSIZE          2048     // размер буфера для принимаемых данных
#define TXBUFSIZE          2048     // размер буфера для передаваемых данных


  
typedef struct {
  
  uint32_t ui32Rate;
  uint16_t ui16StopBits;
  uint16_t ui16Parity;
  uint16_t ui16Timeout;
  
} UART_STRUCT;


  
  // Initialization of control and data lines
  void RS485_InitLines(UART_STRUCT* pUartStruct);
  
  // Modbus Send
  void Modbus_SendData(void);
  
  // Get Tx buffer pointer
  uint8_t* Modbus_GetTxBuffer(void);
  
  // Write to Tx buffer
  void Modbus_WriteToTxBuf(uint8_t byte);
  
  // Tx buffer init
  void Modbus_TxBufInit(void);
  
  // Set Tx packet length
  void Modbus_SetTxPacketlength(uint16_t len);
  
  // Tx timeout timer decrement
  void Modbus_TxTimerDec(void);
  
  // Check if Tx ready
  uint8_t Modbus_IsTxReady(void);
  
  
  // Check Rx data
  uint8_t Modbus_IsRxDataReady(void);
  
  // Rx buffer init
  void Modbus_RxBufInit(void);
  
  // Check Recived data size
  uint16_t Modbus_GetRxDataSize(void);
  
  // Get Rx buffer pointer
  uint8_t* Modbus_GetRxBuffer(void);
  
  // Rx timeout timer decrement
  void Modbus_RxTimerDec(void);
  
  
  // interrupt handler
  void Modbus_InterruptHandler(void);


#endif  /*__HW_CONFIG_H*/
