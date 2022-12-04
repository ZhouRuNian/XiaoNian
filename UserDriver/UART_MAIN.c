#include "WHOLE_LIBRARY.h"




void RxIntCallback(void);
void ErrIntCallback(void);



unsigned char UARRT0_SendByteStatus = 1;//发送单字节完成状态，0为正常，1为发送完成




/******************************************************************************************
  * @brief  串口0发送DMA初始化
	* @param  TX_DMA_Buf：发送DMA缓冲区
						TX_DMA_BufLen：发送DMA缓冲区长度
  * @retval 无
******************************************************************************************/
void USART0_TX_DMA_Init(unsigned char *TX_DMA_Buf,unsigned int TX_DMA_BufLen)//串口0发送DMA初始化
{
	
	stc_dma_cfg_t stcDmaCfg;
    
	DDL_ZERO_STRUCT(stcDmaCfg);                                //初始化变量

	Sysctrl_SetPeripheralGate(SysctrlPeripheralDma,TRUE);      //使能DMAC外设时钟门控开关
	//tx dma配置
	stcDmaCfg.u32SrcAddress = (uint32_t)TX_DMA_Buf;          //接收数据缓存
	stcDmaCfg.u32DstAddress = 0x40000000;                      //发送数据寄存器地址
	stcDmaCfg.enSrcAddrReloadCtl = DmaMskSrcAddrReloadEnable;  //使能DMA源地址重载
	stcDmaCfg.enSrcBcTcReloadCtl = DmaMskBcTcReloadEnable;     //使能BC[3:0]和CONFA:TC[15:0]的重载功能
	stcDmaCfg.enDestAddrReloadCtl = DmaMskDstAddrReloadEnable; //使能DMA目的地址重载
	stcDmaCfg.enTransferMode = DmaMskOneTransfer;              //一次传输，DMAC传输完成时清除CONFA:ENS位
	stcDmaCfg.enDstAddrMode = DmaMskDstAddrFix;                //目的地址固定
	stcDmaCfg.enSrcAddrMode = DmaMskSrcAddrInc;                //源地址自增
	stcDmaCfg.u16BlockSize = 1;                                //块传输个数
	stcDmaCfg.u16TransferCnt = TX_DMA_BufLen;                              //块传输次数，一次传输一个字节，传输两次
	stcDmaCfg.enMode = DmaMskBlock;                            //块(Block)传输
	stcDmaCfg.enTransferWidth = DmaMsk8Bit;                    // 8 bit  字节传输
	stcDmaCfg.enRequestNum = DmaUart0TxTrig;                   //DMA硬件触发源位Uart1Tx
	stcDmaCfg.enPriority = DmaMskPriorityFix;                  //DMA 各通道优先级固定 (CH0>CH1)

	Dma_Enable();                                              //DMA模块使能
	Dma_InitChannel(DmaCh1, &stcDmaCfg);                       //DMA通道1初始化
	Dma_EnableChannel(DmaCh1);                                 //使能通道1
}

