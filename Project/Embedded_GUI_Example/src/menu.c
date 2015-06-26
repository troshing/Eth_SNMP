/**
  ******************************************************************************
  * @file    menu.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    02/04/2011
  * @brief   This file contains all the menu functions.
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "float.h"
#include "LcdHal.h"
#include "TscHal.h"
#include "pictures.h"

/** @addtogroup Embedded_GUI_Example
  * @{
  */

/** @defgroup Menu
  * @brief Menu main functions
  * @{
  */

/** @defgroup Menu_Private_TypesDefinitions
  * @{
  */

/**
  * @}
  */


/** @defgroup Menu_Private_Defines
  * @{
  */
#if defined(USE_STM3210C_EVAL) || defined(USE_STM32100E_EVAL)
 #define INPUT_SOURCE    "the pen or the joystick to select"
#else
 #define INPUT_SOURCE    "the joystick to select"
#endif
/**
  * @}
  */

/** @defgroup Menu_Private_Macros
  * @{
  */

/**
  * @}
  */

/** @defgroup Menu_Private_Variables
  * @{
  */

__IO uint8_t vu8_gPageCurrent = 0;
GL_Page_TypeDef *pageStart;
GL_Page_TypeDef *page0, *page1, *page2, *page3, *page4, *page5, *page6, *page7, *page8, *page9;
GL_Page_TypeDef *pageD0, *pageD1, *pageD2, *pageD3, *pageD4, *pageD5, *pageD6, *pageD7;
GL_bool stEmployee = GL_TRUE;
GL_bool drivingLicense = GL_FALSE;
GenderType user_gender = MAN;
uint8_t travellers = 0x00, favourite_speed = 0x00;


uint8_t cNetAddress = 50;
uint8_t cStartNetAddress = 2;
uint8_t cLastNetAddress = 2;

/**
  * @}
  */

/** @defgroup Menu_Private_FunctionPrototypes
  * @{
  */

static void HomeFuncLibrary(void);
static void NextFunc(void);
static void NextFunc1(void);
static void NextFunc2(void);
static void BackFunc(void);
static void BackFunc1(void);
static void BackFunc2(void);

static void HomeFuncDemo(void);
static void StartDemoFunc(void);
static void NextFuncD1(void);
static void NextFuncD2(void);
static void NextFuncD3(void);
static void NextFuncD4(void);
static void NextFuncD5(void);
static void BackFuncD1(void);
static void BackFuncD2(void);
static void BackFuncD3(void);
static void BackFuncD4(void);
static void BackFuncD5(void);
static void SwitchDemoBtnFunc(void);
static void RButtonFuncD1(void);
static void RButtonFuncD2(void);
static void CheckboxDemoFunc(void);
static void ComboboxDemoFunc(void);
//static void SlidebarDemoFunc(void);
static void FinishBtnFunc(void);


static void MENU_Settings_SwitchPage(GL_Page_TypeDef* PreviousPage, uint32_t PageIndex);
static void MENU_NetWork_SwitchPage(GL_Page_TypeDef* PreviousPage, uint32_t PageIndex);

static void Icon1Func(void);
static void Icon2Func(void);
static void SlidebarNodeAddressFunc(void);
static void RButtonRateFunc1(void);
static void RButtonRateFunc2(void);
static void RButtonRateFunc3(void);
static void SlidebarStartAddressFunc(void);
static void SlidebarLastAddressFunc(void);
static void SaveCanAddrFunc(void);

static void Icon1DFunc(void);
static void Icon2DFunc(void);
static void Icon3DFunc(void);
static void Icon4DFunc(void);
static void Icon5DFunc(void);
static void Icon6DFunc(void);
static void Icon7DFunc(void);

/**
  * @}
  */

/** @defgroup Menu_Private_Functions
  * @{
  */


/**
  * @brief  Initializes the MEnu with all the menu_variables de-initialized
  * @param  None
  * @retval None
  */
void MENU_DeInit(void)
{
  GL_PageControls_TypeDef* pageLabel_0a;
  
  GL_PageControls_TypeDef* IconLabel1;
  GL_PageControls_TypeDef* IconLabel2;
  GL_PageControls_TypeDef* Icon1;
  GL_PageControls_TypeDef* Icon2;
  GL_PageControls_TypeDef* TopBannerIcon;
  
  /*Resetting all the menu parameters*/
  vu8_gPageCurrent = PAGE_HOME;

  /* ************** GRAPHIC LIBRARY - PAGE 0 ************** */
  pageStart = malloc(sizeof(GL_Page_TypeDef));
  Create_PageObj( pageStart );

  TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
  AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageStart );

  pageLabel_0a = NewLabel( "pageLabel_0a", "Главное меню", GL_HORIZONTAL, GL_FONT_SMALL, GL_Blue );
  AddPageControlObj( (uint16_t)((LCD_Width / 11)*7.8), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_0a, pageStart );
  
  Icon1 = NewIcon( "Icon1", (uint8_t*) SettingsLogo, 100, 100, Icon1Func );
  AddPageControlObj( (uint16_t)((LCD_Width / 10)*8.6), (uint16_t)((LCD_Height / 9)*3.5), Icon1, pageStart );
  
  Icon2 = NewIcon( "Icon2", (uint8_t*) NetWorkLogo, 100, 100, Icon2Func );
  AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.6), (uint16_t)((LCD_Height / 9)*3.5), Icon2, pageStart );


  IconLabel1 = NewLabel( "IconLabel1", "Конфигурация", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
  AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.6), (uint16_t)((LCD_Height / 9)*7.5), IconLabel1, pageStart );
  IconLabel2 = NewLabel( "IconLabel2", "Сеть", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
  AddPageControlObj( (uint16_t)((LCD_Width / 9)*3.1), (uint16_t)((LCD_Height / 9)*7.5), IconLabel2, pageStart );

  GL_Clear(White);
  GL_SetTextColor(GL_Blue);
  pageStart->ShowPage( pageStart, GL_TRUE );
  /* Menu start with HOME screen */
}


/**
  * @brief  Start the Settings
  * @param  None
  * @retval None
  */
static void Icon1Func(void)
{
  MENU_Settings_SwitchPage(pageStart, PAGE_0);
}

/**
  * @brief  Start the Settings
  * @param  None
  * @retval None
  */
