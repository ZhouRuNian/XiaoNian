#include "WHOLE_LIBRARY.h"



unsigned char UARRT1_SendByteStatus = 1;//发送单字节完成状态，0为正常，1为发送完成
///******************************************************************************************
//  * @brief  串口1初始化
//  * @param  BaudRate：波特率
//            StopBits：停止位
//  * @retval 无
//******************************************************************************************/
//void USART1Init(unsigned char InitType)//串口1初始化
//{
//	
//	stc_gpio_cfg_t stcGpioCfg;
//	stc_uart_cfg_t    stcCfg;

//	DDL_ZERO_STRUCT(stcGpioCfg);

//	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //使能GPIO模块时钟

//	///<TX
//	stcGpioCfg.enDir = GpioDirOut;
//	Gpio_Init(GpioPortD, GpioPin0, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortD, GpioPin0, GpioAf3);          //配置PD00 端口为URART1_TX

//	///<RX
//	stcGpioCfg.enDir = GpioDirIn;
//	Gpio_Init(GpioPortD, GpioPin1, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortD, GpioPin1, GpioAf3);          //配置PD01 端口为URART1_RX
//	

//	DDL_ZERO_STRUCT(stcCfg);

//	///< 开启外设时钟
//	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1,TRUE);///<使能uart1模块时钟

//	///<UART Init
//	stcCfg.enRunMode        = UartMskMode1;          //模式
//	stcCfg.enStopBit        = UartMsk1bit;           //1bit停止位
//	stcCfg.enMmdorCk        = UartMskEven;           //偶检验
//	stcCfg.stcBaud.u32Baud  = 115200;                //波特率
//	stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<通道采样分频配置
//	stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<获得外设时钟（PCLK）频率值
//	Uart_Init(M0P_UART1, &stcCfg);                   ///<串口初始化

//	///<UART中断使能
//	Uart_ClrStatus(M0P_UART1,UartRC);                ///<清接收请求
//	Uart_ClrStatus(M0P_UART1,UartTC);                ///<清接收请求
//	Uart_EnableIrq(M0P_UART1,UartRxIrq);             ///<使能串口接收中断
//	Uart_EnableIrq(M0P_UART1,UartTxIrq);             ///<使能串口发送中断
//	EnableNvic(UART1_IRQn, IrqLevel3, TRUE);       ///<系统中断使能
//	    
//	
//	if(InitType == 0)
//	{
//		DDL_ZERO_STRUCT(stcGpioCfg);
//		
//		///< 端口方向配置->输入
//		stcGpioCfg.enDir = GpioDirIn;
//		///< 端口驱动能力配置->高驱动能力
//		stcGpioCfg.enDrv = GpioDrvL;
//		///< 端口上下拉配置->无
//		stcGpioCfg.enPu = GpioPuDisable;
//		stcGpioCfg.enPd = GpioPdDisable;
//		///< 端口开漏输出配置->开漏输出关闭
//		stcGpioCfg.enOD = GpioOdDisable;
//		///< 端口输入/输出值寄存器总线控制模式配置->AHB
//		stcGpioCfg.enCtrlMode = GpioAHB;
//		///< GPIO IO USER KEY初始化
//		Gpio_Init(GpioPortD, GpioPin0, &stcGpioCfg); 
//	}
//}





///******************************************************************************************
//  * @brief  发送单个数据
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void USART1SendByte(unsigned char Byte)//发送单个数据
//{ 
//	unsigned char USART1SendByteWaitCount[2] = {0,0};
//	while(UARRT1_SendByteStatus == 0)//发送单字节完成状态，0为正常，1为发送完成
//	{
//		if(USART1SendByteWaitCount[0]++ >= 100)
//		{
//			USART1SendByteWaitCount[0] = 0;
//			if(USART1SendByteWaitCount[1]++ >= 100)
//			{
//				USART1SendByteWaitCount[1] = 0;
//				break;
//			}
//		}
//	}
//	UARRT1_SendByteStatus = 0;//发送单字节完成状态，0为正常，1为发送完成
//	Uart_SendDataIt(M0P_UART1,Byte); //启动UART0发送第一个字节
//}