/******************************************************************************************
  * @brief  串口0发送DMA自动清除状态
  * @param  无
  * @retval 无
******************************************************************************************/
void USART0_TX_DMA_AutoClrStat(void)//串口0发送DMA自动清除状态
{
	if(5 == Dma_GetStat(DmaCh1))//完成一次通道传输（RAM缓存 -> UART0_TX  x字节）
	{
			Dma_DisableChannel(DmaCh1);//禁用通道1
			Dma_ClrStat(DmaCh1);//清除通道1状态值    
			UARRT0_SendByteStatus = 1;//发送单字节完成状态，0为正常，1为发送完成
	}  
	    
}
/******************************************************************************************
  * @brief  串口2初始化
  * @param  BaudRate：波特率
            StopBits：停止位
  * @retval 无
******************************************************************************************/
void USART2Init(unsigned char InitType)//串口2初始化
{
	
	stc_gpio_cfg_t stcGpioCfg;
	stc_uart_cfg_t    stcCfg;

	DDL_ZERO_STRUCT(stcGpioCfg);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //使能GPIO模块时钟

	
	if(InitType == 0)
	{
		///<TX
		stcGpioCfg.enDir = GpioDirOut;
		stcGpioCfg.enPu = GpioPuDisable;
		stcGpioCfg.enPd = GpioPdDisable;
		
		stcGpioCfg.enDrv = GpioDrvH;
		stcGpioCfg.enOD = GpioOdDisable;
		stcGpioCfg.enCtrlMode = GpioFastIO;
		Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
		Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);          //配置PA09 端口为URART0_TX

		///<RX
		stcGpioCfg.enDir = GpioDirIn;
		stcGpioCfg.enPu = GpioPuEnable;
		stcGpioCfg.enPd = GpioPdDisable;

		Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
		Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);          //配置PA10 端口为URART0_RX
		

		DDL_ZERO_STRUCT(stcCfg);

		///< 开启外设时钟
		Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);///<使能uart0模块时钟

		///<UART Init
		stcCfg.enRunMode        = UartMskMode1;          //模式
		stcCfg.enStopBit        = UartMsk1bit;           //1bit停止位
		stcCfg.enMmdorCk        = UartMskEven;           //偶检验
		stcCfg.stcBaud.u32Baud  = 115200;                //波特率
		stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<通道采样分频配置
		stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<获得外设时钟（PCLK）频率值
		Uart_Init(M0P_UART0, &stcCfg);                   ///<串口初始化

		///<UART中断使能
		Uart_ClrStatus(M0P_UART0,UartRC);                ///<清接收请求
		Uart_ClrStatus(M0P_UART0,UartTC);                ///<清接收请求
		Uart_EnableIrq(M0P_UART0,UartRxIrq);             ///<使能串口接收中断
		//Uart_EnableIrq(M0P_UART0,UartTxIrq);             ///<使能串口发送中断
		EnableNvic(UART0_IRQn, IrqLevel3, TRUE);       ///<系统中断使能
		
		Uart_EnableFunc(M0P_UART0,UartDmaTxFunc);              //使能DMA发送, DMA相关通道使能后，如果Tx Buff为空，会立马启动传输
	}
	else if(InitType == 0xF0)
	{
		///<TX
		stcGpioCfg.enDir = GpioDirOut;
		stcGpioCfg.enPu = GpioPuDisable;
		stcGpioCfg.enPd = GpioPdEnable;
		stcGpioCfg.enDrv = GpioDrvH;
		stcGpioCfg.enOD = GpioOdDisable;
		stcGpioCfg.enCtrlMode = GpioFastIO;
		
		Gpio_Init(GpioPortA, GpioPin9, &stcGpioCfg);
		Gpio_ClrIO(GpioPortA, GpioPin9);
		Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
		Gpio_ClrIO(GpioPortA, GpioPin10);
		Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,FALSE);///<使能uart0模块时钟
	}
	
	    
}

///******************************************************************************************
//  * @brief  发送单个数据
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void USART2SendByte(unsigned char Byte)//发送单个数据
//{ 
//	unsigned char USART2SendByteWaitCount[2] = {0,0};
//	while(UARRT0_SendByteStatus == 0)//发送单字节完成状态，0为正常，1为发送完成
//	{
//		if(USART2SendByteWaitCount[0]++ >= 100)
//		{
//			USART2SendByteWaitCount[0] = 0;
//			if(USART2SendByteWaitCount[1]++ >= 100)
//			{
//				USART2SendByteWaitCount[1] = 0;
//				break;
//			}
//		}
//	}
//	UARRT0_SendByteStatus = 0;//发送单字节完成状态，0为正常，1为发送完成
//	Uart_SendDataIt(M0P_UART0,Byte); //启动UART0发送第一个字节
//	//Uart_SendDataPoll(M0P_UART0,Byte);//查询方式发送数据     
//}

///******************************************************************************************
//  * @brief  发送字符串
//  * @param  无
//  * @retval 无
//******************************************************************************************/
//void USART2SendString(unsigned char *String)//发送字符串
//{ 
//	while(*String)
//	{
//		USART2SendByte(*String);//发送单个数据
//		String++;
//	}
//}