void MENU_Settings_Init(uint8_t InitPage)
{
  GL_PageControls_TypeDef* TopBannerIcon;

  // MYOWN ==================================
  
  // page 0
  GL_PageControls_TypeDef* pageLabel_0;
  GL_PageControls_TypeDef* SlidebarNodeAddress;
  GL_PageControls_TypeDef* SlideBarLabel_0_1;
  GL_PageControls_TypeDef* SlideBarLabel_0_2;
  GL_PageControls_TypeDef* SlideBarLabel_0_3;
  
  GL_PageControls_TypeDef* IconLabel_0_1;
  GL_PageControls_TypeDef* IconLabel_0_2;
  GL_PageControls_TypeDef* Icon_0_1;
  GL_PageControls_TypeDef* Icon_0_2;
  GL_PageControls_TypeDef* Icon_0_3;

  
  // page 1
  GL_PageControls_TypeDef* pageLabel_1;
  GL_RadioButtonGrp_TypeDef* RadioButtonGrp1;
  GL_PageControls_TypeDef* RadioOption_1_a;
  GL_PageControls_TypeDef* RadioOption_1_b;
  GL_PageControls_TypeDef* RadioOption_1_c;
  GL_PageControls_TypeDef* RadioButtonLabel_1_1;
  GL_PageControls_TypeDef* RadioButtonLabel_1_2;
  //GL_PageControls_TypeDef* RadioButtonLabel_1_3;
  GL_PageControls_TypeDef* Icon_1_1;
  GL_PageControls_TypeDef* Icon_1_2;
  GL_PageControls_TypeDef* Icon_1_3;
  GL_PageControls_TypeDef* Icon_1_4;
  
  // page 2
  GL_PageControls_TypeDef* pageLabel_2;
  GL_PageControls_TypeDef* SlidebarStartAddress;
  GL_PageControls_TypeDef* SlideBarLabel_2_1;
  GL_PageControls_TypeDef* SlideBarLabel_2_2;
  GL_PageControls_TypeDef* SlideBarLabel_2_3;
  GL_PageControls_TypeDef* Icon_2_1;
  GL_PageControls_TypeDef* Icon_2_2;
  GL_PageControls_TypeDef* Icon_2_3;
  GL_PageControls_TypeDef* Icon_2_4;
  
  // page 3
  GL_PageControls_TypeDef* pageLabel_3;
  GL_PageControls_TypeDef* SlidebarLastAddress;
  GL_PageControls_TypeDef* SlideBarLabel_3_1;
  GL_PageControls_TypeDef* SlideBarLabel_3_2;
  GL_PageControls_TypeDef* SlideBarLabel_3_3;
  GL_PageControls_TypeDef* Icon_3_1;
  GL_PageControls_TypeDef* Icon_3_2;
  GL_PageControls_TypeDef* Icon_3_3;
  
  uint8_t* empty_string = "         ";
  uint16_t percentage_value = 50;
  uint8_t percentage_string[4];
  
  // ENDOF MYOWN ============================

  GL_SetBackColor( GL_White );
  GL_SetTextColor( GL_Blue );

  switch (InitPage)
  {
    case PAGE_0:
    {
      /* ************** SETTINGS - PAGE 0 ********************************** */
      page0 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( page0 );
      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, page0 );

      pageLabel_0 = NewLabel( "pageLabel_0", "CAN Адрес", GL_HORIZONTAL, GL_FONT_SMALL, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*8), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_0, page0 );

      SlidebarNodeAddress = NewSlidebar( "SlidebarNodeAddress", "диапазон: 50-69", /*0, 95, */( (cNetAddress-50)*5 ), 5,
                                        GL_HORIZONTAL, SlidebarNodeAddressFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.7), (uint16_t)((LCD_Height / 9)*2.9), SlidebarNodeAddress, page0 );
      
      SlideBarLabel_0_1 = NewLabel( "SlideBarLabel_0_1", "Задайте CAN адрес пульта", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*5.6), SlideBarLabel_0_1, page0 );
      
      percentage_value = cNetAddress;
      sprintf((char*)percentage_string, "%d", percentage_value);

      GL_SetTextColor(GL_Red);
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
      GL_SetTextColor(GL_Blue);
      
      Icon_0_1 = NewIcon( "Icon_0_1", (uint8_t*) Home_Image, 48, 48, HomeFuncLibrary );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.8), (uint16_t)((LCD_Height / 9)*7), Icon_0_1, page0 );
  
      Icon_0_2 = NewIcon( "Icon_0_2", (uint8_t*) Forward_Image, 48, 48, NextFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*5.0), (uint16_t)((LCD_Height / 9)*7), Icon_0_2, page0 );
      
      Icon_0_3 = NewIcon( "Icon_0_3", (uint8_t*) Save_Image, 48, 48, SaveCanAddrFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*1.7), (uint16_t)((LCD_Height / 9)*7), Icon_0_3, page0 );


      //IconLabel_0_1 = NewLabel( "IconLabel_0_1", "В начало", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      //AddPageControlObj( (uint16_t)((LCD_Width / 9)*6.18), (uint16_t)((LCD_Height / 9)*8), IconLabel_0_1, page0 );
      //IconLabel_0_2 = NewLabel( "IconLabel_0_2", "Далее", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      //AddPageControlObj( (uint16_t)((LCD_Width / 9)*4.5), (uint16_t)((LCD_Height / 9)*8), IconLabel_0_2, page0 );

    }
    break;
    case PAGE_1:
    {
      /* ************** Settings - PAGE 1 ********************************** */
      page1 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( page1 );
      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, page1 );

      pageLabel_1 = NewLabel( "pageLabel_1", "CAN скорость", GL_HORIZONTAL, GL_FONT_SMALL, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*8), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_1, page1 );

      RadioButtonGrp1 = NewRadioButtonGrp("RadioButtonGrp1");
      RadioOption_1_a = RADIO_BUTTON_ADD(RadioButtonGrp1, "20кбит/с", RButtonRateFunc1);
      RadioOption_1_b = RADIO_BUTTON_ADD(RadioButtonGrp1, "100кбит/с", RButtonRateFunc2);
      RadioOption_1_c = RADIO_BUTTON_ADD(RadioButtonGrp1, "500кбит/с", RButtonRateFunc3);
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.3), (uint16_t)((LCD_Height / 9)*2.5), RadioOption_1_a, page1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.3), (uint16_t)((LCD_Height / 9)*3.4), RadioOption_1_b, page1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.3), (uint16_t)((LCD_Height / 9)*4.3), RadioOption_1_c, page1 );

      RadioButtonLabel_1_1 = NewLabel( "RadioButtonLabel_1_1", "Задайте скорость обмена", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.2), (uint16_t)((LCD_Height / 9)*6.1), RadioButtonLabel_1_1, page1 );
      RadioButtonLabel_1_2 = NewLabel( "RadioButtonLabel_1_2", "по CAN сети", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.2), (uint16_t)((LCD_Height / 9)*6.6), RadioButtonLabel_1_2, page1 );
      //RadioButtonLabel_1_3 = NewLabel( "RadioButtonLabel_1_3", "the desired option.", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      //AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.2), (uint16_t)((LCD_Height / 9)*7.2), RadioButtonLabel_1_3, page1 );
      
      Icon_1_1 = NewIcon( "Icon_1_1", (uint8_t*) Home_Image, 48, 48, HomeFuncLibrary );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.8), (uint16_t)((LCD_Height / 9)*7), Icon_1_1, page1 );
      
      Icon_1_2 = NewIcon( "Icon_1_2", (uint8_t*) Back_Image, 48, 48, BackFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*7), Icon_1_2, page1 );
  
      Icon_1_3 = NewIcon( "Icon_1_3", (uint8_t*) Forward_Image, 48, 48, NextFunc1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*5.0), (uint16_t)((LCD_Height / 9)*7), Icon_1_3, page1 );
      
      Icon_1_4 = NewIcon( "Icon_1_4", (uint8_t*) Save_Image, 48, 48, SaveCanAddrFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*1.7), (uint16_t)((LCD_Height / 9)*7), Icon_1_4, page1 );
    }
    break;
    case PAGE_2:
    {
      /* ************** Settings - PAGE 2 ********************************** */
      page2 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( page2 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, page2 );

      pageLabel_2 = NewLabel( "pageLabel_2", "Начальный CAN адрес", GL_HORIZONTAL, GL_FONT_SMALL, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*9), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_2, page2 );

      SlidebarStartAddress = NewSlidebar( "SlidebarStartAddress", "диапазон: 2-49", /*2, 49, */( (cStartNetAddress-2)*2 ), 2,
                                         GL_HORIZONTAL, SlidebarStartAddressFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.7), (uint16_t)((LCD_Height / 9)*2.9), SlidebarStartAddress, page2 );

      SlideBarLabel_2_1 = NewLabel( "SlideBarLabel_2_1", "Задайте стартовый CAN адрес", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*5.6), SlideBarLabel_2_1, page2 );
      SlideBarLabel_2_2 = NewLabel( "SlideBarLabel_2_2", "для поиска контроллеров", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*6.1), SlideBarLabel_2_2, page2 );
      SlideBarLabel_2_3 = NewLabel( "SlideBarLabel_2_3", "в CAN сети", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*6.6), SlideBarLabel_2_3, page2 );
  
      percentage_value = cStartNetAddress;
      sprintf((char*)percentage_string, "%d", percentage_value);

      GL_SetTextColor(GL_Red);
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
      GL_SetTextColor(GL_Blue);

      Icon_2_1 = NewIcon( "Icon_2_1", (uint8_t*) Home_Image, 48, 48, HomeFuncLibrary );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.8), (uint16_t)((LCD_Height / 9)*7), Icon_2_1, page2 );
      
      Icon_2_2 = NewIcon( "Icon_2_2", (uint8_t*) Back_Image, 48, 48, BackFunc1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*7), Icon_2_2, page2 );
  
      Icon_2_3 = NewIcon( "Icon_2_3", (uint8_t*) Forward_Image, 48, 48, NextFunc2 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*5.0), (uint16_t)((LCD_Height / 9)*7), Icon_2_3, page2 );
      
      Icon_2_4 = NewIcon( "Icon_2_4", (uint8_t*) Save_Image, 48, 48, SaveCanAddrFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*1.7), (uint16_t)((LCD_Height / 9)*7), Icon_2_4, page2 );
    }
    break;
    case PAGE_3:
    {
      /* ************** GRAPHIC LIBRARY PRESENTATION - PAGE 3 ************** */
      page3 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( page3 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, page3 );

      pageLabel_3 = NewLabel( "pageLabel_3", "Конечный CAN адрес", GL_HORIZONTAL, GL_FONT_SMALL, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*9), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_3, page3 );

      SlidebarLastAddress = NewSlidebar( "SlidebarLastAddress", "диапазон: 2-49", /*2, 49, */( (cLastNetAddress-2)*2 ), 2,
                                        GL_HORIZONTAL, SlidebarLastAddressFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.7), (uint16_t)((LCD_Height / 9)*2.9), SlidebarLastAddress, page3 );

      SlideBarLabel_3_1 = NewLabel( "SlideBarLabel_3_1", "Задайте конечный CAN адрес", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*5.6), SlideBarLabel_3_1, page3 );
      SlideBarLabel_3_2 = NewLabel( "SlideBarLabel_3_2", "для поиска контроллеров", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*6.1), SlideBarLabel_3_2, page3 );
      SlideBarLabel_3_3 = NewLabel( "SlideBarLabel_3_3", "в CAN сети", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*6.6), SlideBarLabel_3_3, page3 );
  
      percentage_value = cLastNetAddress;
      sprintf((char*)percentage_string, "%d", percentage_value);

      GL_SetTextColor(GL_Red);
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
      GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
      GL_SetTextColor(GL_Blue);

      Icon_3_1 = NewIcon( "Icon_3_1", (uint8_t*) Home_Image, 48, 48, HomeFuncLibrary );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.8), (uint16_t)((LCD_Height / 9)*7), Icon_3_1, page3 );
      
      Icon_3_2 = NewIcon( "Icon_3_2", (uint8_t*) Back_Image, 48, 48, BackFunc2 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*7), Icon_3_2, page3 );
      
      Icon_3_3 = NewIcon( "Icon_3_3", (uint8_t*) Save_Image, 48, 48, SaveCanAddrFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*1.7), (uint16_t)((LCD_Height / 9)*7), Icon_3_3, page3 );
    }
    break;
    
    default:
      break;
  }
  /* ********** End of Pages Creation for GRAPHIC LIBRARY PRESENTATION ********** */
}

