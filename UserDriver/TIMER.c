#include "WHOLE_LIBRARY.h"

unsigned int Timer0Count[2];//定时器0计数

/******************************************************************************************
  * @brief  定时器0初始化
	* @param  无
	* @retval 无
******************************************************************************************/
void Timer0Init(void)//定时器0初始化
{
	uint16_t                  u16ArrValue;
	uint16_t                  u16CntValue;
	
	unsigned int Timer0Period = 0;
	
	//Timer0配置初始化(周期 = Timer0Period*(1/48M)*256 = 10ms)
	
	stc_bt_mode0_cfg_t     stcBtBaseCfg;
	SystemCoreClockUpdate();//更新系统频率值
	
	DDL_ZERO_STRUCT(stcBtBaseCfg);
	Timer0Period = 30000;
	
	Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); //Base Timer外设时钟使能
	
	stcBtBaseCfg.enWorkMode = BtWorkMode0;                  //定时器模式
	stcBtBaseCfg.enCT       = BtTimer;                      //定时器功能，计数时钟为内部PCLK
	stcBtBaseCfg.enPRS      = BtPCLKDiv16;                 //PCLK/256
	stcBtBaseCfg.enCntMode  = Bt16bitArrMode;               //自动重载16位计数器/定时器
	stcBtBaseCfg.bEnTog     = FALSE;
	stcBtBaseCfg.bEnGate    = FALSE;
	stcBtBaseCfg.enGateP    = BtGatePositive;
	Bt_Mode0_Init(TIM0, &stcBtBaseCfg);                     //TIM0 的模式0功能初始化
	
	Bt_M0_ARRSet(TIM0, (0x10000 - Timer0Period));                        //设置重载值(ARR = 0x10000 - 周期)
	Bt_M0_Cnt16Set(TIM0, (0x10000 - Timer0Period));                      //设置计数初值
	
	
	
	Bt_ClearIntFlag(TIM0,BtUevIrq);                         //清中断标志   
	Bt_Mode0_EnableIrq(TIM0);                               //使能TIM0中断(模式0时只有一个中断)
	EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);                 //TIM0中断使能
	
	Bt_M0_Run(TIM0);        //TIM0 运行。
}



void Tim0_IRQHandler(void)//TIM0中断服务函数
{//10ms进入1次中断
	
	//Timer0 模式0 溢出中断
	if(TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))
	{
		
		//USART0_TX_DMA_AutoClrStat();//串口0发送DMA自动清除状态
		if(++Timer0Count[1] >= 5)
		{//进入这里1次
			
			Timer0Count[1] = 0;
			if(McuWorkInfo.Upgrade.UpgradeDeviceStatus == 0)//升级状态，0为正常，1为正在升级
			{
				LEDAutoJump(0xFF);//LED灯自动闪烁
			}
		}
		
		if(++Timer0Count[0] >= 10)
		{//100ms进入这里1次
			
			Timer0Count[0] = 0;
			if(McuWorkInfo.Upgrade.UpgradeDeviceStatus == 0)//升级状态，0为正常，1为正在升级
			{
				McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//升级等待计时
				if(++McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] >= 150)//升级等待计时
				{
					McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//升级等待计时//升级超时自动退出升级状态
					iap_load_app_status=0;//跳转到应用状态，0为需要跳转，1为禁止跳转
				}
			}
			else
			{
				McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//升级等待计时
				if(++McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] >= 100)//升级等待计时
				{
					McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//升级等待计时//升级超时自动退出升级状态
					McuWorkInfo.Upgrade.UpgradeDeviceStatus = 0;//升级状态，0为正常，1为正在升级
				}
			}
			
			if(++McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] >= 100)//自动初始化串口计时
			{
				McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 250;//自动初始化串口计时
			}															
			if((McuConfigInfo.DeviceInfo.CurrentReaderPosi <= 0) || (McuConfigInfo.DeviceInfo.CurrentReaderPosi >= 5))//当前通讯读头方位
			{
				McuConfigInfo.DeviceInfo.CurrentReaderPosi = 1;//当前通讯读头方位
			}
		}
		
		if(++McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[0] >= 10)//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
		{
			McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[0] = 0;//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
			if(++McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] >= 20)//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
			{
				McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] = 250;//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
			}
		}
		if(++McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] >= 50)//延时清空串口接收缓冲区
		{
			McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 250;//延时清空串口接收缓冲区
		}
		
		Bt_ClearIntFlag(TIM0,BtUevIrq); //中断标志清零
	}
}
