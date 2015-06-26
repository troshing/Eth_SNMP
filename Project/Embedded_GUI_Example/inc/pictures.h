/**
  ******************************************************************************
  * @file    pictures.h
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    02/04/2011
  * @brief   This file contains all the images to be printed on the LCD
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PICTURES_H
#define __PICTURES_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @addtogroup Pictures
  * @{
  */


/** @defgroup Pictures_Exported_Constants
  * @{
  */

extern const uint8_t TopBanner[24386];
#if !defined(STM32F10X_MD) && !defined(STM32F10X_MD_VL)

extern const uint8_t Loading_Image[2110];

extern const uint8_t SettingsLogo[20100];
extern const uint8_t NetWorkLogo[20100];

extern const uint8_t Forward_Image[4670];
extern const uint8_t Home_Image[4670];
extern const uint8_t Save_Image[4670];
extern const uint8_t Back_Image[4670];

extern const uint8_t IO_Image[4670];
extern const uint8_t Alarm_Image[4670];
extern const uint8_t Jornal_Image[4670];
extern const uint8_t Config_Image[4670];
extern const uint8_t Graph_Image[4670];
extern const uint8_t Info_Image[4670];
extern const uint8_t Exit_Image[4670];
extern const uint8_t Folder_Image[4670];


//extern const uint8_t STM32Logo[20066];
//extern const uint8_t Motorbike[16266];
//extern const uint8_t Car[16266];
//extern const uint8_t Bus[16266];
//extern const uint8_t Airplane[16266];

#elif defined(STM32F10X_MD) || defined(STM32F10X_MD_VL)

//extern const uint8_t STM32Logo[5054];

#endif /* !defined(STM32F10X_MD) && !defined(STM32F10X_MD_VL) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PICTURES_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