/**
  * @brief  Start the NetWork
  * @param  None
  * @retval None
  */
static void Icon2Func(void)
{
  MENU_NetWork_SwitchPage(pageStart, PAGE_D0);
}


/**
  * @brief  Start the NetWork
  * @param  None
  * @retval None
  */
void MENU_Demo_Init(uint8_t InitPage)
{
  GL_PageControls_TypeDef* TopBannerIcon;
  GL_PageControls_TypeDef* pageLabel_D0;
  GL_PageControls_TypeDef* DemoStartLabel1;
  GL_PageControls_TypeDef* DemoStartLabel2;
  GL_PageControls_TypeDef* DemoStartLabel3;
  GL_PageControls_TypeDef* DemoStartLabel4;
  GL_PageControls_TypeDef* DemoStartLabel5;
  GL_PageControls_TypeDef* StartButton;
  GL_PageControls_TypeDef* HomeButtonD0;
  GL_PageControls_TypeDef* HomeButtonD1;
  GL_PageControls_TypeDef* HomeButtonD2;
  GL_PageControls_TypeDef* HomeButtonD3;
  GL_PageControls_TypeDef* HomeButtonD4;
  GL_PageControls_TypeDef* HomeButtonD5;
  GL_PageControls_TypeDef* NextButtonD1;
  GL_PageControls_TypeDef* NextButtonD2;
  GL_PageControls_TypeDef* NextButtonD3;
  GL_PageControls_TypeDef* NextButtonD4;
  GL_PageControls_TypeDef* NextButtonD5;
  GL_PageControls_TypeDef* BackButtonD1;
  GL_PageControls_TypeDef* BackButtonD2;
  GL_PageControls_TypeDef* BackButtonD3;
  GL_PageControls_TypeDef* BackButtonD4;
  GL_PageControls_TypeDef* BackButtonD5;
  GL_PageControls_TypeDef* pageLabel_D1;
  GL_PageControls_TypeDef* pageLabel_D2;
  GL_PageControls_TypeDef* pageLabel_D3;
  GL_PageControls_TypeDef* pageLabel_D4;
  GL_PageControls_TypeDef* pageLabel_D5;
  GL_PageControls_TypeDef* pageLabel_D6;
  GL_PageControls_TypeDef* pageLabel_D7a;
  GL_PageControls_TypeDef* pageLabel_D7b;
#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL)
  GL_PageControls_TypeDef* pageLabel_D7c;
#endif
  GL_PageControls_TypeDef* SwitchDemoBtn;
  GL_PageControls_TypeDef* SwitchLabelD1;
  GL_RadioButtonGrp_TypeDef* RadioButtonDemoGrp;
  GL_PageControls_TypeDef* RadioOptionD_a;
  GL_PageControls_TypeDef* RadioOptionD_b;
  GL_PageControls_TypeDef* RadioButtonLabelD1;
  GL_PageControls_TypeDef* RadioButtonLabelD2;
  GL_PageControls_TypeDef* CheckBoxDemo;
  GL_PageControls_TypeDef* CheckboxLabelD1;
  GL_PageControls_TypeDef* CheckboxLabelD2;
  GL_PageControls_TypeDef* ComboBoxDemoGrp1;
  GL_PageControls_TypeDef* ComboboxLabelD1;
  GL_PageControls_TypeDef* ComboboxLabelD2;
  //GL_PageControls_TypeDef* SlidebarDemo;
  GL_PageControls_TypeDef* SlideBarLabelD1;
  GL_PageControls_TypeDef* SlideBarLabelD2;
  GL_PageControls_TypeDef* FinishBtn;
  GL_PageControls_TypeDef* FinishBtnLabel1;
  GL_PageControls_TypeDef* FinishBtnLabel2;
  GL_PageControls_TypeDef* RestartBtn;
#if !defined(STM32F10X_MD) && !defined(STM32F10X_MD_VL)
  GL_PageControls_TypeDef* TransportationIcon;
#endif
  
  
  //============== MyOwn =========================================
  
  GL_PageControls_TypeDef* Icon1;
  GL_PageControls_TypeDef* Icon2;
  GL_PageControls_TypeDef* Icon3;
  GL_PageControls_TypeDef* Icon4;
  GL_PageControls_TypeDef* Icon5;
  GL_PageControls_TypeDef* Icon6;
  GL_PageControls_TypeDef* Icon7;
  
  GL_PageControls_TypeDef* IconLabel1;
  GL_PageControls_TypeDef* IconLabel2;
  GL_PageControls_TypeDef* IconLabel3;
  GL_PageControls_TypeDef* IconLabel4;
  GL_PageControls_TypeDef* IconLabel5;
  GL_PageControls_TypeDef* IconLabel6;
  GL_PageControls_TypeDef* IconLabel7;
  
  GL_PageControls_TypeDef* Icon1_1;
  GL_PageControls_TypeDef* Icon1_2;
  GL_PageControls_TypeDef* Icon1_3;
  GL_PageControls_TypeDef* Icon1_4;
  GL_PageControls_TypeDef* Icon1_5;
  GL_PageControls_TypeDef* Icon1_6;
  
  GL_PageControls_TypeDef* IconLabel1_1;
  GL_PageControls_TypeDef* IconLabel1_2;
  GL_PageControls_TypeDef* IconLabel1_3;
  
  //==============================================================
  switch (InitPage)
  {
    case PAGE_D0:
    {
      /* ************** DEMO APPLICATION - PAGE 0 ************** */
      pageD0 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD0 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD0 );

      //pageLabel_D0 = NewLabel( "pageLabel_D0", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      //AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D0, pageD0 );

      Icon1 = NewIcon( "Icon1", (uint8_t*) IO_Image, 48, 48, Icon1DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*2.0), Icon1, pageD0 );
  
      Icon2 = NewIcon( "Icon2", (uint8_t*) Alarm_Image, 48, 48, Icon2DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*2.0), Icon2, pageD0 );
      
      Icon3 = NewIcon( "Icon3", (uint8_t*) Jornal_Image, 48, 48, Icon3DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*2.0), Icon3, pageD0 );
      
      Icon4 = NewIcon( "Icon4", (uint8_t*) Config_Image, 48, 48, Icon4DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*2.0), (uint16_t)((LCD_Height / 9)*2.0), Icon4, pageD0 );
      
      IconLabel1 = NewLabel( "IconLabel1", "Вх/Вых", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*4.0), IconLabel1, pageD0 );
      IconLabel2 = NewLabel( "IconLabel2", "Аварии", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*4.0), IconLabel2, pageD0 );
      IconLabel3 = NewLabel( "IconLabel3", "Журналы", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*4.0), IconLabel3, pageD0 );
      IconLabel4 = NewLabel( "IconLabel4", "Параметры", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*2.3), (uint16_t)((LCD_Height / 9)*4.0), IconLabel4, pageD0 );
      
      Icon5 = NewIcon( "Icon5", (uint8_t*) Graph_Image, 48, 48, Icon5DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*5.0), Icon5, pageD0 );
      
      Icon6 = NewIcon( "Icon6", (uint8_t*) Info_Image, 48, 48, Icon6DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*5.0), Icon6, pageD0 );
      
      Icon7 = NewIcon( "Icon7", (uint8_t*) Exit_Image, 48, 48, Icon7DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*5.0), Icon7, pageD0 );


      IconLabel5 = NewLabel( "IconLabel5", "График", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*7.0), IconLabel5, pageD0 );
      IconLabel6 = NewLabel( "IconLabel6", "Состояние", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.3), (uint16_t)((LCD_Height / 9)*7.0), IconLabel6, pageD0 );
      IconLabel7 = NewLabel( "IconLabel7", "Выход", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*7.0), IconLabel7, pageD0 );

    }
    break;
    case PAGE_D1:
    {
      /* ************** DEMO APPLICATION - PAGE 1 ************** */
      pageD1 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD1 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD1 );

      /*Icon1_1 = NewIcon( "Icon1_1", (uint8_t*) Folder_Image, 48, 48, Icon1_1DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*2.0), Icon1_1, pageD1 );
  
      Icon1_2 = NewIcon( "Icon1_2", (uint8_t*) Folder_Image, 48, 48, Icon1_2DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*2.0), Icon1_2, pageD1 );
      
      Icon1_3 = NewIcon( "Icon1_3", (uint8_t*) Folder_Image, 48, 48, Icon1_3DFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*2.0), Icon1_3, pageD1 );
    
      
      IconLabel1_1 = NewLabel( "IconLabel1_1", "Вх/Вых", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.5), (uint16_t)((LCD_Height / 9)*4.0), IconLabel1_1, pageD1 );
      IconLabel1_2 = NewLabel( "IconLabel1_2", "Аварии", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*4.0), IconLabel1_2, pageD1 );
      IconLabel1_3 = NewLabel( "IconLabel1_3", "Журналы", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*4.5), (uint16_t)((LCD_Height / 9)*4.0), IconLabel1_3, pageD1 );
      
      
      Icon1_4 = NewIcon( "Icon1_4", (uint8_t*) Home_Image, 48, 48, HomeDFuncLibrary );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*9.8), (uint16_t)((LCD_Height / 9)*7), Icon_2_1, pageD1 );
      
      Icon1_5 = NewIcon( "Icon1_5", (uint8_t*) Back_Image, 48, 48, BackDFunc1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.0), (uint16_t)((LCD_Height / 9)*7), Icon_2_2, pageD1 );
  
      Icon1_6 = NewIcon( "Icon1_6", (uint8_t*) Forward_Image, 48, 48, NextDFunc1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*5.0), (uint16_t)((LCD_Height / 9)*7), Icon_2_3, pageD1 );*/

    }
    break;
    case PAGE_D2:
    {
      /* ************** DEMO APPLICATION - PAGE 2 ************** */
      pageD2 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD2 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD2 );

      pageLabel_D2 = NewLabel( "pageLabel_D2", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D2, pageD2 );

      RadioButtonDemoGrp = NewRadioButtonGrp("RadioButtonDemoGrp");
      RadioOptionD_a = RADIO_BUTTON_ADD(RadioButtonDemoGrp, "Man", RButtonFuncD1);
      RadioOptionD_b = RADIO_BUTTON_ADD(RadioButtonDemoGrp, "Woman", RButtonFuncD2);
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6), (uint16_t)((LCD_Height / 9)*2.9), RadioOptionD_a, pageD2 );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6), (uint16_t)((LCD_Height / 9)*3.9), RadioOptionD_b, pageD2 );

      RadioButtonLabelD1 = NewLabel( "RadioButtonLabelD1", "Select your gender:", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*6.3), (uint16_t)((LCD_Height / 9)*5.2), RadioButtonLabelD1, pageD2 );
      RadioButtonLabelD2 = NewLabel( "RadioButtonLabelD2", "Man or Woman?", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*6.3), (uint16_t)((LCD_Height / 9)*5.7), RadioButtonLabelD2, pageD2 );

      BackButtonD1 = NewButton( "BackButtonD1", "<BACK", BackFuncD1 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.3), (uint16_t)((LCD_Height / 9)*8), BackButtonD1, pageD2 );

      HomeButtonD2 = NewButton( "HomeButtonD2", "HOME", HomeFuncDemo );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*5.18), (uint16_t)((LCD_Height / 9)*8), HomeButtonD2, pageD2 );

      NextButtonD2 = NewButton( "NextButtonD2", "NEXT>", NextFuncD2 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*3.3), (uint16_t)((LCD_Height / 9)*8), NextButtonD2, pageD2 );

    }
    break;
    case PAGE_D3:
    {
      /* ************** DEMO APPLICATION - PAGE 3 ************** */
      pageD3 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD3 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD3 );

      pageLabel_D3 = NewLabel( "pageLabel_D3", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D3, pageD3 );

      CheckBoxDemo = NewCheckbox( "CheckBoxDemo", "I own a Driving license", CheckboxDemoFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.9), (uint16_t)((LCD_Height / 9)*3.2), CheckBoxDemo, pageD3 );

      CheckboxLabelD1 = NewLabel( "CheckboxLabelD1", "Select the Checkbox if you", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*4.6), CheckboxLabelD1, pageD3 );
      CheckboxLabelD2 = NewLabel( "CheckboxLabelD2", "have the driving license", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*5.1), CheckboxLabelD2, pageD3 );

      BackButtonD2 = NewButton( "BackButtonD2", "<BACK", BackFuncD2 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.3), (uint16_t)((LCD_Height / 9)*8), BackButtonD2, pageD3 );

      HomeButtonD3 = NewButton( "HomeButtonD3", "HOME", HomeFuncDemo );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*5.18), (uint16_t)((LCD_Height / 9)*8), HomeButtonD3, pageD3 );

      NextButtonD3 = NewButton( "NextButtonD3", "NEXT>", NextFuncD3 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*3.3), (uint16_t)((LCD_Height / 9)*8), NextButtonD3, pageD3 );
    }
    break;
    case PAGE_D4:
    {
      /* ************** DEMO APPLICATION - PAGE 4 ************** */
      pageD4 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD4 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD4 );

      pageLabel_D4 = NewLabel( "pageLabel_D4", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D4, pageD4 );

      ComboBoxDemoGrp1 = NewComboBoxGrp("ComboBoxDemoGrp1");
      AddComboOption (ComboBoxDemoGrp1->objPTR, "Alone", ComboboxDemoFunc);
      AddComboOption (ComboBoxDemoGrp1->objPTR, "1 People", ComboboxDemoFunc);
      AddComboOption (ComboBoxDemoGrp1->objPTR, "2-4 People", ComboboxDemoFunc);
      AddComboOption (ComboBoxDemoGrp1->objPTR, "More than 4", ComboboxDemoFunc);
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*7.4), (uint16_t)((LCD_Height / 9)*3.2), ComboBoxDemoGrp1, pageD4 );

      ComboboxLabelD1 = NewLabel( "ComboboxLabelD1", "How many people do", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*6.2), (uint16_t)((LCD_Height / 9)*4.6), ComboboxLabelD1, pageD4 );
      ComboboxLabelD2 = NewLabel( "ComboboxLabelD2", "You travel with?", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*6.2), (uint16_t)((LCD_Height / 9)*5.1), ComboboxLabelD2, pageD4 );

      BackButtonD3 = NewButton( "BackButtonD3", "<BACK", BackFuncD3 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.3), (uint16_t)((LCD_Height / 9)*8), BackButtonD3, pageD4 );

      HomeButtonD4 = NewButton( "HomeButtonD4", "HOME", HomeFuncDemo );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*5.18), (uint16_t)((LCD_Height / 9)*8), HomeButtonD4, pageD4 );

      NextButtonD4 = NewButton( "NextButtonD4", "NEXT>", NextFuncD4 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*3.3), (uint16_t)((LCD_Height / 9)*8), NextButtonD4, pageD4 );

    }
    break;
    case PAGE_D5:
    {
      /* ************** DEMO APPLICATION - PAGE 5 ************** */
      pageD5 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD5 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD5 );

      pageLabel_D5 = NewLabel( "pageLabel_D5", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D5, pageD5 );

      //SlidebarDemo = NewSlidebar( "SlidebarDemo", "Speed:0-300 KMh", 5, GL_HORIZONTAL, SlidebarDemoFunc );
      //AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.7), (uint16_t)((LCD_Height / 9)*2.9), SlidebarDemo, pageD5 );

      SlideBarLabelD1 = NewLabel( "SlideBarLabelD1", "Move the cursor to select", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*5.6), SlideBarLabelD1, pageD5 );
      SlideBarLabelD2 = NewLabel( "SlideBarLabelD2", "your favourite cruise speed", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.1), (uint16_t)((LCD_Height / 9)*6.1), SlideBarLabelD2, pageD5 );

      BackButtonD4 = NewButton( "BackButtonD4", "<BACK", BackFuncD4 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.3), (uint16_t)((LCD_Height / 9)*8), BackButtonD4, pageD5 );

      HomeButtonD5 = NewButton( "HomeButtonD5", "HOME", HomeFuncDemo );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*5.18), (uint16_t)((LCD_Height / 9)*8), HomeButtonD5, pageD5 );

      NextButtonD5 = NewButton( "NextButtonD5", "NEXT>", NextFuncD5 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*3.3), (uint16_t)((LCD_Height / 9)*8), NextButtonD5, pageD5 );

    }
    break;
    case PAGE_D6:
    {
      /* ************** DEMO APPLICATION - PAGE 6 ************** */
      pageD6 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD6 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD6 );

      pageLabel_D6 = NewLabel( "pageLabel_D6", "Graphic Library Demo", GL_HORIZONTAL, GL_FONT_BIG, GL_Blue );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*10.6), (uint16_t)((LCD_Height / 10)*1.8), pageLabel_D6, pageD6 );

      FinishBtn = NewButton( "FinishBtn", "FINISH", FinishBtnFunc );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.2), (uint16_t)((LCD_Height / 9)*3.2), FinishBtn, pageD6 );

      FinishBtnLabel1 = NewLabel( "FinishBtnLabel1", "Click on Finish to find out the", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.8), (uint16_t)((LCD_Height / 9)*4.6), FinishBtnLabel1, pageD6 );
      FinishBtnLabel2 = NewLabel( "FinishBtnLabel2", "better transportation for you", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.8), (uint16_t)((LCD_Height / 9)*5.1), FinishBtnLabel2, pageD6 );

      BackButtonD5 = NewButton( "BackButtonD5", "<BACK", BackFuncD5 );
      AddPageControlObj( (uint16_t)((LCD_Width / 9)*7.2), (uint16_t)((LCD_Height / 9)*8), BackButtonD5, pageD6 );

    }
    break;
    case PAGE_D7:
    {
      /* ************** DEMO APPLICATION - PAGE 7 ************** */
      pageD7 = malloc(sizeof(GL_Page_TypeDef));
      Create_PageObj( pageD7 );

      TopBannerIcon = NewIcon( "TopBannerIcon", (uint8_t*) TopBanner, 320, 38, NullFunc );
      AddPageControlObj( LCD_Width - 1, 0, TopBannerIcon, pageD7 );

      pageLabel_D7a = NewLabel( "pageLabel_D7a", "The better transportation", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*8.4), (uint16_t)((LCD_Height / 10)*2.2), pageLabel_D7a, pageD7 );

      pageLabel_D7b = NewLabel( "pageLabel_D7b", "for You, is the following:", GL_HORIZONTAL, GL_FONT_SMALL, GL_Black );
      AddPageControlObj( (uint16_t)((LCD_Width / 11)*8.4), (uint16_t)((LCD_Height / 10)*2.8), pageLabel_D7b, pageD7 );

      RestartBtn = NewButton( "RestartBtn", "RESTART", HomeFuncDemo );
      AddPageControlObj( (uint16_t)((LCD_Width / 10)*6.2), (uint16_t)((LCD_Height / 9)*8), RestartBtn, pageD7 );

