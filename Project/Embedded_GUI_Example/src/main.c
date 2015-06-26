#include "main.h"

#include <stdio.h>
#include <string.h>

#include "hw_config.h"
#include "wiznet.h"
#include "modbus.h"


#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)

#endif /* __GNUC__ */


extern uint8_t TCP_flag;
extern uint16_t TCP_wait_timer;
extern uint8_t ip_addr[4];
extern uint16_t port;
extern uint32_t ip_addr32;

extern uint32_t rate;
extern uint16_t stop_bits;
extern uint16_t parity;
extern uint16_t timeout;

uint8_t UDP_Init_flag = 0;
uint8_t ui8ParSave = 0;

uint8_t ui8ResetFlag = 0;
uint8_t uiResetTimer = 0;


int main(void)
{
  RCC_ClocksTypeDef RCC_Clocks;
  UART_STRUCT US;

  /* Setup the microcontroller system. Initialize the Embedded Flash Interface,
  initialize the PLL and update the SystemFrequency variable. */
  SystemInit();
   
  // ------------------------------------------------------------------------
  /* GPIO clock enable */
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

  /* CAN1 Periph clock enable */
 // RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5 | RCC_APB1Periph_USB, ENABLE);
  
  // ------------------------------------------------------------------------
  

  /* Setup SysTick Timer for 10 msec interrupts  */
  RCC_GetClocksFreq(&RCC_Clocks);
  if (SysTick_Config(RCC_Clocks.SYSCLK_Frequency / 100))
  {
    /* Capture error */
    while (1);
  }


  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0000);
  
  LED_init();
    
  W5100_Delay_ms(1000);
  
  /* ------- ПАРАМЕТРЫ ------------------------------ */
  
  // IP
  ip_addr[0] = *((__IO uint8_t*)IP1Address);
  ip_addr[1] = *((__IO uint8_t*)IP2Address);
  ip_addr[2] = *((__IO uint8_t*)IP3Address);
  ip_addr[3] = *((__IO uint8_t*)IP4Address);
    
  // IP адрес не определен
  if ( (ip_addr[0] == 0xFF &&
        ip_addr[1] == 0xFF &&
        ip_addr[2] == 0xFF &&
        ip_addr[3] == 0xFF) ||
        (ip_addr[0] == 0x00 &&
        ip_addr[1] == 0x00 &&
        ip_addr[2] == 0x00 &&
        ip_addr[3] == 0x00)
      )
  {
    ip_addr[0] = 192;
    ip_addr[1] = 168;
    ip_addr[2] = 1;
    ip_addr[3] = 10;
    
    ip_addr32 = ip_addr[0] + (ip_addr[1]<<8) + (ip_addr[2]<<16) + (ip_addr[3]<<24);
    
    
    ui8ParSave = 1;
  }
  
  // ПОРТ
  port = *((__IO uint16_t*)PortAddress);
  
  // порт не определен
  if (port == 0xFFFF)
  {
    port = 30001;
    ui8ParSave = 1;
  }
  
  // СКОРОСТЬ
  rate = *((__IO uint32_t*)RateAddress);
  
  // скорость не определена
  if (rate != 9600  &&
      rate != 14400 &&
      rate != 19200 &&
      rate != 38400 &&
      rate != 57600 &&
      rate != 115200)
  {
    rate = 38400;
    ui8ParSave = 1;
  }
  
  // СТОП БИТЫ
  stop_bits = *((__IO uint16_t*)SBAddress);
  
  // стоп биты не определены
  if (stop_bits != USART_StopBits_1 &&
      stop_bits != USART_StopBits_2)
  {
    stop_bits = USART_StopBits_2;
    ui8ParSave = 1;
  }
  
  // ЧЕТНОСТЬ
  parity = *((__IO uint16_t*)ParityAddress);
  
  // четность не определена
  if (parity != USART_Parity_No &&
      parity != USART_Parity_Even &&
      parity != USART_Parity_Odd)
  {
    parity = USART_Parity_No;
    ui8ParSave = 1;
  }
  
  // таймаут
  timeout = *((__IO uint16_t*)TimeoutAddress);
  
  // таймаут не определен
  if (timeout > 1000)
  {
    timeout = 50;
    ui8ParSave = 1;
  }
  
  if (ui8ParSave)
  {
    ui8ParSave = 0;
    
    // Unlock the internal flash
    FLASH_Unlock();
      
    __disable_interrupt();
      
    // стираем страницу
    FLASH_ErasePage(IP1Address);
        
    FLASH_ProgramWord(IP1Address, ip_addr32);   
    FLASH_ProgramHalfWord(PortAddress, port);
    FLASH_ProgramWord(RateAddress, rate);
    FLASH_ProgramHalfWord(SBAddress, stop_bits);
    FLASH_ProgramHalfWord(ParityAddress, parity);
    FLASH_ProgramHalfWord(TimeoutAddress, timeout);
      
    __enable_interrupt();
  }
  
  // TIMERS
  Timer_100us_Init();
  Timer_100ms_Init();
  
  // ETHERNET
  W5100_InitLines();
  
  PARAM_STRUCT par;
  par.ui8Mode[0] = MR_TCP;
  par.ui8Mode[1] = MR_TCP;
  par.ui8Mode[2] = MR_UDP;
  
  
  par.ip_addr[0] = ip_addr[0];
  par.ip_addr[1] = ip_addr[1];
  par.ip_addr[2] = ip_addr[2];
  par.ip_addr[3] = ip_addr[3];
  
  par.sub_mask[0] = 255;
  par.sub_mask[1] = 255;
  par.sub_mask[2] = 255;
  par.sub_mask[3] = 0;
  
  par.gtw_addr[0] = 192;
  par.gtw_addr[1] = 168;
  par.gtw_addr[2] = 10;
  par.gtw_addr[3] = 1;
  
  W5100_Init(&par);
  
  
  // RS-485 MODBUS
  US.ui32Rate = rate;
  US.ui16StopBits = stop_bits;
  US.ui16Parity = parity;
  US.ui16Timeout = timeout;
  RS485_InitLines(&US);
  
  // param reset pin init
  Param_Reset_init();
    
  GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);

  while (1)
  {
    if (ui8ResetFlag == 0)
    {
      if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == Bit_SET)
      {
        ui8ResetFlag = 1;
        uiResetTimer = 10;
        
        GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
      }
    }
    else
    {
      if (uiResetTimer == 0 && GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7) == Bit_RESET)
      {
        ui8ParSave = 1;
        
        GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_SET);
        
        W5100_Delay_ms(1000);
        
        ip_addr[0] = 192;
        ip_addr[1] = 168;
        ip_addr[2] = 1;
        ip_addr[3] = 10;
      }
    }
    
    
    if (ui8ParSave)
    {
      ui8ParSave = 0;
      ui8ResetFlag = 0;
      
       
      // Unlock the internal flash
      FLASH_Unlock();
      
      __disable_interrupt();
      
      // стираем страницу
      FLASH_ErasePage(IP1Address);
        
      ip_addr32 = ip_addr[0] + (ip_addr[1]<<8) + (ip_addr[2]<<16) + (ip_addr[3]<<24);
      FLASH_ProgramWord(IP1Address, ip_addr32);   
      FLASH_ProgramHalfWord(PortAddress, port);
      FLASH_ProgramWord(RateAddress, rate);
      FLASH_ProgramHalfWord(SBAddress, stop_bits);
      FLASH_ProgramHalfWord(ParityAddress, parity);
      FLASH_ProgramHalfWord(TimeoutAddress, timeout);

      __enable_interrupt();
      
      
      ip_addr[0] = *((__IO uint8_t*)IP1Address);
      ip_addr[1] = *((__IO uint8_t*)IP2Address);
      ip_addr[2] = *((__IO uint8_t*)IP3Address);
      ip_addr[3] = *((__IO uint8_t*)IP4Address);
      
      port = *((__IO uint16_t*)PortAddress);
      rate = *((__IO uint32_t*)RateAddress);
      stop_bits = *((__IO uint16_t*)SBAddress);
      parity = *((__IO uint16_t*)ParityAddress);
      timeout = *((__IO uint16_t*)TimeoutAddress);
      
      // запуск watch dog
      IWDG_Enable();
      
      // вываливаемся из приложения
      while (1);
    }
  
    UDP_Process_handler();
    TCP_Process_handler1();
  };
  
}
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
