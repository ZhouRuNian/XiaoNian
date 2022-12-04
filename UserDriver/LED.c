#include "WHOLE_LIBRARY.h"


unsigned char LEDIOInitStatus = 0;
unsigned char LEDAutoJumpStatus[3];//LED灯自动闪烁状态
unsigned char LEDAutoLampStatus[3];//
/******************************************************************************************
  * @brief  LED IO口初始化
	* @param  无
	* @retval 无
******************************************************************************************/
void LEDIOInit(void)//LED IO口初始化
{
	stc_gpio_cfg_t stcGpioCfg;
  if(LEDIOInitStatus == 0)
	//if(1)
	{
		LEDIOInitStatus = 1;
		///< 打开GPIO外设时钟门控
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
		
		///< 端口方向配置->输出(其它参数与以上（输入）配置参数一致)
		stcGpioCfg.enDir = GpioDirOut;
		///< 端口上下拉配置->下拉
		stcGpioCfg.enPu = GpioPuEnable;
		stcGpioCfg.enPd = GpioPdDisable;
		stcGpioCfg.enDrv = GpioDrvH;
		stcGpioCfg.enOD = GpioOdDisable;
		stcGpioCfg.enCtrlMode = GpioFastIO;
		
		///< GPIO IO LED端口初始化
		Gpio_Init(LED0_PORT, LED0_PIN, &stcGpioCfg);
		Gpio_ClrIO(LED0_PORT, LED0_PIN);  
		
		///< GPIO IO LED端口初始化
		Gpio_Init(LED1_PORT, LED1_PIN, &stcGpioCfg);
		Gpio_ClrIO(LED1_PORT, LED1_PIN);  
	}
	
}

/******************************************************************************************
  * @brief  LED灯控制亮灭
	* @param  OnOrOffStatus：开关状态，0为灭灯，1为亮灯
	* @retval 无
******************************************************************************************/
void LEDOnOrOff(unsigned char LEDx,unsigned char OnOrOffStatus)//LED灯控制亮灭
{
	#if TEST_LED_SWITCH==1//测试LED开关，0为关闭，1为开启
	LEDIOInit();//LED IO口初始化
	switch(LEDx)
	{
		case 0:
						if(OnOrOffStatus==1)//开关状态，0为灭灯，1为亮灯
						{
							///< LED点亮
							Gpio_SetIO(LED0_PORT, LED0_PIN);
						}
						else
						{
							///< LED关闭
							Gpio_ClrIO(LED0_PORT, LED0_PIN);  
						}
						break;
		case 1:
						if(OnOrOffStatus==1)//开关状态，0为灭灯，1为亮灯
						{
							///< LED点亮
							Gpio_SetIO(LED1_PORT, LED1_PIN);
						}
						else
						{
							///< LED关闭
							Gpio_ClrIO(LED1_PORT, LED1_PIN);  
						}
						break;
		case 2:
		case 3:
		case 0xFF:
						if(OnOrOffStatus==1)//开关状态，0为灭灯，1为亮灯
						{
							///< LED点亮
							Gpio_SetIO(LED0_PORT, LED0_PIN);
							Gpio_SetIO(LED1_PORT, LED1_PIN);
						}
						else
						{
							///< LED关闭
							Gpio_ClrIO(LED0_PORT, LED0_PIN); 
							Gpio_ClrIO(LED1_PORT, LED1_PIN);  
						}
						break;
		default:break;
	}
	
	#endif
}


/******************************************************************************************
  * @brief  LED灯自动闪烁
	* @param  无
	* @retval 无
******************************************************************************************/
void LEDAutoJump(unsigned char LEDx)//LED灯自动闪烁
{
	//范围限制
	if(LEDx >= 3)
	{
		LEDx = 2;
	}
	#if TEST_LED_SWITCH==1//测试LED开关，0为关闭，1为开启
	if(LEDAutoJumpStatus[LEDx]==0)//LED灯自动闪烁状态
	{
		LEDOnOrOff(LEDx,1);//LED灯控制亮灭
		LEDAutoJumpStatus[LEDx]=1;//LED灯自动闪烁状态
	}
	else
	{
		LEDOnOrOff(LEDx,0);//LED灯控制亮灭
		LEDAutoJumpStatus[LEDx]=0;//LED灯自动闪烁状态
	}
	#endif
}


/******************************************************************************************
  * @brief  LED灯自动流水灯
	* @param  无
	* @retval 无
******************************************************************************************/
void LEDAutoLamp(unsigned char LampType)//LED灯自动流水灯
{
	if(++LEDAutoLampStatus[0] >= 8)
	{
		LEDAutoLampStatus[0] = 0;
	}
	if(LEDAutoLampStatus[0] == 0)
	{
		LEDOnOrOff(0,0);//LED灯控制亮灭
		LEDOnOrOff(1,0);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 1)
	{
		LEDOnOrOff(0,1);//LED灯控制亮灭
		LEDOnOrOff(1,0);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 2)
	{
		LEDOnOrOff(0,1);//LED灯控制亮灭
		LEDOnOrOff(1,1);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 3)
	{
		LEDOnOrOff(0,0);//LED灯控制亮灭
		LEDOnOrOff(1,1);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 4)
	{
		LEDOnOrOff(0,0);//LED灯控制亮灭
		LEDOnOrOff(1,0);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 5)
	{
		LEDOnOrOff(0,0);//LED灯控制亮灭
		LEDOnOrOff(1,1);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 6)
	{
		LEDOnOrOff(0,1);//LED灯控制亮灭
		LEDOnOrOff(1,1);//LED灯控制亮灭
	}
	else if(LEDAutoLampStatus[0] == 7)
	{
		LEDOnOrOff(0,1);//LED灯控制亮灭
		LEDOnOrOff(1,0);//LED灯控制亮灭
	}
}