#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL)
      pageLabel_D7c = NewLabel( "pageLabel_D7c", "", GL_HORIZONTAL, GL_FONT_BIG, GL_Red );
      AddPageControlObj(  (uint16_t)((LCD_Width / 2) + ((5*GL_FONT_BIG_WIDTH) / 2)), (uint16_t)((LCD_Height / 2) - 10), pageLabel_D7c, pageD7 );
#else
      TransportationIcon = NewIcon ("TransportationIcon", GL_NULL, 90, 90, NullFunc);
      AddPageControlObj( (uint16_t)((LCD_Width / 2) + 45), (uint16_t)((LCD_Height / 2) - 40), TransportationIcon, pageD7 );
#endif

    }
    break;
    default:
      break;
  }

  /* ********** End of Page Creation for GRAPHIC LIBRARY DEMO TEST APPLICATION ********** */
}

/**
  * @brief  HomeFuncLibrary
  * @param  None
  * @retval None
  */
static void HomeFuncLibrary(void)
{

  /* check the page to destroy */
  switch (vu8_gPageCurrent)
  {
    case PAGE_0:
    {
      page0->ShowPage(page0, GL_FALSE);
      DestroyPage(page0);
      free(page0);
    }
    break;
    case PAGE_1:
    {
      page1->ShowPage(page1, GL_FALSE);
      DestroyPage(page1);
      free(page1);
    }
    break;
    case PAGE_2:
    {
      page2->ShowPage(page2, GL_FALSE);
      DestroyPage(page2);
      free(page2);
    }
    break;
    case PAGE_3:
    {
      page3->ShowPage(page3, GL_FALSE);
      DestroyPage(page3);
      free(page3);
    }
    break;
    case PAGE_4:
    {
      page4->ShowPage(page4, GL_FALSE);
      DestroyPage(page4);
      free(page4);
    }
    break;
    case PAGE_5:
    {
      page5->ShowPage(page5, GL_FALSE);
      DestroyPage(page5);
      free(page5);
    }
    break;
    case PAGE_6:
    {
      page6->ShowPage(page6, GL_FALSE);
      DestroyPage(page6);
      free(page6);
    }
    break;
    case PAGE_7:
    {
      page7->ShowPage(page7, GL_FALSE);
      DestroyPage(page7);
      free(page7);
    }
    break;
    case PAGE_8:
    {
      page8->ShowPage(page8, GL_FALSE);
      DestroyPage(page8);
      free(page8);
    }
    break;
    case PAGE_9:
    {
      page9->ShowPage(page9, GL_FALSE);
      DestroyPage(page9);
      free(page9);
    }
    break;
    default:
      break;
  }

  MENU_DeInit();
  vu8_gPageCurrent = PAGE_HOME;
  pageStart->ShowPage( pageStart, GL_TRUE );
}

