
#include "WHOLE_LIBRARY.h"



unsigned char CheckVoltageIOInitStatus = 0;
unsigned char CheckVoltageIOStatus = 1;

/******************************************************************************************
  * @brief  检测电压io口初始化
	* @param  无
	* @retval 无
******************************************************************************************/
void CheckVoltageIOInit(void)
{
	
	stc_gpio_cfg_t stcGpioCfg;
  //if(CheckVoltageIOInitStatus == 0)
	if(1)
	{
		CheckVoltageIOInitStatus = 1;
		
		///< 打开GPIO外设时钟门控
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
		
		///< 端口方向配置->输入
		stcGpioCfg.enDir = GpioDirIn;
		///< 端口驱动能力配置->高驱动能力
		stcGpioCfg.enDrv = GpioDrvL;
		///< 端口上下拉配置->无
		stcGpioCfg.enPu = GpioPuDisable;
		stcGpioCfg.enPd = GpioPdDisable;
		///< 端口开漏输出配置->开漏输出关闭
		stcGpioCfg.enOD = GpioOdDisable;
		///< 端口输入/输出值寄存器总线控制模式配置->AHB
		stcGpioCfg.enCtrlMode = GpioAHB;
		///< GPIO IO USER KEY初始化
		Gpio_Init(VOLTAGE_PORT, VOLTAGE_PIN, &stcGpioCfg); 
		
		
		///< 打开并配置USER KEY为下降沿中断
		Gpio_EnableIrq(VOLTAGE_PORT, VOLTAGE_PIN, GpioIrqRising);
		///< 使能端口PORTA系统中断
		EnableNvic(PORTB_IRQn, IrqLevel0, TRUE);
	}
	
}

unsigned char PortB_IRQHandledr[1];

void PortB_IRQHandler(void)//PortB中断服务函数
{
    if(TRUE == Gpio_GetIrqStatus(VOLTAGE_PORT, VOLTAGE_PIN))
    {
      Gpio_ClearIrq(VOLTAGE_PORT, VOLTAGE_PIN);
    }
		

} 

/******************************************************************************************
  * @brief  检测电压io口电平读取
  * @param  无
  * @retval 无
******************************************************************************************/
unsigned char CheckVoltageIO_LEVEL_READ(void)//检测电压io口电平读取
{
	unsigned char CheckVoltageIO_LEVEL_READResult = 0;//检测电压io口电平读取
	if(FALSE != Gpio_GetInputIO(VOLTAGE_PORT, VOLTAGE_PIN))
	{
		CheckVoltageIO_LEVEL_READResult = 1;//检测电压io口电平读取
	}
	else 
	{
		CheckVoltageIO_LEVEL_READResult = 0;//检测电压io口电平读取
	}
	//return 1;//检测电压io口电平读取
	#if DEBUG_MODE == 0//调试模式，0为正常，1为调试模式
	#else
	CheckVoltageIO_LEVEL_READResult = 1;//检测电压io口电平读取
	#endif
	return CheckVoltageIO_LEVEL_READResult;//检测电压io口电平读取
	
}



/******************************************************************************************
  * @brief  识别板电源io口初始化
	* @param  无
	* @retval 无
******************************************************************************************/
void DiscernPowerIOInit(void)//识别板电源io口初始化
{
	stc_gpio_cfg_t stcGpioCfg;
    
	///< 打开GPIO外设时钟门控
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	
	///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
	stcGpioCfg.enDir = GpioDirOut;
	///< 端口上下拉配置->下拉
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	
	
	stcGpioCfg.enDrv = GpioDrvL;
	stcGpioCfg.enOD = GpioOdDisable;
	stcGpioCfg.enCtrlMode = GpioFastIO;
	///< GPIO IO端口初始化
	Gpio_Init(DISCERN_POWER_PORT, DISCERN_POWER_PIN, &stcGpioCfg);
	
}




/******************************************************************************************
  * @brief  识别板电源控制
	* @param  无
	* @retval 无
******************************************************************************************/
void DiscernPowerControl(unsigned char IO_Level)//识别板电源控制
{
	DiscernPowerIOInit();//识别板电源io口初始化
  if(IO_Level == 1)
	{
		Gpio_SetIO(DISCERN_POWER_PORT, DISCERN_POWER_PIN);
	}
	else
	{
		Gpio_ClrIO(DISCERN_POWER_PORT, DISCERN_POWER_PIN);
	}
}




///******************************************************************************************
//  * @brief  识别板电源闪烁
//	* @param  无
//	* @retval 无
//******************************************************************************************/
//void DiscernPowerJump(void)//识别板电源闪烁
//{
//	unsigned char DiscernPowerJumpNum[1];
//	for(DiscernPowerJumpNum[0]=0;DiscernPowerJumpNum[0]<20;DiscernPowerJumpNum[0]++)
//	{
//		LEDOnOrOff(0xFF,1);//LED灯控制亮灭
//		DiscernPowerControl(1);//识别板电源控制
//		Delay_ms(100);//延时ms
//		LEDOnOrOff(0xFF,0);//LED灯控制亮灭
//		DiscernPowerControl(0);//识别板电源控制
//		Delay_ms(100);//延时ms
//		WatchDogFeed(1);//看门狗喂狗
//	}
//	
//}


///******************************************************************************************
//  * @brief  识别板重新启动
//	* @param  无
//	* @retval 无
//******************************************************************************************/
//void DiscernResetBoot(void)//识别板重新启动
//{
//	unsigned char DiscernResetBootNum[1];
//	
//	StartUpAllMcuIoInit();//上电所有MCU io 口初始化
//	DiscernPowerControl(1);//识别板电源控制
//}















