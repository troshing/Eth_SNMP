/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : wiznet.c
* Author             : MCD Application Team
* Version            : V3.2.1
* Date               : 07/05/2010
* Description        : Hardware Configuration & Setup
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
//#include "platform_config.h"
//#include "stm32_eval.h"

#include "wiznet.h"

#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static PARAM_STRUCT param;


// ************************  DELAY (us)  ************************************ //

// Delay in microseconds
void W5100_Delay_us(uint16_t delay)
{
  for (uint16_t i = 0; i < delay; i++)
  {
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
    asm("nop");
  };
}

// ************************************************************************* //



// ************************  DELAY (ms)  ************************************ //

// Delay in miliseconds
void W5100_Delay_ms(uint16_t delay)
{
  for (uint16_t i = 0; i < delay; i++)
    W5100_Delay_us(1000);
}

// ************************************************************************* //



// ***********  Initialization of control and data lines  ****************** //

// Initialization of control and data lines
void W5100_InitLines(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /*!< SPI_CS_GPIO, SPI_MOSI_GPIO, SPI_MISO_GPIO,
       and SPI_SCK_GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(WIZNET_SPI_SCK_GPIO_CLK | WIZNET_SPI_MISO_GPIO_CLK |
                         WIZNET_SPI_MOSI_GPIO_CLK | WIZNET_CS_GPIO_CLK |
                         WIZNET_RESET_GPIO_CLK, ENABLE);

  /*!< WIZNET_SPI Periph clock enable */
  if (WIZNET_SPI == SPI1) RCC_APB2PeriphClockCmd(WIZNET_SPI_CLK, ENABLE);
  else                    RCC_APB1PeriphClockCmd(WIZNET_SPI_CLK, ENABLE);
  
  /*!< AFIO Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  
  /*!< Configure RESET */
  GPIO_InitStructure.GPIO_Pin = WIZNET_RESET_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(WIZNET_RESET_GPIO_PORT, &GPIO_InitStructure);
  
  // лог '0' - reset вкл.
  GPIO_WriteBit(WIZNET_RESET_GPIO_PORT,WIZNET_RESET_PIN,Bit_RESET);
  W5100_Delay_ms(1);
  
  // лог '1' - reset выкл.
  GPIO_WriteBit(WIZNET_RESET_GPIO_PORT,WIZNET_RESET_PIN,Bit_SET);
  W5100_Delay_ms(1);
  
  /*!< Configure WIZNET_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = WIZNET_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(WIZNET_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure WIZNET_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = WIZNET_SPI_MISO_PIN;
  GPIO_Init(WIZNET_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure WIZNET_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = WIZNET_SPI_MOSI_PIN;
  GPIO_Init(WIZNET_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure WIZNET_SPI_CS_PIN pin: WIZNET CS pin */
  GPIO_InitStructure.GPIO_Pin = WIZNET_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(WIZNET_CS_GPIO_PORT, &GPIO_InitStructure);
  
  // лог '1' - CS выкл.
  GPIO_WriteBit(WIZNET_CS_GPIO_PORT,WIZNET_CS_PIN,Bit_SET);

  /*!< WIZNET_SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(WIZNET_SPI, &SPI_InitStructure);
  
  /* Enable SPI_MASTER NSS output for master mode */
  SPI_SSOutputCmd(WIZNET_SPI, ENABLE);
  
  SPI_Cmd(WIZNET_SPI, ENABLE); /*!< WIZNET_SPI enable */
}
  
// *************************  SPI Write  *********************************** //

// SPI Write
void SPI_Write(uint16_t addr, uint8_t data)
{
  // лог '0' - CS вкл.
  GPIO_WriteBit(WIZNET_CS_GPIO_PORT,WIZNET_CS_PIN ,Bit_RESET);
  
  W5100_Delay_us(2);

  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, WIZNET_WRITE_OPCODE);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
  // Start Wiznet W5100 Address High Bytes transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, ((addr & 0xFF00) >> 8));
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  // Start Wiznet W5100 Address Low Bytes transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, (addr & 0x00FF));
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  // Start Data transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, data);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  W5100_Delay_us(2);

  
  // лог '1' - CS выкл.
  GPIO_WriteBit(WIZNET_CS_GPIO_PORT,WIZNET_CS_PIN ,Bit_SET);
}


// **************************  SPI Read  *********************************** //