/******************************************************************************************
  * @brief  串口发送转发数据
  * @param  *LT8900SendBuf：发送缓冲区
  * @retval 无
******************************************************************************************/
void USART0ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen)
{
	unsigned char USART1ForWordSendDataNum[2];
	unsigned char USART2SendByteWaitCount[2] = {0,0};
	while(UARRT0_SendByteStatus == 0)//发送单字节完成状态，0为正常，1为发送完成
	{
		if(USART2SendByteWaitCount[0]++ >= 100)
		{
			USART2SendByteWaitCount[0] = 0;
			if(USART2SendByteWaitCount[1]++ >= 100)
			{
				
				USART2SendByteWaitCount[1] = 0;
				break;
			}
		}
	}
	McuWorkInfo.UartInfo.DMASendBufNum = USART1SendBufLen;//DMA发送缓冲区下标号
	memcpy((unsigned char *)McuWorkInfo.UartInfo.DMASendBuf,(unsigned char *)USART1SendBuf,McuWorkInfo.UartInfo.DMASendBufNum);//字符串复制
	UARRT0_SendByteStatus = 0;//发送单字节完成状态，0为正常，1为发送完成
	
	USART0_TX_DMA_Init(USART1SendBuf,USART1SendBufLen);//串口0发送DMA初始化
	
//	for(USART1ForWordSendDataNum[0]=0;USART1ForWordSendDataNum[0]<USART1SendBufLen;USART1ForWordSendDataNum[0]++)
//	{
//		USART2SendByte(USART1SendBuf[USART1ForWordSendDataNum[0]]);//发送单个数据
//	}
}




/******************************************************************************************
  * @brief  算出异或CRC
  * @param  *ValidArray：有效数组
						ValidArrayLen：有效数组长度
  * @retval 返回算出来的CRC校验值
******************************************************************************************/
unsigned char FigureOutXOR_CRC(volatile unsigned char *ValidArray,volatile unsigned char ValidArrayLen)//算出异或CRC
{
	unsigned char FigureOutXOR_CRCNum[2];
	unsigned char FigureOutXOR_CRCResult=0;//算出异或CRC返回值
	for(FigureOutXOR_CRCNum[0]=0;FigureOutXOR_CRCNum[0]<ValidArrayLen;FigureOutXOR_CRCNum[0]++)
	{
		FigureOutXOR_CRCResult	^=	ValidArray[FigureOutXOR_CRCNum[0]];//算出异或CRC返回值
	}
	return FigureOutXOR_CRCResult;//算出异或CRC返回值
}




/******************************************************************************************
  * @brief  清空UART1接收缓冲区
  * @param  无
  * @retval 无
******************************************************************************************/
void EmptyUART0ReceiveBuf(void)//清空UART1接收缓冲区
{
	unsigned char EmptyUART0ReceiveBufNum[1];
	//清空UART1接收缓冲区
	for(EmptyUART0ReceiveBufNum[0]=0;EmptyUART0ReceiveBufNum[0]<UART1_RECEIVE_BUF_NUM_MAX;EmptyUART0ReceiveBufNum[0]++)
	{
		McuWorkInfo.UartInfo.UART1ReceiveBuf[EmptyUART0ReceiveBufNum[0]] = 0;//UART1接收缓冲区
	}
	McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1接收缓冲区下标号
	
}

/******************************************************************************************
	* @brief  清空UART1发送缓冲区
  * @param  无
  * @retval 无
******************************************************************************************/
void EmptyUART0SendBuf(void)//清空UART1发送缓冲区
{
	unsigned char EmptyUART0SendBufNum[1];
	//清空UART1发送缓冲区
	for(EmptyUART0SendBufNum[0]=0;EmptyUART0SendBufNum[0]<UART1_SEND_BUF_NUM_MAX;EmptyUART0SendBufNum[0]++)
	{
		McuWorkInfo.UartInfo.UART1SendBuf[EmptyUART0SendBufNum[0]] = 0;//UART1发送缓冲区
	}
	McuWorkInfo.UartInfo.UART1SendBufNum = 0;//UART1发送缓冲区下标号
	
}