void PortC_IRQHandler(void)//PortC中断服务函数
{
    
} 



/******************************************************************************************
  * @brief  低功耗模式配置
	* @param  Mode：0为运行模式，1为休眠模式，2为深度休眠模式
	* @retval 无
******************************************************************************************/
void LowPowerModeConfig(unsigned char Mode)//低功耗模式配置
{
	
	stc_gpio_cfg_t stcGpioCfg;
	StartUpAllMcuIoInit();//上电所有MCU io 口初始化
	INTX_ENABLE();//开启所有中断
	DiscernPowerControl(0);//识别板电源控制
	CheckVoltageIOInit();//检测电压io口初始化
	
	///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
	stcGpioCfg.enDir = GpioDirIn;
	///< 端口上下拉配置->下拉
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	stcGpioCfg.enDrv = GpioDrvH;
	stcGpioCfg.enOD = GpioOdDisable;
	stcGpioCfg.enCtrlMode = GpioFastIO;
	
	///< GPIO IO LED端口初始化
	Gpio_Init(LED0_PORT, LED0_PIN, &stcGpioCfg);
	Gpio_ClrIO(LED0_PORT, LED0_PIN);  
	
	///< GPIO IO LED端口初始化
	Gpio_Init(LED1_PORT, LED1_PIN, &stcGpioCfg);
	Gpio_ClrIO(LED1_PORT, LED1_PIN);
	
	///< 端口方向配置->输出
	stcGpioCfg.enDir = GpioDirIn;
	///< 端口驱动能力配置->高驱动能力
	stcGpioCfg.enDrv = GpioDrvH;
	///< 端口上下拉配置->上拉
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	///< 端口开漏输出配置->开漏输出关闭
	stcGpioCfg.enOD = GpioOdDisable;
	///< 端口输入/输出值寄存器总线控制模式配置->AHB
	stcGpioCfg.enCtrlMode = GpioAHB;
	///< GPIO IO初始化
	Gpio_Init(LT8900_POWER_PORT, LT8900_POWER_PIN, &stcGpioCfg); 
	Gpio_ClrIO(LT8900_POWER_PORT, LT8900_POWER_PIN);
	
	
	USART2Init(0xF0);//串口2初始化
	if(Mode == 1)
	{
		
	}
	else if(Mode == 2)
	{
//		///< 打开GPIO外设时钟门控
//    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

//    //swd as gpio
//    Sysctrl_SetFunc(SysctrlSWDUseIOEn, TRUE);

//    ///< 配置为数字端口
//    M0P_GPIO->PAADS = 0;
//    M0P_GPIO->PBADS = 0;
//    M0P_GPIO->PCADS = 0;
//    M0P_GPIO->PDADS = 0;

//    ///< 配置为端口输入
//    M0P_GPIO->PADIR = 0XFFFF;
//    M0P_GPIO->PBDIR = 0XFFFF;
//    M0P_GPIO->PCDIR = 0XFFFF;
//    M0P_GPIO->PDDIR = 0XFFFF;

//    ///< 输入下拉
//    M0P_GPIO->PAPD = 0xFFFF;
//    M0P_GPIO->PBPD = 0xFFFF;
//    M0P_GPIO->PCPD = 0xFFFF;
//    M0P_GPIO->PDPD = 0xFFFF;


//		stc_lptim_cfg_t    stcLptCfg;
//    DDL_ZERO_STRUCT(stcLptCfg);

//    ///< 使能LPTIM0 外设时钟
//    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, TRUE);

//    stcLptCfg.enGate   = LptimGateLow;
//    stcLptCfg.enGatep  = LptimGatePLow;
//    stcLptCfg.enTcksel = LptimRcl;
//    stcLptCfg.enTogen  = LptimTogEnLow;
//    stcLptCfg.enCt     = LptimCntFun;           //计数器功能
//    stcLptCfg.enMd     = LptimMode2;            //工作模式为模式2：自动重装载16位计数器/定时器
//    stcLptCfg.u16Arr   = 65530;                 //预装载寄存器值，计数初值
//    Lptim_Init(M0P_LPTIMER, &stcLptCfg);

//    Lptim_ClrItStatus(M0P_LPTIMER);            //清除中断标志位
//    Lptim_ConfIt(M0P_LPTIMER, TRUE);           //允许LPTIMER中断
//    EnableNvic(LPTIM_IRQn, IrqLevel3, TRUE);
//		Lptim_Cmd(M0P_LPTIMER, TRUE);   ///< 启动lptimer0运行
//		while(1)
//		{
//			WatchDogFeed(42);//看门狗喂狗
//		}
	
			Lpm_GotoDeepSleep(FALSE);///< 进入深度睡眠模式，使能退出中断服务后再次进入休眠特性
	}
	
}

/**
 ******************************************************************************
 ** \brief  LPTIMER中断服务函数
 **
 ** \return 无
 ******************************************************************************/
void LpTim_IRQHandler(void)//LPTIMER中断服务函数
{
    if (TRUE == Lptim_GetItStatus(M0P_LPTIMER))
    {
        Lptim_ClrItStatus(M0P_LPTIMER);//清除LPTIMER的中断标志位
				if(CheckVoltageIO_LEVEL_READ() != 0)//检测电压io口电平读取
				{//说明有高电压过来了，此时直接复位单片机
					MCURestart();//MCU重启
				}
    }
}
