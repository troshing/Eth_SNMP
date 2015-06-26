/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    02/04/2011
  * @brief   This file provides targets hardware configuration.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */

/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "wiznet.h"
#include "modbus.h"

#include <string.h>
#include <stdlib.h>

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup HWConfig
  * @brief Target Hardware initialization and configuration
  * @{
  */

/** @defgroup HWConfig_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */

/** @defgroup HWConfig_Private_Variables
  * @{
  */


const char HtmlText2[2][100] = {
  
/* 0*/  {"HTTP/1.0 200 OK\r\nContent-Type: image/gif\r\n"},
/* 1*/  {"Content-Length: 44072\r\n\r\n"},

};

const char Rate_9600[6][100] = {
  
/* 0*/  {"<option selected value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option value=\"115200\">115200</option>\r\n"}

};

const char Rate_14400[6][100] = {
  
/* 0*/  {"<option value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option selected value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option value=\"115200\">115200</option>\r\n"}

};

const char Rate_19200[6][100] = {
  
/* 0*/  {"<option value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option selected value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option value=\"115200\">115200</option>\r\n"}

};

const char Rate_38400[6][100] = {
  
/* 0*/  {"<option value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option selected value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option value=\"115200\">115200</option>\r\n"}

};

const char Rate_57600[6][100] = {
  
/* 0*/  {"<option value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option selected value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option value=\"115200\">115200</option>\r\n"}

};

const char Rate_115200[6][100] = {
  
/* 0*/  {"<option value=\"9600\">9600</option>\r\n"},
/* 1*/  {"<option value=\"14400\">14400</option>\r\n"},
/* 2*/  {"<option value=\"19200\">19200</option>\r\n"},
/* 3*/  {"<option value=\"38400\">38400</option>\r\n"},
/* 4*/  {"<option value=\"57600\">57600</option>\r\n"},
/* 5*/  {"<option selected value=\"115200\">115200</option>\r\n"}

};


const char Stopbits_1[2][100] = {
  
/* 0*/  {"<option selected value=\"0\">1</option>\r\n"},
/* 1*/  {"<option value=\"8192\">2</option>\r\n"},

};

const char Stopbits_2[2][100] = {
  
/* 0*/  {"<option value=\"0\">1</option>\r\n"},
/* 1*/  {"<option selected value=\"8192\">2</option>\r\n"},

};


const char Parity_No[3][100] = {
  
/* 0*/  {"<option selected value=\"0\">HET</option>\r\n"},
/* 1*/  {"<option value=\"1536\">ODD</option>\r\n"},
/* 2*/  {"<option value=\"1024\">EVEN</option>\r\n"},

};

const char Parity_Odd[3][100] = {
  
/* 0*/  {"<option value=\"0\">HET</option>\r\n"},
/* 1*/  {"<option selected value=\"1536\">ODD</option>\r\n"},
/* 2*/  {"<option value=\"1024\">EVEN</option>\r\n"},

};


const char Parity_Even[3][100] = {
  
/* 0*/  {"<option value=\"0\">HET</option>\r\n"},
/* 1*/  {"<option value=\"1536\">ODD</option>\r\n"},
/* 2*/  {"<option selected value=\"1024\">EVEN</option>\r\n"},

};



  
/* Extern variables ----------------------------------------------------------*/


// Define W5100 Socket Register and Variables Used
uint16_t delay_ms_cnt = 0;


uint8_t temp_ip_addr[4];
uint16_t temp_port;

uint8_t ip_addr[4];
uint16_t port;
uint32_t ip_addr32;

uint32_t rate;
uint16_t stop_bits;
uint16_t parity;
uint16_t timeout;


// переменные сокета
uint8_t TCP_buf[2048];
int getidx,postidx;
uint8_t CurentWebState = 0;
uint8_t sockstat;
uint16_t rsize,rsize1;


extern uint8_t ui8ParSave;

/**
  * @}
  */


 
// 0.1sec timer
void Timer_100ms_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* Enable the TIM7 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  // 0.1sec timer
  /* TIM6 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 7000;
  TIM_TimeBaseStructure.TIM_Prescaler = 1023;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);
  
  TIM_ARRPreloadConfig(TIM6, ENABLE);
  
  /* TIM6 enable counter */
  TIM_Cmd(TIM6, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
}

// 0.1msec timer
void Timer_100us_Init(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  /* Enable the TIM7 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* TIM7 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 7000;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
  
  TIM_ARRPreloadConfig(TIM7, ENABLE);
  
  /* TIM7 enable counter */
  TIM_Cmd(TIM7, ENABLE);
  
  /* TIM IT enable */
  TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
 
}

void Param_Reset_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  /*!< Configure RESET */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void LED_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
  
  /*!< Configure LED4C PD13 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12| GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
  
  GPIO_WriteBit(GPIOD,GPIO_Pin_13,Bit_RESET);
  GPIO_WriteBit(GPIOD,GPIO_Pin_11,Bit_SET);
}

void Delay_ms(uint16_t delay)
{
  delay_ms_cnt = delay*10;
  
  while (delay_ms_cnt)
  {
    asm("nop");
  };
}

void Delay_us(uint16_t delay)
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

void UDP_Process_handler(void)
{
  // чтение статуса
  sockstat = W5100_ReadStatus(UDP_SOCKET);
  if (sockstat != SOCK_UDP)
  {
    // инициализация сокета
    if ( W5100_socket(UDP_SOCKET,MR_UDP,port) )
    {
    }
      
  }
  else
  {
    // Get the client request size
    rsize = W5100_recv_size(UDP_SOCKET);
      
    // прем данных по UDP и отправка далее по RS-485
    if (rsize)
    {
      if ( W5100_recv(UDP_SOCKET,Modbus_GetTxBuffer(),rsize,temp_ip_addr,&temp_port) )
      {
        Modbus_SetTxPacketlength(rsize-UDP_HEADER_SIZE);
        Modbus_SendData();
      }
    }
      
    
    if ( Modbus_IsRxDataReady() )
    {
      temp_port = UDP_PORT;
      if ( W5100_send(UDP_SOCKET,Modbus_GetRxBuffer(),Modbus_GetRxDataSize(),temp_ip_addr,&temp_port) )
      {
        W5100_Delay_ms(1);
        Modbus_RxBufInit();
      }

    }
      
    
  }
    
}


void TCP_Process_handler1(void)
{
  int g1,g2,g3,g4,g5,g6;
  char buf[20];
  char s;
    
  // чтение статуса
  sockstat = W5100_ReadStatus(TCP_DEFAULT_SOCKET);
  switch (sockstat)
  {
  case SOCK_CLOSED:
    if ( W5100_socket(TCP_DEFAULT_SOCKET,MR_TCP,TCP_PORT) )
    {
      // Listen to Socket 0
      if (W5100_listen(TCP_DEFAULT_SOCKET) == 0) W5100_Delay_ms(1);
    }
    break;
        
  case SOCK_ESTABLISHED:
        
    Delay_us(1000);
    
    // Get the client request size
    rsize = W5100_recv_size(TCP_DEFAULT_SOCKET);
    
    rsize1 = 0xffff;
    while (rsize != rsize1)
    {
      rsize1 = rsize;
      
      Delay_us(10000);
      rsize = W5100_recv_size(TCP_DEFAULT_SOCKET);
    }
        
    if (rsize1)
    {

      // Now read the client Request
      if ( W5100_recv(TCP_DEFAULT_SOCKET,TCP_buf,rsize,0,0) == 0) break;
        
      // Check the Request Header
      // Now check the Radio Button for POST request
      postidx = W5100_strindex((char *)TCP_buf,"POST /");
      if (postidx >= 0)
      {
        g1 = W5100_strindex((char *)TCP_buf,"Editbox1=");
        g2 = W5100_strindex((char *)TCP_buf,"Editbox2=");
        g3 = W5100_strindex((char *)TCP_buf,"Combobox1=");
        g4 = W5100_strindex((char *)TCP_buf,"Combobox2=");
        g5 = W5100_strindex((char *)TCP_buf,"Combobox3=");
        g6 = W5100_strindex((char *)TCP_buf,"Editbox3=");
                
        if (g1 >= 0)
        {
          g1 += 9;
              
          for (uint16_t i = 0,j = g1,k = 0; i < 16 && k < 4; i++,j++)
          {
            if (TCP_buf[j] == '.' || TCP_buf[j] == ' ' || TCP_buf[j] == 0x0D )
            {
              TCP_buf[j] = 0;
              ip_addr[k++] = atoi((char*)(&TCP_buf[g1]));
              g1 = j+1;
            }
                    
          }
        }
                     
        if (g2 >= 0)
        {
          g2 += 9;

          g1 = W5100_strindex((char *)(&TCP_buf[g2]),"\r");
          TCP_buf[g1] = 0;
          port = atoi((char*)(&TCP_buf[g2]));
        }
          
        if (g3 >= 0)
        {
          g3 += 10;

          g1 = W5100_strindex((char *)(&TCP_buf[g3]),"\r");
          TCP_buf[g1] = 0;
          rate = atoi((char*)(&TCP_buf[g3]));
        }
        
        if (g4 >= 0)
        {
          g4 += 10;

          g1 = W5100_strindex((char *)(&TCP_buf[g4]),"\r");
          TCP_buf[g1] = 0;
          stop_bits = atoi((char*)(&TCP_buf[g4]));
        }
        
        if (g5 >= 0)
        {
          g5 += 10;

          g1 = W5100_strindex((char *)(&TCP_buf[g5]),"\r");
          TCP_buf[g1] = 0;
          parity = atoi((char*)(&TCP_buf[g5]));
        }
        
        if (g6 >= 0)
        {
          g6 += 9;

          g1 = W5100_strindex((char *)(&TCP_buf[g6]),"\r");
          TCP_buf[g1] = 0;
          timeout = atoi((char*)(&TCP_buf[g6]));
        }
        
        ui8ParSave = 1;
        
        W5100_close(TCP_DEFAULT_SOCKET);
        W5100_close(TCP_SOCKET);
        W5100_close(UDP_SOCKET);

        break;        
        
      } // if (postidx >= 0)
 
       
      getidx = W5100_strindex((char *)TCP_buf,"GET / HTTP/1.1");
          
      // Now check the Radio Button for GET request
      if (getidx >= 0)
      {

          for (uint16_t h = 0,k = 0; h < 7074; h++,k++)
          {
            if (k > 1999) k = 0;
            TCP_buf[k] = (*(__IO uint8_t*)(FileAddress1 + h));
                
            if (k > 1998)
            {
              TCP_buf[k+1] = 0;
              
              
              g1 = W5100_strindex((char *)TCP_buf,"Editbox1\" value=\"");
              if (g1 >= 0)
              {
                sprintf(buf,"%d%s%d%s%d%s%d",ip_addr[0],".",
                        ip_addr[1],".",ip_addr[2],".",ip_addr[3]);
              
                s = strlen(buf);
                g1 += 17;
              
                for (uint16_t i = 0,j = g1; i < 15; i++,j++)
                {
                  if (i < s) TCP_buf[j] = buf[i];
                  else       TCP_buf[j] = ' '; 
                }
              }
                
              g1 = W5100_strindex((char *)TCP_buf,"Editbox2\" value=\"");
              if (g1 >= 0)
              {
                sprintf(buf,"%d",port);
                s = strlen(buf);
                g1 += 17;
              
                for (uint16_t i = 0,j = g1; i < 5; i++,j++)
                {
                  if (i < s) TCP_buf[j] = buf[i];
                  else       TCP_buf[j] = ' ';
                }
              }
              
              g3 = W5100_strindex((char *)TCP_buf,"name=\"Combobox1\"");
              if (g3 >= 0)
              {
                g2 = W5100_strindex((char *)(&TCP_buf[g3]),"\r\n");
                if (g2 >= 0)
                {
                  g2 += 2;
                  g2 += g3;
                  switch (rate)
                  {
                  case 9600:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_9600[i][g3])
                      {
                        TCP_buf[g2++] = Rate_9600[i][g3++];
                      }
                    }
                    break;
                  case 14400:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_14400[i][g3])
                      {
                        TCP_buf[g2++] = Rate_14400[i][g3++];
                      }
                    }
                    break;
                  case 19200:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_19200[i][g3])
                      {
                        TCP_buf[g2++] = Rate_19200[i][g3++];
                      }
                    }
                    break;
                  case 38400:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_38400[i][g3])
                      {
                        TCP_buf[g2++] = Rate_38400[i][g3++];
                      }
                    }
                    break;
                  case 57600:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_57600[i][g3])
                      {
                        TCP_buf[g2++] = Rate_57600[i][g3++];
                      }
                    }
                    break;
                  case 115200:
                    for (uint8_t i = 0; i < 6; i++)
                    {
                      g3 = 0;
                      while (Rate_115200[i][g3])
                      {
                        TCP_buf[g2++] = Rate_115200[i][g3++];
                      }
                    }
                    break;
                  }
                }
              }
              
              
              g3 = W5100_strindex((char *)TCP_buf,"name=\"Combobox2\"");
              if (g3 >= 0)
              {
                g2 = W5100_strindex((char *)(&TCP_buf[g3]),"\r\n");
                if (g2 >= 0)
                {
                  g2 += 2;
                  g2 += g3;
                  switch (stop_bits)
                  {
                  case 0:
                    for (uint8_t i = 0; i < 2; i++)
                    {
                      g3 = 0;
                      while (Stopbits_1[i][g3])
                      {
                        TCP_buf[g2++] = Stopbits_1[i][g3++];
                      }
                    }
                    break;
                  case 8192:
                    for (uint8_t i = 0; i < 2; i++)
                    {
                      g3 = 0;
                      while (Stopbits_2[i][g3])
                      {
                        TCP_buf[g2++] = Stopbits_2[i][g3++];
                      }
                    }
                    break;
                  
                  }
                }
              }
              
              
              g3 = W5100_strindex((char *)TCP_buf,"name=\"Combobox3\"");
              if (g3 >= 0)
              {
                g2 = W5100_strindex((char *)(&TCP_buf[g3]),"\r\n");
                if (g2 >= 0)
                {
                  g2 += 2;
                  g2 += g3;
                  switch (parity)
                  {
                  case 0:
                    for (uint8_t i = 0; i < 3; i++)
                    {
                      g3 = 0;
                      while (Parity_No[i][g3])
                      {
                        TCP_buf[g2++] = Parity_No[i][g3++];
                      }
                    }
                    break;
                  case 1536:
                    for (uint8_t i = 0; i < 3; i++)
                    {
                      g3 = 0;
                      while (Parity_Odd[i][g3])
                      {
                        TCP_buf[g2++] = Parity_Odd[i][g3++];
                      }
                    }
                    break;
                  case 1024:
                    for (uint8_t i = 0; i < 3; i++)
                    {
                      g3 = 0;
                      while (Parity_Even[i][g3])
                      {
                        TCP_buf[g2++] = Parity_Even[i][g3++];
                      }
                    }
                    break;
                  
                  }
                }
              }
              
              g1 = W5100_strindex((char *)TCP_buf,"Editbox3\" value=\"");
              if (g1 >= 0)
              {
                sprintf(buf,"%d",timeout);
                s = strlen(buf);
                g1 += 17;
              
                for (uint16_t i = 0,j = g1; i < 4; i++,j++)
                {
                  if (i < s) TCP_buf[j] = buf[i];
                  else       TCP_buf[j] = ' ';
                }
              }

              // Now Send the HTTP Response
              if ( W5100_send(TCP_DEFAULT_SOCKET,TCP_buf,2000,0,0) == 0 ) break;
            }
          }

          
            
          // Now Send the HTTP Response
          if ( W5100_send(TCP_DEFAULT_SOCKET,TCP_buf,1074,0,0) == 0 ) break;

          W5100_disconnect(TCP_DEFAULT_SOCKET);
          break;
      }
              
      
      getidx = W5100_strindex((char *)TCP_buf,"GET /images/trc.gif HTTP/1.1");
          
      // Now check the Radio Button for GET request
      if (getidx >= 0)
      {
          TCP_buf[0] = 0;
          for (uint8_t k = 0; k < 2; k++)
          {
            strcat((char *)TCP_buf,HtmlText2[k]);
          };
              
          // Now Send the HTTP Response
          if ( W5100_send(TCP_DEFAULT_SOCKET,TCP_buf,strlen((char *)TCP_buf),0,0) == 0 ) break;


          for (uint16_t h = 0,k = 0; h < 44072; h++,k++)
          {
            if (k > 1999) k = 0;
            TCP_buf[k] = (*(__IO uint8_t*)(FileAddress + h));
                
            if (k > 1998)
            {
              TCP_buf[k+1] = 0;
                  
              // Now Send the HTTP Response
	      if ( W5100_send(TCP_DEFAULT_SOCKET,TCP_buf,2000,0,0) == 0 ) break;
            }
          }

          // Now Send the HTTP Response
	  if ( W5100_send(TCP_DEFAULT_SOCKET,TCP_buf,72,0,0) == 0 ) break;

          //Delay_us(10000);
          break;

      } // if (getidx >= 0)
      
      W5100_disconnect(TCP_DEFAULT_SOCKET);  

    } // if (rsize)

    
        
    break;
        
        
  case SOCK_FIN_WAIT:
  case SOCK_CLOSING:
  case SOCK_TIME_WAIT:
  case SOCK_CLOSE_WAIT:
  case SOCK_LAST_ACK:
        
    // Force to close the socket
    W5100_close(TCP_DEFAULT_SOCKET);
    break;
  }

    
}
 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
