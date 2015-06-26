
#include "modbus.h"


static uint8_t m_ui8RxBuf[RXBUFSIZE];
static uint8_t m_ui8TxBuf[TXBUFSIZE];

static uint16_t m_ui16TxLength;  
static uint16_t m_ui16TxBufCnt;

static uint8_t m_ui8TxTimer;
static uint8_t m_ui16RxTimer;

static uint8_t m_ui8TxReady = 1;
static uint8_t m_ui8RxDataReady;

static uint16_t m_ui16RxBufCnt;
static UART_STRUCT m_uart;


// ***********  Initialization of control and data lines  ****************** //

// Initialization of control and data lines
void RS485_InitLines(UART_STRUCT* pUartStruct)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(MODBUS_UART_TX_GPIO_CLK | MODBUS_UART_RX_GPIO_CLK |
                         MODBUS_485_TR_GPIO_CLK, ENABLE);
  
  /*!< MODBUS_UART Periph clock enable */
  if (MODBUS_UART == USART1) RCC_APB2PeriphClockCmd(MODBUS_UART_CLK, ENABLE);
  else                       RCC_APB1PeriphClockCmd(MODBUS_UART_CLK, ENABLE);
  
  /*!< AFIO Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Configure USARTy Rx as input floating */
  GPIO_InitStructure.GPIO_Pin = MODBUS_UART_RX_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(MODBUS_UART_RX_GPIO_PORT, &GPIO_InitStructure);
  
  /* Configure USARTy Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = MODBUS_UART_TX_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(MODBUS_UART_TX_GPIO_PORT, &GPIO_InitStructure);
  
  
  /*!< Configure TR485 */
  GPIO_InitStructure.GPIO_Pin = MODBUS_485_TR_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MODBUS_485_TR_GPIO_PORT, &GPIO_InitStructure);
  
  // лог '0' - reciever вкл.
  GPIO_WriteBit(MODBUS_485_TR_GPIO_PORT,MODBUS_485_TR_PIN,Bit_RESET);
  
  
  
  // struct
  m_uart.ui32Rate     = pUartStruct->ui32Rate;
  m_uart.ui16StopBits = pUartStruct->ui16StopBits;
  m_uart.ui16Parity   = pUartStruct->ui16Parity;
  m_uart.ui16Timeout  = pUartStruct->ui16Timeout;

  
  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = MODBUS_UART_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = m_uart.ui32Rate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = m_uart.ui16StopBits;
  USART_InitStructure.USART_Parity = m_uart.ui16Parity;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure USARTy */
  USART_Init(MODBUS_UART, &USART_InitStructure);
  
  /* Enable USARTy Receive interrups */
  USART_ITConfig(MODBUS_UART, USART_IT_RXNE, ENABLE);
  
  USART_ITConfig(MODBUS_UART, USART_IT_TXE, DISABLE);
  USART_ITConfig(MODBUS_UART, USART_IT_TC, DISABLE);

  /* Enable the USARTy */
  USART_Cmd(MODBUS_UART, ENABLE);
  
  unsigned int u = 0xffff;
  while (--u);
}
  

// *************************  Modbus Send  ********************************* //

// Modbus Send
void Modbus_SendData(void)
{
  if (m_ui16TxLength == 0) return;  
  m_ui16TxBufCnt = 0;
  
  m_ui8TxReady = 0;
  
  // лог '1' - transmitter вкл.
  GPIO_WriteBit(MODBUS_485_TR_GPIO_PORT,MODBUS_485_TR_PIN,Bit_SET);
  
  if (USART_GetITStatus(MODBUS_UART, USART_IT_TXE) == RESET)
  { 
    USART_SendData(MODBUS_UART,m_ui8TxBuf[m_ui16TxBufCnt++]);
    USART_ITConfig(MODBUS_UART, USART_IT_TXE, ENABLE);
    //USART_SendData(MODBUS_UART,m_ui8TxBuf[m_ui16TxBufCnt++]);
  }
  else
  {
    USART_ITConfig(MODBUS_UART, USART_IT_TXE, ENABLE);
  };

}

