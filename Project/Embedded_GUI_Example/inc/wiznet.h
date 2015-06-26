/******************** (C) COPYRIGHT 2010 STMicroelectronics ********************
* File Name          : hw_config.h
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WIZNET_H
#define __WIZNET_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define WIZNET_SPI_BAUD_RATE      19200
   
#define WIZNET_SPI                           SPI1
#define WIZNET_SPI_CLK                       RCC_APB2Periph_SPI1

#define WIZNET_SPI_SCK_PIN                   GPIO_Pin_5
#define WIZNET_SPI_SCK_GPIO_PORT             GPIOA
#define WIZNET_SPI_SCK_GPIO_CLK              RCC_APB2Periph_GPIOA

#define WIZNET_SPI_MISO_PIN                  GPIO_Pin_6
#define WIZNET_SPI_MISO_GPIO_PORT            GPIOA
#define WIZNET_SPI_MISO_GPIO_CLK             RCC_APB2Periph_GPIOA

#define WIZNET_SPI_MOSI_PIN                  GPIO_Pin_7
#define WIZNET_SPI_MOSI_GPIO_PORT            GPIOA
#define WIZNET_SPI_MOSI_GPIO_CLK             RCC_APB2Periph_GPIOA

#define WIZNET_CS_PIN                        GPIO_Pin_4
#define WIZNET_CS_GPIO_PORT                  GPIOA
#define WIZNET_CS_GPIO_CLK                   RCC_APB2Periph_GPIOA

#define WIZNET_RESET_PIN                     GPIO_Pin_7
#define WIZNET_RESET_GPIO_PORT               GPIOE
#define WIZNET_RESET_GPIO_CLK                RCC_APB2Periph_GPIOE
   
// Wiznet W5100 Op Code
#define WIZNET_WRITE_OPCODE      0xF0
#define WIZNET_READ_OPCODE       0x0F
   
// Wiznet W5100 Register Addresses
#define MR         0x0000      // Mode Register
#define GAR        0x0001      // Gateway Address: 0x0001 to 0x0004
#define SUBR       0x0005      // Subnet mask Address: 0x0005 to 0x0008
#define SAR        0x0009      // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR       0x000F      // Source IP Address: 0x000F to 0x0012
#define RMSR       0x001A      // RX Memory Size Register
#define TMSR       0x001B      // TX Memory Size Register
#define S0_MR	   0x0400      // Socket 0: Mode Register Address
#define S0_CR	   0x0401      // Socket 0: Command Register Address
#define S0_IR	   0x0402      // Socket 0: Interrupt Register Address
#define S0_SR	   0x0403      // Socket 0: Status Register Address
#define S0_PORT    0x0404      // Socket 0: Source Port: 0x0404 to 0x0405
#define S0_DIPR    0x040C      // Socket 0: Destination IP address Register: 0x040C to 0x040E
#define S0_DIPORT  0x0410      // Socket 0: Destination Port Register: 0x0410 to 0x0411
#define SO_TX_FSR  0x0420      // Socket 0: Tx Free Size Register: 0x0420 to 0x0421
#define S0_TX_RD   0x0422      // Socket 0: Tx Read Pointer Register: 0x0422 to 0x0423
#define S0_TX_WR   0x0424      // Socket 0: Tx Write Pointer Register: 0x0424 to 0x0425
#define S0_RX_RSR  0x0426      // Socket 0: Rx Received Size Pointer Register: 0x0425 to 0x0427
#define S0_RX_RD   0x0428      // Socket 0: Rx Read Pointer: 0x0428 to 0x0429
#define TXBUFADDR  0x4000      // W5100 Send Buffer Base Address
#define RXBUFADDR  0x6000      // W5100 Read Buffer Base Address
   
// S0_MR values
#define MR_CLOSE	  0x00    // Unused socket
#define MR_TCP		  0x01    // TCP
#define MR_UDP		  0x02    // UDP
#define MR_IPRAW	  0x03	  // IP LAYER RAW SOCK
#define MR_MACRAW	  0x04	  // MAC LAYER RAW SOCK
#define MR_PPPOE	  0x05	  // PPPoE
#define MR_ND		  0x20	  // No Delayed Ack(TCP) flag
#define MR_MULTI	  0x80	  // support multicating
   
// S0_CR values
#define CR_OPEN          0x01	  // Initialize or open socket
#define CR_LISTEN        0x02	  // Wait connection request in tcp mode(Server mode)
#define CR_CONNECT       0x04	  // Send connection request in tcp mode(Client mode)
#define CR_DISCON        0x08	  // Send closing reqeuset in tcp mode
#define CR_CLOSE         0x10	  // Close socket
#define CR_SEND          0x20	  // Update Tx memory pointer and send data
#define CR_SEND_MAC      0x21	  // Send data with MAC address, so without ARP process
#define CR_SEND_KEEP     0x22	  // Send keep alive message
#define CR_RECV          0x40	  // Update Rx memory buffer pointer and receive data
   
// S0_SR values
#define SOCK_CLOSED      0x00     // Closed
#define SOCK_INIT        0x13	  // Init state
#define SOCK_LISTEN      0x14	  // Listen state
#define SOCK_SYNSENT     0x15	  // Connection state
#define SOCK_SYNRECV     0x16	  // Connection state
#define SOCK_ESTABLISHED 0x17	  // Success to connect
#define SOCK_FIN_WAIT    0x18	  // Closing state
#define SOCK_CLOSING     0x1A	  // Closing state
#define SOCK_TIME_WAIT	 0x1B	  // Closing state
#define SOCK_CLOSE_WAIT  0x1C	  // Closing state
#define SOCK_LAST_ACK    0x1D	  // Closing state
#define SOCK_UDP         0x22	  // UDP socket
#define SOCK_IPRAW       0x32	  // IP raw mode socket
#define SOCK_MACRAW      0x42	  // MAC raw mode socket
#define SOCK_PPPOE       0x5F	  // PPPOE socket
#define TX_BUF_MASK      0x07FF   // Tx 2K Buffer Mask:
#define RX_BUF_MASK      0x07FF   // Rx 2K Buffer Mask:
#define NET_MEMALLOC     0x55     // Use 2K of Tx/Rx Buffer

   
   
#define TCP_PORT         80       // TCP/IP Port (WEB SERVER PORT)
#define UDP_PORT         30001    // UDP Port (USER PORT)


#define BUFSIZE          2048     // размер буфера для принимаемых данных
#define UDP_HEADER_SIZE  8        // размер заголовка пакета UDP


typedef uint8_t		 SOCKET;


// UDP Header
/*typedef struct {
  
  char peer_ip_addr[4];    // IP устройства адресата
  uint16_t peer_port;      // порт адресата
  uint16_t data_size;      // размер данных
  
} UDP_HEADER_STRUCT;*/

