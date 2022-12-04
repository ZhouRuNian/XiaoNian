#include "WHOLE_LIBRARY.h"

#if BOARD_TYPE == 1//板子类型，0为双模板，1为有线板
//外部看门狗管脚定义
#define IWDG_EM6323_PORT        GpioPortA
#define IWDG_EM6323_PIN         GpioPin7
#else
//外部看门狗管脚定义
#define IWDG_EM6323_PORT        GpioPortA
#define IWDG_EM6323_PIN         GpioPin8
#endif



/**
 ******************************************************************************
 ** \brief  WDT复位及启动函数
 **
 ** \param [in] 无
 **
 ** \retval 无
 **
 ******************************************************************************/
void Wdt_Start(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
 ******************************************************************************
 ** \brief  WDT喂狗
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_Feed(void)//WDT喂狗
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
	
//		Gpio_ClrIO(IWDG_EM6323_PORT, IWDG_EM6323_PIN); 
//		Delay_us(1000);//延时us
//		Gpio_SetIO(IWDG_EM6323_PORT, IWDG_EM6323_PIN);
}


/******************************************************************************************
  * @brief  看门狗喂狗
	* @param  无
	* @retval 无
******************************************************************************************/
void WatchDogFeed(unsigned char FeedFjlag)//看门狗喂狗
{
	Wdt_Feed();   // 喂狗
}

/**
 ******************************************************************************
 ** \brief  WDT中断标志清除
 **
 ** \param [in] 无
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_IrqClr(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/******************************************************************************************
  * @brief  看门狗初始化
	* @param  无
	* @retval 无
******************************************************************************************/
void WatchDogInit(void)//看门狗初始化
{
	#if IWDG_SWITCH==1//看门狗开关，0为关闭看门狗，1为开启看门狗
	SetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN)), SysctrlPeripheralWdt, TRUE);
	M0P_WDT->CON_f.WOV = WdtT3s28;
	//M0P_WDT->CON_f.WINT_EN = WdtResetEn;
	M0P_WDT->CON_f.WINT_EN = WdtIntEn;
	EnableNvic(WDT_IRQn, IrqLevel3, TRUE);
	///< 启动 WDT
	Wdt_Start();
	#endif
}


void Wdt_IRQHandler(void)///< WDT 中断服务程序
{
	if((M0P_WDT->CON&0x80u))
	{
			Wdt_IrqClr();       ///<清除 wdt 中断标记

			MCURestart();//MCU重启
	}
}