// SPI Read
char SPI_Read(uint16_t addr)
{
  // лог '0' - CS вкл.
  GPIO_WriteBit(WIZNET_CS_GPIO_PORT,WIZNET_CS_PIN ,Bit_RESET);
  
  //W5100_Delay_ms(1);
  

  SPI_I2S_ReceiveData(WIZNET_SPI);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, WIZNET_READ_OPCODE);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_RXNE) == RESET);
  
  SPI_I2S_ReceiveData(WIZNET_SPI);

  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);

  // Start Wiznet W5100 Address High Bytes transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, ((addr & 0xFF00) >> 8));
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_RXNE) == RESET);
  
  SPI_I2S_ReceiveData(WIZNET_SPI);

  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  // Start Wiznet W5100 Address Low Bytes transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, (addr & 0x00FF));
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  SPI_I2S_ReceiveData(WIZNET_SPI);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_TXE) == RESET);
  
  // Start Data transmission
  /* Send WIZNET_SPI data */
  SPI_I2S_SendData(WIZNET_SPI, 0x00);
  
  /* Wait for WIZNET_SPI Tx buffer empty */
  while (SPI_I2S_GetFlagStatus(WIZNET_SPI, SPI_I2S_FLAG_RXNE) == RESET);
  
  char reg = SPI_I2S_ReceiveData(WIZNET_SPI);
  
  //W5100_Delay_ms(1);
  
  // лог '1' - CS выкл.
  GPIO_WriteBit(WIZNET_CS_GPIO_PORT,WIZNET_CS_PIN ,Bit_SET);
  
  return reg;
}

// ************************************************************************* //
 

// ******************  Initialization of W5100 module  ********************* //

// Initialization
void W5100_Init(PARAM_STRUCT* pParam)
{
  // Setting the Wiznet W5100 Mode Register: 0x0000
  // RESET
  SPI_Write(MR,0x80);            // MR = 0b10000000;
  W5100_Delay_ms(1);
  
  param.ui8Mode[0] = pParam->ui8Mode[0];
  param.ui8Mode[1] = pParam->ui8Mode[1];
  param.ui8Mode[2] = pParam->ui8Mode[2];
  param.ui8Mode[3] = pParam->ui8Mode[3];
  
  param.ip_addr[0] = pParam->ip_addr[0];
  param.ip_addr[1] = pParam->ip_addr[1];
  param.ip_addr[2] = pParam->ip_addr[2];
  param.ip_addr[3] = pParam->ip_addr[3];
  
  param.sub_mask[0] = pParam->sub_mask[0];
  param.sub_mask[1] = pParam->sub_mask[1];
  param.sub_mask[2] = pParam->sub_mask[2];
  param.sub_mask[3] = pParam->sub_mask[3];
  
  param.gtw_addr[0] = pParam->gtw_addr[0];
  param.gtw_addr[1] = pParam->gtw_addr[1];
  param.gtw_addr[2] = pParam->gtw_addr[2];
  param.gtw_addr[3] = pParam->gtw_addr[3];
  

  // Setting the Wiznet W5100 Gateway Address (GAR): 0x0001 to 0x0004
  SPI_Write(GAR + 0,param.gtw_addr[0]);
  SPI_Write(GAR + 1,param.gtw_addr[1]);
  SPI_Write(GAR + 2,param.gtw_addr[2]);
  SPI_Write(GAR + 3,param.gtw_addr[3]);
  W5100_Delay_ms(1);
  
  // Setting the Wiznet W5100 Sub Mask Address (SUBR): 0x0005 to 0x0008
  SPI_Write(SUBR + 0,param.sub_mask[0]);
  SPI_Write(SUBR + 1,param.sub_mask[1]);
  SPI_Write(SUBR + 2,param.sub_mask[2]);
  SPI_Write(SUBR + 3,param.sub_mask[3]);
  W5100_Delay_ms(1);
  
  // Setting the Wiznet W5100 IP Address (SIPR): 0x000F to 0x0012
  SPI_Write(SIPR + 0,param.ip_addr[0]);
  SPI_Write(SIPR + 1,param.ip_addr[1]);
  SPI_Write(SIPR + 2,param.ip_addr[2]);
  SPI_Write(SIPR + 3,param.ip_addr[3]);    
  W5100_Delay_ms(1);
  
  // Setting the Wiznet W5100 RX and TX Memory Size (2KB),
  SPI_Write(RMSR,NET_MEMALLOC);
  SPI_Write(TMSR,NET_MEMALLOC);

}