/******************************************************************************************
  * @brief  自动清空UART1接收缓冲区
  * @param  无
  * @retval 无
******************************************************************************************/
void AutoEmptyUART0ReceiveBuf(void)//自动清空UART1接收缓冲区
{
//	unsigned char EmptyUART0ReceiveBufNum[1];
	//自动清空串口数据缓冲区，有时候接收到的数据无法通过校验，则丢弃
	if(McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] >= 250)//延时清空串口接收缓冲区
	{
		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 0;//延时清空串口接收缓冲区
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum != 0)//UART1接收缓冲区下标号
		{//有数据才进来
			EmptyUART0ReceiveBuf();//清空UART1接收缓冲区
		}
	}
}


///******************************************************************************************
//  * @brief  配置识别板WiFi开关
//  * @param  无
//  * @retval 返回0说明没有执行，返回1说明已经执行了
//******************************************************************************************/
//unsigned char ConfigDiscernWiFiSwitch(unsigned char ConfigValue)//配置识别板WiFi开关
//{
//	unsigned char ConfigDiscernWiFiSwitchNum[1];
//	unsigned char ConfigDiscernWiFiSwitchResult = 0;//配置识别板WiFi开关返回值
//	

//	McuWorkInfo.UartInfo.UART1SendBufNum=0;
//	
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[0];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[1];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[2];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[3];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[4];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=LT8900SyncSend[5];
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]='M';
//	
//	//这是真正的协议
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x11;//命令码长度
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x03;//操作码
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=McuConfigInfo.DeviceInfo.CurrentReaderPosi;//当前通讯读头方位
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x07;//配置类型
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x01;//数据长度
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=ConfigValue;//配置数据
//	
//	
//	for(ConfigDiscernWiFiSwitchNum[0]=0;ConfigDiscernWiFiSwitchNum[0]<10;ConfigDiscernWiFiSwitchNum[0]++)
//	{
//		McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x00;
//	}
//	
//	McuWorkInfo.UartInfo.UART1SendBufCRC = Get_Crc8_LookUp(McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum,0,CRC_8_TAB);
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x04)&0x0F;//发送缓冲区
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x00)&0x0F;//发送缓冲区
//	
//	McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
//	return ConfigDiscernWiFiSwitchResult;//配置识别板WiFi开关返回值
//}



/******************************************************************************************
  * @brief  串口控制灯光
  * @param  ControlCode：0为关，1为开
  * @retval 无
******************************************************************************************/
void USART1ControlLight(unsigned char ControlCode,unsigned char ControlType)//串口控制灯光
{
	unsigned char USART1ControlLightNum[1];
	if(McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] >= 250)//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
	{
		if(McuWorkInfo.UartInfo.UART1SendDataStatus == 0)//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
		{//
			McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] = 0;//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时
			
			
			if((McuConfigInfo.DeviceInfo.CurrentReaderPosi <= 0) || (McuConfigInfo.DeviceInfo.CurrentReaderPosi >= 5))//当前通讯读头方位
			{
				McuConfigInfo.DeviceInfo.CurrentReaderPosi = 1;//当前通讯读头方位
			}
			McuWorkInfo.UartInfo.UART1SendBufNum=0;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[0];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[1];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[2];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[3];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[4];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=K30VSyncSend[5];
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]='M';
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x11;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x03;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=McuConfigInfo.DeviceInfo.CurrentReaderPosi;//当前通讯读头方位
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x02;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x01;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=ControlCode;

			McuWorkInfo.Upgrade.UncertainData[1] = 0x10;//待定数据	强制转换成无线模式
			for(USART1ControlLightNum[0]=0;USART1ControlLightNum[0]<10;USART1ControlLightNum[0]++)
			{
				McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++] = McuWorkInfo.Upgrade.UncertainData[USART1ControlLightNum[0]];//待定数据
			}
			
			
			McuWorkInfo.UartInfo.UART1SendBufCRC = Get_Crc8_LookUp(McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum,0,CRC_8_TAB);
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x04)&0x0F;//发送缓冲区
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x00)&0x0F;//发送缓冲区
			
			McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
			
		}
	}
}