// Get Tx buffer pointer
uint8_t* Modbus_GetTxBuffer(void)
{
  return m_ui8TxBuf;
}

// Write to Tx buffer
void Modbus_WriteToTxBuf(uint8_t byte)
{
  m_ui8TxBuf[m_ui16TxLength++] = byte;
}

// Tx buffer init
void Modbus_TxBufInit(void)
{
  m_ui16TxLength   = 0;
  m_ui16TxBufCnt   = 0;
}

// Set Tx packet length
void Modbus_SetTxPacketlength(uint16_t len)
{
  m_ui16TxLength = len;
}

// Tx timeout timer decrement
void Modbus_TxTimerDec(void)
{
  if (m_ui8TxTimer)
  {
    if (--m_ui8TxTimer == 0) m_ui8TxReady = 1;
  };
}

// Check if Tx ready
uint8_t Modbus_IsTxReady(void)
{
  return m_ui8TxReady;
}

// ************************************************************************* //



// **************************  Modbus Read  ******************************** //

// Check Rx data
uint8_t Modbus_IsRxDataReady(void)
{
  return m_ui8RxDataReady;
}

// Rx buffer init
void Modbus_RxBufInit(void)
{
  m_ui8RxDataReady = 0;
  m_ui16RxBufCnt   = 0;
}

// Check Recived data size
uint16_t Modbus_GetRxDataSize(void)
{
  return m_ui16RxBufCnt;
}

// Get Rx buffer pointer
uint8_t* Modbus_GetRxBuffer(void)
{
  return m_ui8RxBuf;
}

// Rx timeout timer decrement
void Modbus_RxTimerDec(void)
{
  if (m_ui16RxTimer)
  {
    if (--m_ui16RxTimer == 0) m_ui8RxDataReady = 1;
  };
}


// ************************************************************************* //

// *****************************  IRQ Handler  ***************************** //


// interrupt handler
void Modbus_InterruptHandler(void)
{
  if (USART_GetITStatus(MODBUS_UART, USART_IT_RXNE) != RESET)
  {
    if (m_ui16RxTimer == 0)
    {
      m_ui8RxDataReady = 0;
      m_ui16RxBufCnt   = 0;
    }
    
    /* Read one byte from the receive data register */
    m_ui8RxBuf[m_ui16RxBufCnt++] = USART_ReceiveData(MODBUS_UART);
    if (m_ui16RxBufCnt == RXBUFSIZE) m_ui16RxBufCnt = 0;
    
    m_ui16RxTimer = m_uart.ui16Timeout*10;

  }

  if (USART_GetITStatus(MODBUS_UART, USART_IT_TXE) != RESET)
  {   
    if (m_ui16TxBufCnt < m_ui16TxLength)
    {
      /* Write one byte to the transmit data register */
      USART_SendData(MODBUS_UART, m_ui8TxBuf[m_ui16TxBufCnt++]);

      if (m_ui16TxBufCnt == m_ui16TxLength)
      {
        /* Disable the USARTy Transmit interrupt */
        USART_ITConfig(MODBUS_UART, USART_IT_TXE, DISABLE);
        
        USART_ITConfig(MODBUS_UART, USART_IT_TC, ENABLE);
      } 
    }
  }
  
  if (USART_GetITStatus(MODBUS_UART, USART_IT_TC) != RESET)
  {   
    
    // лог '0' - reciever вкл.
    GPIO_WriteBit(MODBUS_485_TR_GPIO_PORT,MODBUS_485_TR_PIN,Bit_RESET);
    
    USART_ITConfig(MODBUS_UART, USART_IT_TC, DISABLE);
    
    //m_ui8TxTimer = MODBUS_TIMEOUT;
    
    m_ui16TxLength   = 0;
    m_ui16TxBufCnt   = 0;
  }

}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