// ************************************************************************* //





// ********************  INITIALIZATION OF SOCKET ************************** //

// Socket initialization
uint8_t W5100_socket(
              SOCKET sock,
              uint8_t eth_protocol,
              uint16_t port
              )
{
  uint8_t retval = 0;

  // Make sure we close the socket first
  if (SPI_Read(S0_SR + sock*256) == SOCK_CLOSED)
  {
    W5100_close(sock);
  };
    
  // Assigned Socket 0 Mode Register
  SPI_Write(S0_MR + sock*256,eth_protocol);

  // Now open the Socket 0
  SPI_Write(S0_PORT + sock*256,((port & 0xFF00) >> 8 ));
  SPI_Write(S0_PORT + 1 + sock*256,(port & 0x00FF));
    
  // Open Socket
  SPI_Write(S0_CR + sock*256,CR_OPEN);
    
  // Wait for Opening Process
  while(SPI_Read(S0_CR + sock*256));
    
  // Check for Init Status
  uint8_t status = SPI_Read(S0_SR + sock*256);
    
  if ( (eth_protocol == MR_TCP && status == SOCK_INIT) ||
       (eth_protocol == MR_UDP && status == SOCK_UDP) )
    retval = 1;
  else
    W5100_close(sock);

  return retval;
}

// **************************  READ STATUS  ******************************** //

// Read Status
uint8_t W5100_ReadStatus(SOCKET sock)
{
  return SPI_Read(S0_SR + sock*256);
}


// ***********************  RECIEVING DATA  ******************************** //

// Check if some data recieved
uint16_t W5100_recv_size(SOCKET sock)
{
  return ((SPI_Read(S0_RX_RSR + sock*256) & 0x00FF) << 8 ) + SPI_Read(S0_RX_RSR + 1 + sock*256);
}



// Recieving process
uint8_t W5100_recv(
              SOCKET sock,
              uint8_t *buf,
              uint16_t len,
              uint8_t *ip_addr,
              uint16_t *port
              )
{
  uint16_t ptr;
  uint16_t get_offset;
  uint16_t get_start_addr;
  uint16_t get_size;
  
  uint8_t header[8];
  uint16_t header_size = 8;
  
  uint16_t os = sock*2048;
  uint16_t os1 = sock*256;

  if (len <= 0) return 0;   

  // If the request size > MAX_BUF, just truncate it
  if (len > BUFSIZE) len = BUFSIZE - 2;
  
  get_size = len;
    
  // Read the Rx Read Pointer
  ptr = SPI_Read(S0_RX_RD + os1);
  get_offset = (((ptr & 0x00FF) << 8 ) + SPI_Read(S0_RX_RD + 1 + os1));
  
  // если UDP, то читаем заголовок
  if (param.ui8Mode[sock] == MR_UDP)
  {
    // if overflow socket Rx memory
    if ( (get_offset & RX_BUF_MASK) + header_size > RX_BUF_MASK + 1 )
    {
      uint16_t upper_size = ( RX_BUF_MASK + 1 ) - (get_offset & RX_BUF_MASK);
      
      // copy upper size
      for (uint16_t i = 0; i < upper_size; i++)
      {
        get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
        header[i] = SPI_Read(get_start_addr);
      
        get_offset++;
      };
      
      // copy left size
      get_offset = 0;
      for (uint16_t i = upper_size; i < header_size; i++)
      {
        get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
        header[i] = SPI_Read(get_start_addr);
      
        get_offset++;
      };
      
    }
    else
    {
      // copy header
      for (uint16_t i = 0; i < header_size; i++)
      {
        get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
        header[i] = SPI_Read(get_start_addr);
      
        get_offset++;
      };
    };
    
    // remote IP address
    ip_addr[0] = header[0];
    ip_addr[1] = header[1];
    ip_addr[2] = header[2];
    ip_addr[3] = header[3];
    
    // remote port
    *port = (header[4]<<8);
    *port += header[5];
    
    get_size = (header[6]<<8);
    get_size += header[7];
    
  };


  // copy data
  
  // if overflow socket Rx memory
  if ( (get_offset & RX_BUF_MASK) + get_size > RX_BUF_MASK + 1 )
  {
    uint16_t upper_size = ( RX_BUF_MASK + 1 ) - (get_offset & RX_BUF_MASK);
      
    // copy upper size
    for (uint16_t i = 0; i < upper_size; i++)
    {
      get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
      *buf++ = SPI_Read(get_start_addr);
      
      get_offset++;
    };
      
    // copy left size
    get_offset = 0;
    for (uint16_t i = upper_size; i < get_size; i++)
    {
      get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
      *buf++ = SPI_Read(get_start_addr);
      
      get_offset++;
    };
      
  }
  else
  {
    // copy data
    for (uint16_t i = 0; i < get_size; i++)
    {
      get_start_addr = RXBUFADDR + os + (get_offset & RX_BUF_MASK);
      *buf++ = SPI_Read(get_start_addr);
      
      get_offset++;
    };
  };
  
  *buf = '\0';        // String terminated character

  // Read the Rx Read Pointer
  ptr = SPI_Read(S0_RX_RD + os1);
  get_offset = (((ptr & 0x00FF) << 8 ) + SPI_Read(S0_RX_RD + 1 + os1));
  
  get_offset += header_size + get_size;

  // Increase the S0_RX_RD value, so it point to the next receive
  SPI_Write(S0_RX_RD + os1,(get_offset & 0xFF00) >> 8 );
  SPI_Write(S0_RX_RD + 1 + os1,(get_offset & 0x00FF));	

  // Now Send the RECV command
  SPI_Write(S0_CR + os1,CR_RECV);
  
  W5100_Delay_us(5);    // Wait for Receive Process

  return 1;
}