///******************************************************************************************
//  * @brief  串口发送转发数据
//  * @param  *LT8900SendBuf：发送缓冲区
//  * @retval 无
//******************************************************************************************/
//void USART1ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen)//串口发送转发数据
//{
//	unsigned int USART1ForWordSendDataNum[2];
//	unsigned int USART1ForWordSendDataCount = 0;
//	USART1Init(1);//串口1初始化
//	Delay_ms(1);//延时ms
//	for(USART1ForWordSendDataNum[1]=0;USART1ForWordSendDataNum[1]<1;USART1ForWordSendDataNum[1]++)
//	{
//		for(USART1ForWordSendDataNum[0]=0;USART1ForWordSendDataNum[0]<USART1SendBufLen;USART1ForWordSendDataNum[0]++)
//		{
//			USART1SendByte(USART1SendBuf[USART1ForWordSendDataNum[0]]);//发送单个数据
//			Delay_us(50);//延时us
//		}
//		Delay_ms(1);//延时ms
//	}
//	Delay_ms(5);//延时ms
//	USART1Init(0);//串口1初始化
//}

///******************************************************************************************
//  * @brief  清空UART1接收缓冲区
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void EmptyUART1ReceiveBuf(void)//清空UART1接收缓冲区
//{
//	unsigned char EmptyUART1ReceiveBufNum[1];
//	//清空UART1接收缓冲区
//	for(EmptyUART1ReceiveBufNum[0]=0;EmptyUART1ReceiveBufNum[0]<UART1_RECEIVE_BUF_NUM_MAX;EmptyUART1ReceiveBufNum[0]++)
//	{
//		McuWorkInfo.Uart1Info.UART1ReceiveBuf[EmptyUART1ReceiveBufNum[0]] = 0;//UART1接收缓冲区
//	}
//	McuWorkInfo.Uart1Info.UART1ReceiveBufNum = 0;//UART1接收缓冲区下标号
//	
//}

///******************************************************************************************
//	* @brief  清空UART1发送缓冲区
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void EmptyUART1SendBuf(void)//清空UART1发送缓冲区
//{
//	unsigned char EmptyUART1SendBufNum[1];
//	//清空UART1发送缓冲区
//	for(EmptyUART1SendBufNum[0]=0;EmptyUART1SendBufNum[0]<UART1_SEND_BUF_NUM_MAX;EmptyUART1SendBufNum[0]++)
//	{
//		McuWorkInfo.Uart1Info.UART1SendBuf[EmptyUART1SendBufNum[0]] = 0;//UART1发送缓冲区
//	}
//	McuWorkInfo.Uart1Info.UART1SendBufNum = 0;//UART1发送缓冲区下标号
//	
//}


///******************************************************************************************
//  * @brief  自动清空UART1接收缓冲区
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void AutoEmptyUART1ReceiveBuf(void)//自动清空UART1接收缓冲区
//{
//	unsigned char EmptyUART1ReceiveBufNum[1];
//	//自动清空串口数据缓冲区，有时候接收到的数据无法通过校验，则丢弃
//	if(McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] >= 250)//延时清空串口接收缓冲区
//	{
//		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] = 0;//延时清空串口接收缓冲区
//		if(McuWorkInfo.Uart1Info.UART1ReceiveBufNum != 0)//UART1接收缓冲区下标号
//		{//有数据才进来
//			EmptyUART1ReceiveBuf();//清空UART1接收缓冲区
//		}
//	}
//}



