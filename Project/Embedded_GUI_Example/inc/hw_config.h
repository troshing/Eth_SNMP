    
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HARDWARE_CONFIG_H
#define __HARDWARE_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif 
   

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"   
#include <stdio.h>
   
  
   
//#define USE_GSM   
//#define USE_GSM_OUTPUT
//#define USE_ZIGBEE_OUTPUT

//#define READER_NUMBER               1234
#define READER_NUMBER               1235   
   
   
/* Flash memory address where mode flag will be located */
#define FileAddress  0x08030000   // picture
#define FileAddress1 0x0802E000   // html
#define FileAddress2 0x0803F800   // param
   
#define IP1Address      0x0803F800
#define IP2Address      0x0803F801
#define IP3Address      0x0803F802
#define IP4Address      0x0803F803
#define PortAddress     0x0803F804
#define RateAddress     0x0803F806
#define SBAddress       0x0803F80A
#define ParityAddress   0x0803F80C
#define TimeoutAddress  0x0803F80E
   
   
#define TCP_DEFAULT_SOCKET  0   
#define TCP_SOCKET          1
#define UDP_SOCKET          2

   
// 1 - 9600
// 2 - 14400
// 3 - 19200
// 4 - 38400
// 5 - 57600
// 6 - 115200
   
   
// 1 - НЕТ чености
// 2 - ODD
// 3 - EVEN
   
 void Param_Reset_init(void);
 void LED_init(void);
   
 void Timer_100us_Init(void);
 void Timer_100ms_Init(void);
   
 void UDP_Process_handler(void);
 void TCP_Process_handler1(void);
   
#ifdef __cplusplus
}
#endif

#endif /* __HARDWARE_CONFIG_H */