// парметры
typedef struct 
{
  
  uint8_t ui8Mode[4];    // режим TCP/UDP
  uint8_t ip_addr[4];    // IP устройства
  uint8_t sub_mask[4];   // маска подсети
  uint8_t gtw_addr[4];   // IP шлюза
  
} PARAM_STRUCT;


  void W5100_Delay_ms(uint16_t delay);
  void W5100_Delay_us(uint16_t delay);
  
  // Initialization of control and data lines
  void W5100_InitLines(void);
  
  // Module initialization
  void W5100_Init(PARAM_STRUCT* pParam);
  
  // Socket initialization
  // returns 1 if success, 0 if failed
  // Socket initialization
  uint8_t W5100_socket(
              SOCKET sock,
              uint8_t eth_protocol,
              uint16_t port
              );
  
  // Read Status
  uint8_t W5100_ReadStatus(SOCKET sock);
  
  // Check if some data recieved
  // returns size of recieved data
  uint16_t W5100_recv_size(SOCKET sock);
  
  // Recieving process
  // returns 1 if success, 0 if failed
  uint8_t W5100_recv(
              SOCKET sock,
              uint8_t *buf,
              uint16_t len,
              uint8_t *ip_addr,
              uint16_t *port
              );
  
  // sending process
  // returns 1 if success, 0 if failed
  uint8_t W5100_send(
              SOCKET sock,
              const uint8_t *buf,
              uint16_t len,
              uint8_t *ip_addr,
              uint16_t *port
              );

  // close socket
  void W5100_close(SOCKET sock);
  
  // disconnect socket (TCP/IP)
  void W5100_disconnect(SOCKET sock);
  
  // waits for request from peer (TCP/IP server mode)
  // returns 1 if any request, else 0 
  uint8_t W5100_listen(SOCKET sock);
  
  // establishes connection (TCP/IP client mode)
  // returns 1 if success, 0 if failed
  uint8_t W5100_connect(
              SOCKET sock,
              uint8_t *ip_addr,
              uint16_t port
              );

  int W5100_strindex(char *s,char *t);
  //void W5100_handler(void);

/* External variables --------------------------------------------------------*/

#endif  /*__HW_CONFIG_H*/
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