unsigned char ReceiveRebootCount = 0;
/******************************************************************************************
  * @brief  升级回复指令生成
  * @param  ReplyPortNum：0为识别板串口，1为读头串口
  * @retval 无
******************************************************************************************/
void UpgradeReplyCommandCreate(unsigned char ReplyPortNum,unsigned char CommandCode,unsigned char *ControlCommandBuf,unsigned char ControlCommandBufLen,unsigned char FaultCode)//升级回复指令生成
{
	unsigned char UpgradeReplyCommandBuf[100];
	unsigned char UpgradeReplyCommandBufLen = 0;
	
	unsigned char UpgradeReplyCommandNum[1];
	unsigned char UpgradeReplyCommandCRC=0;
	UpgradeReplyCommandBufLen = 0;
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[0];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[1];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[2];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[3];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[4];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = K30VSyncReveive[5];
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = 'M';
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = 0x00;//命令码长度	//待会要重新赋值
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = CommandCode;//操作码
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = FaultCode;//故障码
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = McuConfigInfo.DeviceInfo.CurrentReaderPosi;//方位

	for(UpgradeReplyCommandNum[0]=0;UpgradeReplyCommandNum[0]<ControlCommandBufLen;UpgradeReplyCommandNum[0]++)
	{
		UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = ControlCommandBuf[UpgradeReplyCommandNum[0]];
	}
	
	//植入待定数据
	//McuWorkInfo.Upgrade.UncertainData[1] = 0x10;
	for(UpgradeReplyCommandNum[0]=0;UpgradeReplyCommandNum[0]<10;UpgradeReplyCommandNum[0]++)
	{
		UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = McuWorkInfo.Upgrade.UncertainData[UpgradeReplyCommandNum[0]];//待定数据
	}

	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen-4] = 1;//识别板状态，0为不在线，1为在线，2为休眠，3为掉电
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen-3] = 1;//识别板状态，0为不在线，1为在线，2为休眠，3为掉电
	
	UpgradeReplyCommandBuf[7] = UpgradeReplyCommandBufLen - 6;//命令码长度
	UpgradeReplyCommandCRC = Get_Crc8_LookUp(UpgradeReplyCommandBuf,UpgradeReplyCommandBufLen,0,CRC_8_TAB);
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++]=(volatile unsigned char)(UpgradeReplyCommandCRC >>0x04)&0x0F;//发送缓冲区
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++]=(volatile unsigned char)(UpgradeReplyCommandCRC >>0x00)&0x0F;//发送缓冲区
	if(ReplyPortNum == 0)//0为识别板串口
	{
		McuWorkInfo.UartInfo.UART1SendBufNum = UpgradeReplyCommandBufLen;//发送缓冲区下标号
		memcpy((unsigned char *)McuWorkInfo.UartInfo.UART1SendBuf,(unsigned char *)UpgradeReplyCommandBuf,McuWorkInfo.UartInfo.UART1SendBufNum);//字符串复制
		McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
	}
	else
	{
		McuWorkInfo.Uart1Info.UART1SendBufNum = UpgradeReplyCommandBufLen;//发送缓冲区下标号
		memcpy((unsigned char *)McuWorkInfo.Uart1Info.UART1SendBuf,(unsigned char *)UpgradeReplyCommandBuf,McuWorkInfo.Uart1Info.UART1SendBufNum);//字符串复制
		McuWorkInfo.Uart1Info.UART1SendDataStatus = 1;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
	}
				
}