/**
  * @brief  This function allows to switch from one page to an other
  * @param  PreviousPage: pointer to the current page
  * @param  PageIndex: Index of the next page
  * @retval None
  */
static void MENU_Settings_SwitchPage(GL_Page_TypeDef* PreviousPage, uint32_t PageIndex)
{
  /* Switch to new page, and free previous one. */
  GL_Page_TypeDef* NextPage = NULL;

  (*PreviousPage).ShowPage(PreviousPage, GL_FALSE);
  DestroyPage(PreviousPage);
  free(PreviousPage);
  PreviousPage = NULL;
  MENU_Settings_Init(PageIndex);
  vu8_gPageCurrent = PageIndex;
  switch (PageIndex)
  {
    case PAGE_0:
      NextPage = page0;
      break;
    case PAGE_1:
      NextPage = page1;
      break;
    case PAGE_2:
      NextPage = page2;
      break;
    case PAGE_3:
      NextPage = page3;
      break;
    case PAGE_4:
      NextPage = page4;
      break;
    case PAGE_5:
      NextPage = page5;
      break;
    case PAGE_6:
      NextPage = page6;
      break;
    case PAGE_7:
      NextPage = page7;
      break;
    case PAGE_8:
      NextPage = page8;
      break;
    case PAGE_9:
      NextPage = page9;
      break;
    default:
      break;
  }
  (*NextPage).ShowPage(NextPage, GL_TRUE);
}