// ************************************************************************* //



// *************************  SENDING DATA  ******************************** //

// sending process
uint8_t W5100_send(
              SOCKET sock,
              const uint8_t *buf,
              uint16_t len,
              uint8_t *ip_addr,
              uint16_t *port
              )
{
  
  uint16_t ptr;
  uint16_t get_offset;
  uint16_t get_start_addr;
  uint16_t send_size;
  uint16_t get_free_size;
  
  uint16_t timeout;   
  
  uint16_t os = sock*2048;
  uint16_t os1 = sock*256;

  if (len <= 0) return 0;
  
  send_size = len;

  // Make sure the TX Free Size Register is available
  get_free_size = SPI_Read(SO_TX_FSR + os1);
  get_free_size = (((get_free_size & 0x00FF) << 8 ) + SPI_Read(SO_TX_FSR + 1 + os1));

  timeout = 0;
  while (get_free_size < send_size)
  {
    W5100_Delay_ms(1);
    get_free_size = SPI_Read(SO_TX_FSR + os1);
    get_free_size = (((get_free_size & 0x00FF) << 8 ) + SPI_Read(SO_TX_FSR + 1 + os1));
     
    // Timeout for approx 1000 ms
    if (timeout++ > 10000)
    {
      if (param.ui8Mode[sock] == MR_TCP)
      {
        // Disconnect the connection
        W5100_disconnect(sock);
      }
      else
      {
        // Close socket
        W5100_close(sock);
      };
      
      return 0;
    };
  };	
  
  if (param.ui8Mode[sock] == MR_UDP)
  {
    // set remote IP
    SPI_Write(S0_DIPR + os1 + 0,ip_addr[0]);
    SPI_Write(S0_DIPR + os1 + 1,ip_addr[1]);
    SPI_Write(S0_DIPR + os1 + 2,ip_addr[2]);
    SPI_Write(S0_DIPR + os1 + 3,ip_addr[3]);
  
    // set remote port
    SPI_Write(S0_DIPORT + os1,(uint8_t)((*port & 0xff00) >> 8));
    SPI_Write(S0_DIPORT + 1 + os1,(uint8_t)(*port & 0x00ff));
  };
  

  // Read the Tx Write Pointer
  ptr = SPI_Read(S0_TX_WR + os1);
  get_offset = (((ptr & 0x00FF) << 8 ) + SPI_Read(S0_TX_WR + 1 + os1));
  
  // if overflow socket Tx memory
  if ( (get_offset & TX_BUF_MASK) + send_size > TX_BUF_MASK + 1 )
  {
    uint16_t upper_size = ( TX_BUF_MASK + 1 ) - (get_offset & TX_BUF_MASK);
      
    // copy upper size
    for (uint16_t i = 0; i < upper_size; i++)
    {
      get_start_addr = TXBUFADDR + os + (get_offset & TX_BUF_MASK);
      
      // Copy the application data to the W5100 Tx Buffer
      SPI_Write(get_start_addr,*buf++);
      
      get_offset++;
    };
      
    // copy left size
    get_offset = 0;
    for (uint16_t i = upper_size; i < send_size; i++)
    {
      get_start_addr = TXBUFADDR + os + (get_offset & TX_BUF_MASK);
      
      // Copy the application data to the W5100 Tx Buffer
      SPI_Write(get_start_addr,*buf++);
      
      get_offset++;
    };
      
  }
  else
  {
    // copy data
    for (uint16_t i = 0; i < send_size; i++)
    {
      get_start_addr = TXBUFADDR + os + (get_offset & TX_BUF_MASK);
      
      // Copy the application data to the W5100 Tx Buffer
      SPI_Write(get_start_addr,*buf++);
      
      get_offset++;
    };
  };

  
  // Read the Tx Write Pointer
  ptr = SPI_Read(S0_TX_WR + os1);
  get_offset = (((ptr & 0x00FF) << 8 ) + SPI_Read(S0_TX_WR + 1 + os1));
  
  get_offset += send_size;
  
  // Increase the S0_TX_WR value, so it point to the next transmit
  SPI_Write(S0_TX_WR + os1,(get_offset & 0xFF00) >> 8 );
  SPI_Write(S0_TX_WR + 1 + os1,(get_offset & 0x00FF));	

  // Now Send the SEND command
  SPI_Write(S0_CR + os1,CR_SEND);

  // Wait for Sending Process
  while(SPI_Read(S0_CR + os1));	

  return 1;
}