/******************************************************************************************
  * @brief  自动接收串口读头原始数据
  * @param  ReceiveSourceData：接收到的原始数据
  * @retval 无
******************************************************************************************/
unsigned char AutoReceiveUartReaderSourceData(unsigned char UartPortNum)//自动接收串口读头原始数据
{
	unsigned char ReceiveReaderDataNum[1];
	unsigned char ReceiveUartReaderAnalysis = 0;
	unsigned char *pReceiveDataAnalysisBuf;
	unsigned char ReceiveDataAnalysisBufLen = 0;
	unsigned char ReceiveDataAnalysisBufCRC = 0;
  unsigned char pReceiveDataIndex = 0;//指针指向的索引
  unsigned char pReceiveDataDeviationIndex = 0;//指针偏移索引

	
	if(UartPortNum == 0)//识别板串口
	{
		pReceiveDataAnalysisBuf = (unsigned char *)&McuWorkInfo.UartInfo.UART1ReceiveBuf[0];
		ReceiveDataAnalysisBufLen = McuWorkInfo.UartInfo.UART1ReceiveBufNum;
	}
	else
	{//读头串口
		
		pReceiveDataAnalysisBuf = (unsigned char *)&McuWorkInfo.Uart1Info.UART1ReceiveBuf[0];
		ReceiveDataAnalysisBufLen = McuWorkInfo.Uart1Info.UART1ReceiveBufNum;
	}
	if(	(ReceiveDataAnalysisBufLen >= (pReceiveDataAnalysisBuf[7]+8))
		&&(pReceiveDataAnalysisBuf[7] != 0)
		)
	{//说明长度验证成功
		if(pReceiveDataAnalysisBuf[6] == 'M')
		{//说明是K20V协议
			ReceiveDataAnalysisBufLen = pReceiveDataAnalysisBuf[7]+8;//重新校准长度
			ReceiveDataAnalysisBufCRC = Get_Crc8_LookUp(pReceiveDataAnalysisBuf,ReceiveDataAnalysisBufLen - 2,0,CRC_8_TAB);
			if(	(pReceiveDataAnalysisBuf[ReceiveDataAnalysisBufLen-1] == ((ReceiveDataAnalysisBufCRC&0x0F)>>0))
				&&(pReceiveDataAnalysisBuf[ReceiveDataAnalysisBufLen-2] == ((ReceiveDataAnalysisBufCRC&0xF0)>>4))
				)
			{//校验通过了
				
				pReceiveDataIndex = pReceiveDataAnalysisBuf[7] + 8 - 12;//指针指向的索引
				//提取待定数据
				for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<10;ReceiveReaderDataNum[0]++)
				{
					McuWorkInfo.Upgrade.UncertainData[ReceiveReaderDataNum[0]] = pReceiveDataAnalysisBuf[pReceiveDataIndex + ReceiveReaderDataNum[0]];//待定数据
				}
				
				if(pReceiveDataAnalysisBuf[0] == K30VSyncReveive[0])
				{//说明是识别板发过来的
					pReceiveDataDeviationIndex = 1;//指针偏移索引
					McuConfigInfo.DeviceInfo.CurrentReaderPosi = pReceiveDataAnalysisBuf[10];//当前通讯读头方位
					
				}
				else
				{
					pReceiveDataDeviationIndex = 0;//指针偏移索引
				}
//				
//	volatile unsigned int 
//	volatile unsigned int UpgradePacketLen;//当前升级包长度
//	volatile unsigned char UpgradeDataBuf[UpgradeDataBufMax];//升级数据缓冲区
//	volatile unsigned char UpgradeDataBufNum;//升级数据缓冲区下标号
//	
//	
//	volatile unsigned char UncertainData[10];//待定数据
				if(UartPortNum == 0)
				{
					McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 0;//自动初始化串口计时
					McuWorkInfo.Upgrade.CommunicationPortNum = 1;//升级通讯端口，1为识别板串口，2为读头串口
				}
				else
				{
					McuWorkInfo.AutoWorkInfo.AutoInitUartTime[0] = 0;//自动初始化串口计时
					McuWorkInfo.Upgrade.CommunicationPortNum = 2;//升级通讯端口，1为识别板串口，2为读头串口
				}
				
				McuWorkInfo.Upgrade.CreateDataBufNum = 0;//生成数据下标号
				
				McuWorkInfo.Upgrade.CreateFaultCode = 0x01;//生成故障码
				switch(pReceiveDataAnalysisBuf[8])//操作码
				{
					
					case 8://主板所有信息
									if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//当前通讯读头方位
									{//必须是本方位的才解析
										McuConfigInfo.DeviceInfo.BaseBoardVersionLen = 5;//无线底板版本长度
										
										McuWorkInfo.Upgrade.CreateCommand = 4;//生成命令
										McuWorkInfo.Upgrade.CreateFaultCode = 0xF0;//生成故障码
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x04;//通道
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x01;//获取类型	说明是识别板信息
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 15 + 12 + 5 + McuConfigInfo.DeviceInfo.BaseBoardVersionLen + 5;//信息长度	10Byte固定字节 + 12Byte序列号 + 5Byte识别板版本 + 5Byte底板版本
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x12;//洗牌栋数
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0xFF;//识别范围高8位
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0xFF;//识别范围低8位
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x01;//摄像头灯光
										//植入主设备ID
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<4;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0;//主设备ID
										}
										//植入序列号
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=12;//序列号长度
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<12;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuConfigInfo.DeviceInfo.CurrentReaderPosi;//序列号
										}
										
										
										//植入识别板版本
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=5;//识别板版本长度
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<5;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = MCU_VERSION[ReceiveReaderDataNum[0]];//识别板版本
										}
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//延迟进入休眠时间	工作时间	假的
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=0;//灯光亮度
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//灯光延迟时间	电池电量	假的
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//电池电压当前值	假的
										
										//植入无线底板版本
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=5;//无线底板版本长度
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<5;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = MCU_VERSION[ReceiveReaderDataNum[0]];//无线底板版本
										}
										//植入WiFi底板版本
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=McuConfigInfo.DeviceInfo.BaseBoardVersionLen;//无线底板版本长度
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<McuConfigInfo.DeviceInfo.BaseBoardVersionLen;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuConfigInfo.DeviceInfo.BaseBoardVersion[ReceiveReaderDataNum[0]];//无线底板版本
										}
										
										
									}
									break;
					case 20://寻找设备
									if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//当前通讯读头方位
									{//必须是本方位的才解析
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x04;//通道
										
									}
									break;
					case 0x30://升级准备
									McuWorkInfo.Upgrade.CreateCommand = pReceiveDataAnalysisBuf[8];//生成命令
									pReceiveDataIndex = 10 + pReceiveDataDeviationIndex;//指针指向的索引
									McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = pReceiveDataAnalysisBuf[pReceiveDataIndex];//控制码
									McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 1;//结果,0为失败，1为成功
					
					