/**
  * @brief  NextFunc
  * @param  None
  * @retval None
  */
static void NextFunc(void)
{
  MENU_Settings_SwitchPage(page0, PAGE_1);
}

/**
  * @brief  NextFunc1
  * @param  None
  * @retval None
  */
static void NextFunc1(void)
{
  MENU_Settings_SwitchPage(page1, PAGE_2);
}

/**
  * @brief  NextFunc2
  * @param  None
  * @retval None
  */
static void NextFunc2(void)
{
  MENU_Settings_SwitchPage(page2, PAGE_3);
}



/**
  * @brief  BackFunc
  * @param  None
  * @retval None
  */
static void BackFunc(void)
{
  MENU_Settings_SwitchPage(page1, PAGE_0);
}

/**
  * @brief  BackFunc1
  * @param  None
  * @retval None
  */
static void BackFunc1(void)
{

  MENU_Settings_SwitchPage(page2, PAGE_1);
}

/**
  * @brief  BackFunc2
  * @param  None
  * @retval None
  */
static void BackFunc2(void)
{
  MENU_Settings_SwitchPage(page3, PAGE_2);
}


/**
  * @brief  NextFunc
  * @param  None
  * @retval None
  */
static void SaveCanAddrFunc(void)
{
  //MENU_Settings_SwitchPage(page0, PAGE_1);
}