// ************************************************************************* //




// ***********************  Closing socket  ******************************** //

// Closing socket
void W5100_close(SOCKET sock)
{
  uint16_t os1 = sock*256;

  // Send Close Command
  SPI_Write(S0_CR + os1,CR_CLOSE);
   
  // Waiting until the S0_CR is clear
  while(SPI_Read(S0_CR + os1));
}

// ************************************************************************* //




// ***************************  Disconnect  ******************************** //

// Disconnect
void W5100_disconnect(SOCKET sock)
{
  uint16_t os1 = sock*256;
   
  // Send Disconnect Command
  SPI_Write(S0_CR + os1,CR_DISCON);
   
  // Wait for Disconecting Process
  while(SPI_Read(S0_CR + os1));
}

// ************************************************************************* //



// ****************************  Listening  ******************************** //

// Listening
uint8_t W5100_listen(SOCKET sock)
{
  uint8_t retval = 0;
  uint16_t os1 = sock*256;
   
  if (SPI_Read(S0_SR + os1) == SOCK_INIT)
  {
    // Send the LISTEN Command
    SPI_Write(S0_CR + os1,CR_LISTEN);

    // Wait for Listening Process
    while(SPI_Read(S0_CR + os1));
     
    // Check for Listen Status
    if (SPI_Read(S0_SR + os1) == SOCK_LISTEN)
      retval = 1;
    else
      W5100_close(sock);
  };
   
  return retval;
}

// ************************************************************************* //



// ******************************  Connect  ******************************** //

// Connect
uint8_t W5100_connect(
              SOCKET sock,
              uint8_t *ip_addr,
              uint16_t port
              )
{
  uint8_t sockstat;
  
  uint16_t os1 = sock*256;
  
  // set remote IP
  SPI_Write(S0_DIPR + os1 + 0,ip_addr[0]);
  SPI_Write(S0_DIPR + os1 + 1,ip_addr[1]);
  SPI_Write(S0_DIPR + os1 + 2,ip_addr[2]);
  SPI_Write(S0_DIPR + os1 + 3,ip_addr[3]);
  
  // set remote port
  SPI_Write(S0_DIPORT + os1,(uint8_t)((port & 0xff00) >> 8));
  SPI_Write(S0_DIPORT + 1 + os1,(uint8_t)(port & 0x00ff));
   
  // Send the LISTEN Command
  SPI_Write(S0_CR + os1,CR_CONNECT);

  // Wait for Listening Process
  while(SPI_Read(S0_CR + os1));
     
  // Wait for CONNECT or CLOSED Status
  while (1)
  {
    sockstat = SPI_Read(S0_SR + os1);
    
    if (sockstat == SOCK_ESTABLISHED)
      return 1;
    else
      if (sockstat == SOCK_CLOSED)
        return 0;
  };
}


int W5100_strindex(char *s,char *t)
{
  uint16_t i,n;

  n = strlen(t);
  for(i=0;*(s+i); i++) {
    if (strncmp(s+i,t,n) == 0)
      return i;
  }
  return -1;
}

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