//									McuConfigInfo.UpgradeStatus = 0;//升级状态，0为正常状态，1为需要升级状态
//									EepromSaveImportantInfo();//EEPROM存储重要信息
					
					
					
									iap_load_app_status=0;//跳转到应用状态，0为需要跳转，1为禁止跳转
									if(pReceiveDataAnalysisBuf[10] == 0)
									{//说明是控制重启的
										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU复位状态，0为正常状态，1为需要复位状态
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU复位倒计时
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU复位倒计时
									}
									else if(pReceiveDataAnalysisBuf[10] == 1)
									{//说明是擦除
//										iap_load_app_status=0;//跳转到应用状态，0为需要跳转，1为禁止跳转
//										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU复位状态，0为正常状态，1为需要复位状态
//										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU复位倒计时
//										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU复位倒计时
									}
									else if(pReceiveDataAnalysisBuf[10] == 3)
									{//说明是控制跳转的
										iap_load_app_status=0;//跳转到应用状态，0为需要跳转，1为禁止跳转
										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU复位状态，0为正常状态，1为需要复位状态
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU复位倒计时
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU复位倒计时
									}
									ReceiveRebootCount++;
									break;
					case 0x31://升级数据
									//if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//当前通讯读头方位
									if(1)
									{//必须是本方位的才解析
										
											LEDAutoLamp(0);//LED灯自动流水灯
											McuWorkInfo.Upgrade.UpgradeDeviceStatus = 1;//升级状态，0为正常，1为正在升级
											McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//升级等待计时
											McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//升级等待计时
							
											McuWorkInfo.Upgrade.CreateCommand = pReceiveDataAnalysisBuf[8];//生成命令
											McuWorkInfo.Upgrade.UpdateReplyResult = 1;//升级回复结果，0为失败，1为成功
											pReceiveDataIndex = 10 + pReceiveDataDeviationIndex;//指针指向的索引
							
											McuWorkInfo.Upgrade.UpgradeDeviceType = pReceiveDataAnalysisBuf[pReceiveDataIndex++];//当前升级设备类型，0为固件，1为主程序
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = 0;//当前升级包地址
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//当前升级包地址
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//当前升级包地址
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<0;//当前升级包地址
											if(McuWorkInfo.Upgrade.UpgradePacketAddress[0] <= McuWorkInfo.Upgrade.UpgradePacketAddress[1])
											{//进到这里说明不合法
												McuWorkInfo.Upgrade.UpgradePacketAddress[1] = 0;
											}
											
											//if(McuWorkInfo.Upgrade.UpgradePacketAddress[0] == (McuWorkInfo.Upgrade.UpgradePacketAddress[1] + McuWorkInfo.Upgrade.UpgradePacketLen))
											if(1)
											{//说明地址是对的，
												McuWorkInfo.Upgrade.UpgradePacketLen = 0;//当前升级包长度
												McuWorkInfo.Upgrade.UpgradePacketLen = (McuWorkInfo.Upgrade.UpgradePacketLen + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//当前升级包长度
												McuWorkInfo.Upgrade.UpgradePacketLen = (McuWorkInfo.Upgrade.UpgradePacketLen + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<0;//当前升级包长度
												
												
												if(McuWorkInfo.Upgrade.UpgradePacketLen <= UpgradeDataBufMax)//当前升级包长度
												{//说明包数据长度没有超过范围
													McuWorkInfo.Upgrade.UpgradeDataBufNum = McuWorkInfo.Upgrade.UpgradePacketLen;//升级数据缓冲区下标号
													//提取升级包数据
													for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<McuWorkInfo.Upgrade.UpgradeDataBufNum;ReceiveReaderDataNum[0]++)
													{
														McuWorkInfo.Upgrade.UpgradeDataBuf[ReceiveReaderDataNum[0]] = pReceiveDataAnalysisBuf[pReceiveDataIndex + ReceiveReaderDataNum[0]];//升级数据缓冲区
													}
													//准备把数据写入Flash
													if(FlashWriteData(McuWorkInfo.Upgrade.UpgradePacketAddress[0],(unsigned char *)McuWorkInfo.Upgrade.UpgradeDataBuf,McuWorkInfo.Upgrade.UpgradeDataBufNum) == 0)//Flash写入数据
													{//进到这里说明写入失败
														McuWorkInfo.Upgrade.UpdateReplyResult = 0;//升级回复结果，0为失败，1为成功
													}
													
												}
												else
												{
													McuWorkInfo.Upgrade.UpdateReplyResult = 0;//升级回复结果，0为失败，1为成功
												}
											}
											else
											{//地址是不合法的
												McuWorkInfo.Upgrade.UpdateReplyResult = 0;//升级回复结果，0为失败，1为成功
											}
											
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuWorkInfo.Upgrade.UpgradeDeviceType;//升级类型
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 16) & 0xFF;//升级包地址
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 8) & 0xFF;//升级包地址
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 0) & 0xFF;//升级包地址
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketLen >> 8) & 0xFF;//升级包长度
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketLen >> 0) & 0xFF;//升级包长度
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuWorkInfo.Upgrade.UpdateReplyResult;//升级结果
											
											
									}
									
									break;
					default:break;
				}
				
				if(McuWorkInfo.Upgrade.CreateDataBufNum != 0)//生成数据下标号
				{
					if(McuWorkInfo.Upgrade.CommunicationPortNum == 1)//升级通讯端口，1为识别板串口，2为读头串口
					{
						UpgradeReplyCommandCreate(0,McuWorkInfo.Upgrade.CreateCommand,(unsigned char *)McuWorkInfo.Upgrade.CreateDataBuf,McuWorkInfo.Upgrade.CreateDataBufNum,McuWorkInfo.Upgrade.CreateFaultCode);//升级回复指令生成
					}
					else
					{
						UpgradeReplyCommandCreate(1,McuWorkInfo.Upgrade.CreateCommand,(unsigned char *)McuWorkInfo.Upgrade.CreateDataBuf,McuWorkInfo.Upgrade.CreateDataBufNum,McuWorkInfo.Upgrade.CreateFaultCode);//升级回复指令生成
					}
				}
			}
		}
		
		if(UartPortNum == 0)
		{
			EmptyUART0ReceiveBuf();//清空UART1接收缓冲区
		}
		else
		{
			//EmptyUART1ReceiveBuf();//清空UART1接收缓冲区
		}
		
	}
}

