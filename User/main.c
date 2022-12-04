/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2017-05-28 LiuHL    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "WHOLE_LIBRARY.h"
#include "adc.h"
#include "gpio.h"
#include "bgr.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
unsigned char ErrorFlag=0;//错误标记



const char MCU_CONFIG_INFO_SYNC[MCU_CONFIG_INFO_SYNC_MAX]="McuConfigInfo";//McuConfigInfo同步头
const char LT8900SyncSend[7]="Reader";//LT8900同步头（发送）
const char K30VSyncSend[7]="Vision";//K30V同步头（发送）
const char K30VSyncReveive[7]="LT8900";//K30V同步头(接收)

MCU_WORK_INFO McuWorkInfo;//MCU工作信息
MCU_CONFIG_INFO McuConfigInfo;//MCU配置信息


unsigned char iap_load_app_status=0;//跳转到应用状态，0为需要跳转，1为禁止跳转
/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 


#define RC_TRIM_BASE_ADDR           ((volatile uint16_t*) (0x00100C00ul))
#define RCH_CR_TRIM_24M_VAL         (*((volatile uint16_t*) (0x00100C00ul)))
#define RCH_CR_TRIM_22_12M_VAL      (*((volatile uint16_t*) (0x00100C02ul)))
#define RCH_CR_TRIM_16M_VAL         (*((volatile uint16_t*) (0x00100C04ul)))
#define RCH_CR_TRIM_8M_VAL          (*((volatile uint16_t*) (0x00100C06ul)))
#define RCH_CR_TRIM_4M_VAL          (*((volatile uint16_t*) (0x00100C08ul)))
	
void _SysctrlUnlock(void)
{
    M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
    M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
}
/******************************************************************************************
  * @brief  系统时钟设置
  * @param  无
  * @retval 无
******************************************************************************************/
void SetSysClockConfig(void)//系统时钟设置
{
	unsigned char temp=0;   
	
//	stc_sysctrl_clk_cfg_t stcCfg;
//	
	///< 开启FLASH外设时钟
	Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);

	
	en_flash_waitcycle_t      enWaitCycle;
	stc_sysctrl_pll_cfg_t     stcPLLCfg;
	
	//结构体初始化清零
	DDL_ZERO_STRUCT(stcPLLCfg);
	
	enWaitCycle = FlashWaitCycle1;
	Flash_WaitCycle(enWaitCycle);
	
	stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
	stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL 输出48MHz
	stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //输入时钟源选择RCH
	stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
	Sysctrl_SetPLLFreq(&stcPLLCfg);
	Sysctrl_SetPLLStableTime(SysctrlPllStableCycle16384);
	Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
	
	Sysctrl_SysClkSwitch(SysctrlClkPLL);  ///< 时钟切换//使能RCL
  //Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
	
}	


/******************************************************************************************
  * @brief  上电所有MCU io 口初始化
  * @param  无
  * @retval 无
******************************************************************************************/
void StartUpAllMcuIoInit(void)//上电所有MCU io 口初始化
{
	unsigned char StartUpAllMcuIoInitNum[1];
	stc_gpio_cfg_t stcGpioCfg;
	Bt_M0_Stop(TIM0);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTick, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralDma, FALSE); 
	
	
	
	///< 打开GPIO外设时钟门控
	//Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	///< 端口方向配置->输入
	stcGpioCfg.enDir = GpioDirIn;
	///< 端口上下拉配置->下拉
	stcGpioCfg.enPu = GpioPuEnable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	stcGpioCfg.enDrv = GpioDrvL;//低驱动能力 
	stcGpioCfg.enOD = GpioOdDisable;//开漏输出关闭
	stcGpioCfg.enCtrlMode = GpioFastIO;
	
	///< GPIO IO 端口初始化
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortA, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortB, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortC, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
//	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
//	{
//		Gpio_Init(GpioPortD, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
//	}
	
	
	
	
	
	
}




extern unsigned char CheckVoltageIOStatus;
unsigned char CurrentChannelTemp = 18;
unsigned char MainNum[3];