/**
  * @brief  Rate_SettingsNodeAddressFunc
  * @param  None
  * @retval None
  */
static void SlidebarNodeAddressFunc(void)
{
  uint8_t* empty_string = "         ";
  /*const uint8_t percentage_suffix[5] =
    {'K', 'm', '/', 'h', 0
    };*/
  uint16_t percentage_value = 0;
  uint8_t percentage_string[4];
  percentage_value = Get_SlidebarValue ( page0, "SlidebarNodeAddress" );
  
  // масштабирование
  percentage_value = percentage_value / 5 + 50;
  if (percentage_value > 69) percentage_value = 69;
  
  cNetAddress = percentage_value;
  sprintf((char*)percentage_string, "%d", percentage_value);
  //strcat ( (char*)percentage_string, (char*)percentage_suffix );
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
  GL_SetTextColor(GL_Blue);
}

/**
  * @brief  Rate_SettingsStartAddressFunc
  * @param  None
  * @retval None
  */
static void SlidebarStartAddressFunc(void)
{
  uint8_t* empty_string = "         ";
  /*const uint8_t percentage_suffix[5] =
    {'K', 'm', '/', 'h', 0
    };*/
  uint16_t percentage_value = 0;
  uint8_t percentage_string[4];
  percentage_value = Get_SlidebarValue ( page2, "SlidebarStartAddress" );
  
  // масштабирование
  percentage_value = percentage_value / 2 + 2;
  if (percentage_value > 49) percentage_value = 49;
  
  cStartNetAddress = percentage_value;
  sprintf((char*)percentage_string, "%d", percentage_value);
  //strcat ( (char*)percentage_string, (char*)percentage_suffix );
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
  GL_SetTextColor(GL_Blue);
}

/**
  * @brief  Rate_SettingsLastAddressFunc
  * @param  None
  * @retval None
  */
static void SlidebarLastAddressFunc(void)
{
  uint8_t* empty_string = "         ";
  /*const uint8_t percentage_suffix[5] =
    {'K', 'm', '/', 'h', 0
    };*/
  uint16_t percentage_value = 0;
  uint8_t percentage_string[4];
  percentage_value = Get_SlidebarValue ( page3, "SlidebarLastAddress" );
  
  // масштабирование
  percentage_value = percentage_value / 2 + 2;
  if (percentage_value > 49) percentage_value = 49;
  
  cLastNetAddress = percentage_value;
  sprintf((char*)percentage_string, "%d", percentage_value);
  //strcat ( (char*)percentage_string, (char*)percentage_suffix );
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 9)*4.2), (uint16_t)((LCD_Width / 9)*5.9), percentage_string, GL_TRUE );
  GL_SetTextColor(GL_Blue);
}

/**
  * @brief  RButtonFunc1
  * @param  None
  * @retval None
  */
static void RButtonRateFunc1(void)
{
  /*uint8_t* empty_string = "                      ";
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), "You've chosen option1 ", GL_TRUE );
  GL_SetTextColor(GL_Blue);*/
}

/**
  * @brief  RButtonFunc2
  * @param  None
  * @retval None
  */
static void RButtonRateFunc2(void)
{
  /*uint8_t* empty_string = "                      ";
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), "You've chosen option2", GL_TRUE );
  GL_SetTextColor(GL_Blue);*/
}

/**
  * @brief  RButtonFunc3
  * @param  None
  * @retval None
  */
static void RButtonRateFunc3(void)
{
  /*uint8_t* empty_string = "                      ";
  GL_SetTextColor(GL_Red);
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), empty_string, GL_FALSE );
  GL_DisplayAdjStringLine( (uint16_t)((LCD_Height / 10)*5.6), (uint16_t)((LCD_Width / 11)*10.9), "You've chosen option3", GL_TRUE );
  GL_SetTextColor(GL_Blue);*/
}


/**
  * @brief  HomeFuncDemo
  * @param  None
  * @retval None
  */
static void HomeFuncDemo(void)
{
  /* check the page to be cleared */
  switch (vu8_gPageCurrent)
  {
    case PAGE_D0:
    {
      pageD0->ShowPage(pageD0, GL_FALSE);
      DestroyPage(pageD0);
      free(pageD0);
    }
    break;
    case PAGE_D1:
    {
      pageD1->ShowPage(pageD1, GL_FALSE);
      DestroyPage(pageD1);
      free(pageD1);
    }
    break;
    case PAGE_D2:
    {
      pageD2->ShowPage(pageD2, GL_FALSE);
      DestroyPage(pageD2);
      free(pageD2);
    }
    break;
    case PAGE_D3:
    {
      pageD3->ShowPage(pageD3, GL_FALSE);
      DestroyPage(pageD3);
      free(pageD3);
    }
    break;
    case PAGE_D4:
    {
      pageD4->ShowPage(pageD4, GL_FALSE);
      DestroyPage(pageD4);
      free(pageD4);
    }
    break;
    case PAGE_D5:
    {
      pageD5->ShowPage(pageD5, GL_FALSE);
      DestroyPage(pageD5);
      free(pageD5);
    }
    break;
    case PAGE_D6:
    {
      pageD6->ShowPage(pageD6, GL_FALSE);
      DestroyPage(pageD6);
      free(pageD6);
    }
    break;
    case PAGE_D7:
    {
      pageD7->ShowPage(pageD7, GL_FALSE);
      DestroyPage(pageD7);
      free(pageD7);
    }
    break;
    default:
      break;
  }
  MENU_DeInit();
  vu8_gPageCurrent = PAGE_HOME;
  pageStart->ShowPage( pageStart, GL_TRUE );
}

/**
  * @brief  This function allows to switch from one page to an other
  * @param  PreviousPage: pointer to the current page
  * @param  PageIndex: Index of the next page
  * @retval None
  */
void MENU_NetWork_SwitchPage(GL_Page_TypeDef* PreviousPage , uint32_t PageIndex)
{
  GL_Page_TypeDef* NextPage = NULL;

  (*PreviousPage).ShowPage(PreviousPage, GL_FALSE);
  DestroyPage(PreviousPage);
  free(PreviousPage);
  PreviousPage = NULL;
  vu8_gPageCurrent = PageIndex;
  MENU_Demo_Init(PageIndex);
  switch (PageIndex)
  {
    case PAGE_D0:
    {
      NextPage = pageD0;
    }
    break;
    case PAGE_D1:
    {
      NextPage = pageD1;
    }
    break;
    case PAGE_D2:
    {
      NextPage = pageD2;
    }
    break;
    case PAGE_D3:
    {
      NextPage = pageD3;
    }
    break;
    case PAGE_D4:
    {
      NextPage = pageD4;
    }
    break;
    case PAGE_D5:
    {
      NextPage = pageD5;
    }
    break;
    case PAGE_D6:
    {
      NextPage = pageD6;
    }
    break;
    case PAGE_D7:
    {
      NextPage = pageD7;
    }
    break;
    default:
      break;
  }
  NextPage->ShowPage(NextPage, GL_TRUE);
}