/******************************************************************************************
  * @brief  打开识别板灯光自动处理
  * @param  无
  * @retval 无
******************************************************************************************/
void AutoTurnOnDiscernLightDeal(void)//打开识别板灯光自动处理
{
	unsigned char LT8900ReplayGetMahjNum[1];
	USART1ControlLight(1,11);//串口控制灯光
}

/******************************************************************************************
  * @brief  UART主处理函数
  * @param  无
  * @retval 无
******************************************************************************************/
unsigned char UartUserSwitch = 0;
unsigned char UARTMainDeal(void)//UART主处理函数
{
	unsigned char UARTMainDealNum[2];
	unsigned char UARTMainDealResult = 0;//UART主处理函数返回值
	
	if(McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] >= 250)//自动初始化串口计时
	{
		McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 0;//自动初始化串口计时
		USART2Init(0);//串口2初始化
	}
	AutoTurnOnDiscernLightDeal();//打开识别板灯光自动处理
	
	USART0_TX_DMA_AutoClrStat();//串口0发送DMA自动清除状态
	if(McuWorkInfo.UartInfo.UART1SendDataStatus == 1)//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
	{//需要把数据通过串口发送出去
		USART0ForWordSendData((unsigned char *)McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum);//串口发送转发数据
		McuWorkInfo.UartInfo.UART1SendDataStatus = 0;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
		UARTMainDealResult = 1;//UART主处理函数返回值
	}
	AutoEmptyUART0ReceiveBuf();//自动清空UART1接收缓冲区
	return UARTMainDealResult;//UART主处理函数返回值
}






void Uart0_IRQHandler(void)//UART0中断函数
{
	unsigned char USART2_IRQHandlerTemp=0;
	if(Uart_GetStatus(M0P_UART0, UartRC))         //UART0数据接收
	{
		Uart_ClrStatus(M0P_UART0, UartRC);        //清中断状态位
		USART2_IRQHandlerTemp=Uart_ReceiveData(M0P_UART0);   //接收数据字节
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= LT8900_RECEIVE_BUF_NUM_MAX)//UART1接收缓冲区下标号
		{//进到这里说明缓冲区超过了最大
			McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1接收缓冲区下标号
		}
		if(
				(	
					((McuWorkInfo.UartInfo.UART1ReceiveBuf[0] != K30VSyncReveive[0])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 1))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[1] != K30VSyncReveive[1])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 2))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[2] != K30VSyncReveive[2])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 3))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[3] != K30VSyncReveive[3])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 4))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[4] != K30VSyncReveive[4])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 5))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[5] != K30VSyncReveive[5])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 6))
				)
			&&
				(	
					((McuWorkInfo.UartInfo.UART1ReceiveBuf[0] != K30VSyncSend[0])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 1))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[1] != K30VSyncSend[1])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 2))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[2] != K30VSyncSend[2])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 3))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[3] != K30VSyncSend[3])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 4))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[4] != K30VSyncSend[4])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 5))
				||((McuWorkInfo.UartInfo.UART1ReceiveBuf[5] != K30VSyncSend[5])&&(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 6))
				)
			)
		{//说明不符合同步头情况
			McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1接收缓冲区下标号
		}
		
		McuWorkInfo.UartInfo.UART1ReceiveBuf[McuWorkInfo.UartInfo.UART1ReceiveBufNum++] = USART2_IRQHandlerTemp;//UART1接收缓冲区
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 2)//UART1接收缓冲区下标号
		{
			AutoReceiveUartReaderSourceData(0);//自动接收串口读头原始数据
		}
			
			
		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 0;//延时清空串口接收缓冲区
	}
	if(Uart_GetStatus(M0P_UART0, UartTC))         //UART0数据发送
	{
			Uart_ClrStatus(M0P_UART0, UartTC);        //清中断状态位
			UARRT0_SendByteStatus = 1;//发送单字节完成状态，0为正常，1为发送完成
	}
}