///******************************************************************************************
//  * @brief  串口1自动处理
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void USART1AutoDeal(void)//串口1自动处理
//{
//	
//	if(McuWorkInfo.Uart1Info.UART1SendDataStatus == 1)//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
//	{//需要把数据通过串口发送出去
//		USART1ForWordSendData((unsigned char *)McuWorkInfo.Uart1Info.UART1SendBuf,McuWorkInfo.Uart1Info.UART1SendBufNum);//串口发送转发数据
//		McuWorkInfo.Uart1Info.UART1SendDataStatus = 0;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
//	}
//	
//	
//	AutoEmptyUART1ReceiveBuf();//自动清空UART1接收缓冲区
//	
//}




//void Uart1_IRQHandler(void)//UART1中断函数
//{
//	unsigned char USART1_IRQHandlerTemp=0;
//	if(Uart_GetStatus(M0P_UART1, UartRC))         //UART1数据接收
//	{
//		Uart_ClrStatus(M0P_UART1, UartRC);        //清中断状态位
//		USART1_IRQHandlerTemp=Uart_ReceiveData(M0P_UART1);   //接收数据字节
//		if(
//				(	
//					((McuWorkInfo.Uart1Info.UART1ReceiveBuf[0] != K30VSyncReveive[0])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 1))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[1] != K30VSyncReveive[1])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 2))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[2] != K30VSyncReveive[2])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 3))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[3] != K30VSyncReveive[3])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 4))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[4] != K30VSyncReveive[4])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 5))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[5] != K30VSyncReveive[5])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 6))
//				)
//			&&
//				(	
//					((McuWorkInfo.Uart1Info.UART1ReceiveBuf[0] != K30VSyncSend[0])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 1))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[1] != K30VSyncSend[1])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 2))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[2] != K30VSyncSend[2])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 3))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[3] != K30VSyncSend[3])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 4))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[4] != K30VSyncSend[4])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 5))
//				||((McuWorkInfo.Uart1Info.UART1ReceiveBuf[5] != K30VSyncSend[5])&&(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 6))
//				)
//			)
//		{//说明不符合同步头情况
//			McuWorkInfo.Uart1Info.UART1ReceiveBufNum = 0;//UART1接收缓冲区下标号
//		}
//		
//		McuWorkInfo.Uart1Info.UART1ReceiveBuf[McuWorkInfo.Uart1Info.UART1ReceiveBufNum++] = USART1_IRQHandlerTemp;//UART1接收缓冲区
//		if(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 2)//UART1接收缓冲区下标号
//		{
//			AutoReceiveUartReaderSourceData(1);//自动接收串口读头原始数据
//		}
//		
//		
//		
//		
//		
//		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] = 0;//延时清空串口接收缓冲区
//	}
//	if(Uart_GetStatus(M0P_UART1, UartTC))         //UART0数据发送
//	{
//			Uart_ClrStatus(M0P_UART1, UartTC);        //清中断状态位
//			UARRT1_SendByteStatus = 1;//发送单字节完成状态，0为正常，1为发送完成
//	}
//}