/******************************************************************************************
  * @brief  上电初始化
  * @param  无
  * @retval 无
******************************************************************************************/
void StartUpInit(void)//上电初始化
{
  volatile uint32_t u32Val = 0;
	unsigned int StartUpInitNum[2]={0,0};
	unsigned char StartUpDormancyDelay[2]={0,0};//上电延时休眠
	DiscernPowerControl(1);//识别板电源控制
	
	
	INTX_ENABLE();//开启所有中断
	CheckVoltageIOInit();//检测电压io口初始化
	
	while(CheckVoltageIO_LEVEL_READ() == 0)//检测电压io口电平读取
	{//到这里说明是没有高电压过来，准备进入休眠
		for(MainNum[0]=0;MainNum[0]<20;MainNum[0]++)
		{
			WatchDogFeed(9);//看门狗喂狗
			LEDAutoJump(0xFF);//LED灯自动闪烁
			Delay_ms(10);//延时ms
		}
		#if SLEEP_MODE_SWITCH == 1//睡眠模式开关，0为关闭，1为开启
		LowPowerModeConfig(2);//低功耗模式配置
		//被唤醒了，等一下，再判断是不是高电压来了
		//Delay_ms(10);//延时ms
		#endif
		WatchDogFeed(8);//看门狗喂狗
		MCURestart();//MCU重启
	}
	
	SetSysClockConfig();//系统时钟设置
	WatchDogInit();//看门狗初始化
	EepromInit();//eeprom初始化
	EepromReadImportantInfo();//EEPROM读取重要信息
	
	if(McuConfigInfo.StartOverCount != 0)//启动次数，用于标记固件启动次数
	{
		for(MainNum[0]=0;MainNum[0]<20;MainNum[0]++)
		{
			WatchDogFeed(9);//看门狗喂狗
			LEDOnOrOff(0,1);//LED灯控制亮灭
			LEDOnOrOff(1,1);//LED灯控制亮灭
			Delay_ms(30);//延时ms
		}
		for(MainNum[0]=0;MainNum[0]<50;MainNum[0]++)
		{
			WatchDogFeed(9);//看门狗喂狗
			LEDAutoJump(0xFF);//LED灯自动闪烁
			Delay_ms(30);//延时ms
		}
	}
	if(McuConfigInfo.StartOverCount++ >= 3)//启动次数，用于标记固件启动次数
	{//这个值要在主程序中清零，如果累加到一定次数，说明进入主程序失败，此时需要重新升级主程序
		McuConfigInfo.StartOverCount = 250;//启动次数，用于标记固件启动次数
		McuConfigInfo.UpgradeStatus = 1;//升级状态，0为正常状态，1为需要升级状态
	}
	
	
	if(McuConfigInfo.UpgradeStatus == 1)//升级状态，0为正常状态，1为需要升级状态
	{//需要升级的，就不重启识别板了
		iap_load_app_status=1;//跳转到应用状态，0为需要跳转，1为禁止跳转
		DiscernPowerControl(1);//识别板电源控制
	}
	else
	{
		
		USART2Init(0xF0);//串口2初始化
		DiscernPowerControl(0);//识别板电源控制
		Delay_ms(100);//延时ms
		DiscernPowerControl(1);//识别板电源控制
	}
	
	Timer0Init();//定时器0初始化
	//USART1Init(0);//串口1初始化
	USART2Init(0);//串口2初始化
	
	
	
	McuWorkInfo.CurrentStatus.MCUResetStatus = 0;//MCU复位状态，0为正常状态，1为需要复位状态
	McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU复位倒计时
	McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU复位倒计时
	
	McuWorkInfo.Upgrade.UpgradeDeviceStatus = 0;//升级状态，0为正常，1为正在升级
	
	INTX_ENABLE();//开启所有中断
}

/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/

int32_t main(void)
{

	StartUpInit();//上电初始化
	
	while(1)
	{
		if(iap_load_app_status==0)//跳转到应用状态，0为需要跳转，1为禁止跳转
		{
			EepromSaveImportantInfo();//EEPROM存储重要信息
			Wdt_Feed();// 喂狗
			StartUpAllMcuIoInit();//上电所有MCU io 口初始化
			INTX_DISABLE();//关闭所有中断(但是不包括fault和NMI中断)
			iap_load_app(FLASH_APP1_ADDR);//跳转到应用
			//iap_load_app_status=1;//跳转到应用状态，0为需要跳转，1为禁止跳转
			StartUpInit();//上电初始化
			INTX_ENABLE();//开启所有中断
			MCURestart();//MCU重启
		}
		Wdt_Feed();   // 喂狗
		UARTMainDeal();//UART主处理函数
	}
}



/******************************************************************************************
  * @brief  MCU重启自动处理
  * @param  无
  * @retval 无
******************************************************************************************/
void MCUAutoRestartDeal(unsigned char DealCount)//MCU重启自动处理
{
//	if(McuWorkInfo.CurrentStatus.MCUResetStatus != 0)//MCU复位状态，0为正常状态，1为需要复位状态
//	{
//		if(McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0]++ >= DealCount)//MCU复位倒计时
//		{
//			McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU复位倒计时
//			if(McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1]++ >= 5)//MCU复位倒计时
//			{
//				McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU复位倒计时
//				
//				MCURestart();//MCU重启
//			}
//		}
//	}
}


/******************************************************************************************
  * @brief  MCU重启
  * @param  无
  * @retval 无
******************************************************************************************/
void MCURestart(void)//MCU重启
{
	unsigned char MCURestartStatus = 0;
	#if DEBUG_MODE == 0//调试模式，0为正常，1为调试模式
	if(MCURestartStatus == 0)
	{
		NVIC_SystemReset();//复位
	}
	
	#else
	
	#endif
}



/******************************************************************************************
  * @brief  恢复出厂设置
	* @param  无
	* @retval 无
******************************************************************************************/
//void RestoreFactorySettings(void)//恢复出厂设置
//{
//	
//}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