/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon1DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD0, PAGE_D1);
}

/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon2DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD1, PAGE_D2);
}

/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon3DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD2, PAGE_D3);
}

/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon4DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD3, PAGE_D4);
}

/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon5DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD4, PAGE_D5);
}

/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon6DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD5, PAGE_D6);
}


/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void Icon7DFunc(void)
{
  MENU_NetWork_SwitchPage(pageD6, PAGE_D7);
}


/**
  * @brief  StartDemoFunc
  * @param  None
  * @retval None
  */
static void StartDemoFunc(void)
{
  MENU_NetWork_SwitchPage(pageD0, PAGE_D1);
}

/**
  * @brief  BackFuncD1
  * @param  None
  * @retval None
  */
static void BackFuncD1(void)
{
  MENU_NetWork_SwitchPage(pageD2, PAGE_D1);
}

/**
  * @brief  BackFuncD2
  * @param  None
  * @retval None
  */
static void BackFuncD2(void)
{
  MENU_NetWork_SwitchPage(pageD3, PAGE_D2);
}

/**
  * @brief  BackFuncD3
  * @param  None
  * @retval None
  */
static void BackFuncD3(void)
{
  MENU_NetWork_SwitchPage(pageD4, PAGE_D3);
}

/**
  * @brief  BackFuncD4
  * @param  None
  * @retval None
  */
static void BackFuncD4(void)
{
  MENU_NetWork_SwitchPage(pageD5, PAGE_D4);
}

/**
  * @brief  BackFuncD5
  * @param  None
  * @retval None
  */
static void BackFuncD5(void)
{
  MENU_NetWork_SwitchPage(pageD6, PAGE_D5);
}

/**
  * @brief  NextFuncD1
  * @param  None
  * @retval None
  */
static void NextFuncD1(void)
{
  MENU_NetWork_SwitchPage(pageD1, PAGE_D2);
}

/**
  * @brief  NextFuncD2
  * @param  None
  * @retval None
  */
static void NextFuncD2(void)
{
  MENU_NetWork_SwitchPage(pageD2, PAGE_D3);
}

/**
  * @brief  NextFuncD3
  * @param  None
  * @retval None
  */
static void NextFuncD3(void)
{
  MENU_NetWork_SwitchPage(pageD3, PAGE_D4);
}

/**
  * @brief  NextFuncD4
  * @param  None
  * @retval None
  */
static void NextFuncD4(void)
{
  MENU_NetWork_SwitchPage(pageD4, PAGE_D5);
}

/**
  * @brief  NextFuncD5
  * @param  None
  * @retval None
  */
static void NextFuncD5(void)
{
  MENU_NetWork_SwitchPage(pageD5, PAGE_D6);
}

/**
  * @brief  SwitchDemoBtnFunc
  * @param  None
  * @retval None
  */
static void SwitchDemoBtnFunc(void)
{
  if ( GetObjStatus( pageD1, "SwitchDemoBtn" ) == GL_FALSE )
  {
    stEmployee = GL_FALSE;
  }
  else
  {
    stEmployee = GL_TRUE;
  }
}

/**
  * @brief  RButtonFuncD1
  * @param  None
  * @retval None
  */
static void RButtonFuncD1(void)
{
  user_gender = MAN;
}

/**
  * @brief  RButtonFuncD2
  * @param  None
  * @retval None
  */
static void RButtonFuncD2(void)
{
  user_gender = WOMAN;
}

/**
  * @brief  CheckboxDemoFunc
  * @param  None
  * @retval None
  */
static void CheckboxDemoFunc(void)
{
  if ( GetObjStatus( pageD3, "CheckBoxDemo" ) == GL_FALSE )
  {
    drivingLicense = GL_FALSE;
  }
  else
  {
    drivingLicense = GL_TRUE;
  }
}

/**
  * @brief  ComboboxDemoFunc
  * @param  None
  * @retval None
  */
static void ComboboxDemoFunc(void)
{
  if ( GetComboOptionActive( pageD4, "ComboBoxDemoGrp1" ) == 1 )
  {
    travellers = 1;
  }
  else if ( GetComboOptionActive( pageD4, "ComboBoxDemoGrp1" ) == 2 )
  {
    travellers = 2;
  }
  else if ( GetComboOptionActive( pageD4, "ComboBoxDemoGrp1" ) == 3 )
  {
    travellers = 5;
  }
  else if ( GetComboOptionActive( pageD4, "ComboBoxDemoGrp1" ) == 4 )
  {
    travellers = 6;
  }
}



/**
  * @brief  FinishBtnFunc
  * @param  None
  * @retval None
  */
static void FinishBtnFunc(void)
{
#if !defined(STM32F10X_MD) && !defined(STM32F10X_MD_VL)
  const uint8_t* ptrBitmap = GL_NULL;
#endif
  GL_SetBackColor( GL_White );
  GL_SetTextColor( GL_Blue );

  pageD6->ShowPage(pageD6, GL_FALSE);
  DestroyPage(pageD6);
  free(pageD6);
  MENU_Demo_Init(PAGE_D7);

#if defined(STM32F10X_MD) || defined(STM32F10X_MD_VL)

  if ( favourite_speed > 150 )
  {
    Set_Label(pageD7, "pageLabel_D7c", "Airplane");
  }
  else if ( (travellers == 1 || travellers == 2) && user_gender == MAN )
  {
    Set_Label(pageD7, "pageLabel_D7c", "Motorbike") ;
  }
  else if (travellers == 5 && user_gender == MAN && favourite_speed <= 150 && stEmployee == GL_TRUE && drivingLicense == GL_TRUE)
  {
    Set_Label(pageD7, "pageLabel_D7c", "Car");
  }
  else if ( travellers == 6 || stEmployee == GL_FALSE || drivingLicense == GL_FALSE || user_gender == WOMAN)
  {
    Set_Label(pageD7, "pageLabel_D7c", "Bus") ;
  }
  else
  {
    Set_Label(pageD7, "pageLabel_D7c", "Airplane");
  }

#else /* !defined(STM32F10X_MD) && !defined(STM32F10X_MD_VL) */

  if ( favourite_speed > 150 )
  {
    //ptrBitmap = Airplane;
  }
  else if ( (travellers == 1 || travellers == 2) && user_gender == MAN )
  {
    //ptrBitmap = Motorbike;
  }
  else if (travellers == 5 && user_gender == MAN && favourite_speed <= 150 && stEmployee == GL_TRUE && drivingLicense == GL_TRUE)
  {
    //ptrBitmap = Car;
  }
  else if ( travellers == 6 || stEmployee == GL_FALSE || drivingLicense == GL_FALSE || user_gender == WOMAN)
  {
    //ptrBitmap = Bus;
  }
  else
  {
    //ptrBitmap = Airplane;
  }
  SetIconImage( pageD7, "TransportationIcon", ptrBitmap, 90, 90);
#endif /* defined(STM32F10X_MD) || defined(STM32F10X_MD_VL) */

  vu8_gPageCurrent = PAGE_D7;
  pageD7->ShowPage(pageD7, GL_TRUE);
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
