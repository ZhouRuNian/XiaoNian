#include "WHOLE_LIBRARY.h"




void RxIntCallback(void);
void ErrIntCallback(void);



unsigned char UARRT0_SendByteStatus = 1;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������




/******************************************************************************************
  * @brief  ����0����DMA��ʼ��
	* @param  TX_DMA_Buf������DMA������
						TX_DMA_BufLen������DMA����������
  * @retval ��
******************************************************************************************/
void USART0_TX_DMA_Init(unsigned char *TX_DMA_Buf,unsigned int TX_DMA_BufLen)//����0����DMA��ʼ��
{
	
	stc_dma_cfg_t stcDmaCfg;
    
	DDL_ZERO_STRUCT(stcDmaCfg);                                //��ʼ������

	Sysctrl_SetPeripheralGate(SysctrlPeripheralDma,TRUE);      //ʹ��DMAC����ʱ���ſؿ���
	//tx dma����
	stcDmaCfg.u32SrcAddress = (uint32_t)TX_DMA_Buf;          //�������ݻ���
	stcDmaCfg.u32DstAddress = 0x40000000;                      //�������ݼĴ�����ַ
	stcDmaCfg.enSrcAddrReloadCtl = DmaMskSrcAddrReloadEnable;  //ʹ��DMAԴ��ַ����
	stcDmaCfg.enSrcBcTcReloadCtl = DmaMskBcTcReloadEnable;     //ʹ��BC[3:0]��CONFA:TC[15:0]�����ع���
	stcDmaCfg.enDestAddrReloadCtl = DmaMskDstAddrReloadEnable; //ʹ��DMAĿ�ĵ�ַ����
	stcDmaCfg.enTransferMode = DmaMskOneTransfer;              //һ�δ��䣬DMAC�������ʱ���CONFA:ENSλ
	stcDmaCfg.enDstAddrMode = DmaMskDstAddrFix;                //Ŀ�ĵ�ַ�̶�
	stcDmaCfg.enSrcAddrMode = DmaMskSrcAddrInc;                //Դ��ַ����
	stcDmaCfg.u16BlockSize = 1;                                //�鴫�����
	stcDmaCfg.u16TransferCnt = TX_DMA_BufLen;                              //�鴫�������һ�δ���һ���ֽڣ���������
	stcDmaCfg.enMode = DmaMskBlock;                            //��(Block)����
	stcDmaCfg.enTransferWidth = DmaMsk8Bit;                    // 8 bit  �ֽڴ���
	stcDmaCfg.enRequestNum = DmaUart0TxTrig;                   //DMAӲ������ԴλUart1Tx
	stcDmaCfg.enPriority = DmaMskPriorityFix;                  //DMA ��ͨ�����ȼ��̶� (CH0>CH1)

	Dma_Enable();                                              //DMAģ��ʹ��
	Dma_InitChannel(DmaCh1, &stcDmaCfg);                       //DMAͨ��1��ʼ��
	Dma_EnableChannel(DmaCh1);                                 //ʹ��ͨ��1
}

/******************************************************************************************
  * @brief  ����0����DMA�Զ����״̬
  * @param  ��
  * @retval ��
******************************************************************************************/
void USART0_TX_DMA_AutoClrStat(void)//����0����DMA�Զ����״̬
{
	if(5 == Dma_GetStat(DmaCh1))//���һ��ͨ�����䣨RAM���� -> UART0_TX  x�ֽڣ�
	{
			Dma_DisableChannel(DmaCh1);//����ͨ��1
			Dma_ClrStat(DmaCh1);//���ͨ��1״ֵ̬    
			UARRT0_SendByteStatus = 1;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
	}  
	    
}
/******************************************************************************************
  * @brief  ����2��ʼ��
  * @param  BaudRate��������
            StopBits��ֹͣλ
  * @retval ��
******************************************************************************************/
void USART2Init(unsigned char InitType)//����2��ʼ��
{
	
	stc_gpio_cfg_t stcGpioCfg;
	stc_uart_cfg_t    stcCfg;

	DDL_ZERO_STRUCT(stcGpioCfg);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //ʹ��GPIOģ��ʱ��

	
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
		Gpio_SetAfMode(GpioPortA, GpioPin9, GpioAf1);          //����PA09 �˿�ΪURART0_TX

		///<RX
		stcGpioCfg.enDir = GpioDirIn;
		stcGpioCfg.enPu = GpioPuEnable;
		stcGpioCfg.enPd = GpioPdDisable;

		Gpio_Init(GpioPortA, GpioPin10, &stcGpioCfg);
		Gpio_SetAfMode(GpioPortA, GpioPin10, GpioAf1);          //����PA10 �˿�ΪURART0_RX
		

		DDL_ZERO_STRUCT(stcCfg);

		///< ��������ʱ��
		Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,TRUE);///<ʹ��uart0ģ��ʱ��

		///<UART Init
		stcCfg.enRunMode        = UartMskMode1;          //ģʽ
		stcCfg.enStopBit        = UartMsk1bit;           //1bitֹͣλ
		stcCfg.enMmdorCk        = UartMskEven;           //ż����
		stcCfg.stcBaud.u32Baud  = 115200;                //������
		stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<ͨ��������Ƶ����
		stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<�������ʱ�ӣ�PCLK��Ƶ��ֵ
		Uart_Init(M0P_UART0, &stcCfg);                   ///<���ڳ�ʼ��

		///<UART�ж�ʹ��
		Uart_ClrStatus(M0P_UART0,UartRC);                ///<���������
		Uart_ClrStatus(M0P_UART0,UartTC);                ///<���������
		Uart_EnableIrq(M0P_UART0,UartRxIrq);             ///<ʹ�ܴ��ڽ����ж�
		//Uart_EnableIrq(M0P_UART0,UartTxIrq);             ///<ʹ�ܴ��ڷ����ж�
		EnableNvic(UART0_IRQn, IrqLevel3, TRUE);       ///<ϵͳ�ж�ʹ��
		
		Uart_EnableFunc(M0P_UART0,UartDmaTxFunc);              //ʹ��DMA����, DMA���ͨ��ʹ�ܺ����Tx BuffΪ�գ���������������
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
		Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0,FALSE);///<ʹ��uart0ģ��ʱ��
	}
	
	    
}

///******************************************************************************************
//  * @brief  ���͵�������
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void USART2SendByte(unsigned char Byte)//���͵�������
//{ 
//	unsigned char USART2SendByteWaitCount[2] = {0,0};
//	while(UARRT0_SendByteStatus == 0)//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
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
//	UARRT0_SendByteStatus = 0;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
//	Uart_SendDataIt(M0P_UART0,Byte); //����UART0���͵�һ���ֽ�
//	//Uart_SendDataPoll(M0P_UART0,Byte);//��ѯ��ʽ��������     
//}

///******************************************************************************************
//  * @brief  �����ַ���
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void USART2SendString(unsigned char *String)//�����ַ���
//{ 
//	while(*String)
//	{
//		USART2SendByte(*String);//���͵�������
//		String++;
//	}
//}


/******************************************************************************************
  * @brief  ���ڷ���ת������
  * @param  *LT8900SendBuf�����ͻ�����
  * @retval ��
******************************************************************************************/
void USART0ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen)
{
	unsigned char USART1ForWordSendDataNum[2];
	unsigned char USART2SendByteWaitCount[2] = {0,0};
	while(UARRT0_SendByteStatus == 0)//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
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
	McuWorkInfo.UartInfo.DMASendBufNum = USART1SendBufLen;//DMA���ͻ������±��
	memcpy((unsigned char *)McuWorkInfo.UartInfo.DMASendBuf,(unsigned char *)USART1SendBuf,McuWorkInfo.UartInfo.DMASendBufNum);//�ַ�������
	UARRT0_SendByteStatus = 0;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
	
	USART0_TX_DMA_Init(USART1SendBuf,USART1SendBufLen);//����0����DMA��ʼ��
	
//	for(USART1ForWordSendDataNum[0]=0;USART1ForWordSendDataNum[0]<USART1SendBufLen;USART1ForWordSendDataNum[0]++)
//	{
//		USART2SendByte(USART1SendBuf[USART1ForWordSendDataNum[0]]);//���͵�������
//	}
}




/******************************************************************************************
  * @brief  ������CRC
  * @param  *ValidArray����Ч����
						ValidArrayLen����Ч���鳤��
  * @retval �����������CRCУ��ֵ
******************************************************************************************/
unsigned char FigureOutXOR_CRC(volatile unsigned char *ValidArray,volatile unsigned char ValidArrayLen)//������CRC
{
	unsigned char FigureOutXOR_CRCNum[2];
	unsigned char FigureOutXOR_CRCResult=0;//������CRC����ֵ
	for(FigureOutXOR_CRCNum[0]=0;FigureOutXOR_CRCNum[0]<ValidArrayLen;FigureOutXOR_CRCNum[0]++)
	{
		FigureOutXOR_CRCResult	^=	ValidArray[FigureOutXOR_CRCNum[0]];//������CRC����ֵ
	}
	return FigureOutXOR_CRCResult;//������CRC����ֵ
}




/******************************************************************************************
  * @brief  ���UART1���ջ�����
  * @param  ��
  * @retval ��
******************************************************************************************/
void EmptyUART0ReceiveBuf(void)//���UART1���ջ�����
{
	unsigned char EmptyUART0ReceiveBufNum[1];
	//���UART1���ջ�����
	for(EmptyUART0ReceiveBufNum[0]=0;EmptyUART0ReceiveBufNum[0]<UART1_RECEIVE_BUF_NUM_MAX;EmptyUART0ReceiveBufNum[0]++)
	{
		McuWorkInfo.UartInfo.UART1ReceiveBuf[EmptyUART0ReceiveBufNum[0]] = 0;//UART1���ջ�����
	}
	McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1���ջ������±��
	
}

/******************************************************************************************
	* @brief  ���UART1���ͻ�����
  * @param  ��
  * @retval ��
******************************************************************************************/
void EmptyUART0SendBuf(void)//���UART1���ͻ�����
{
	unsigned char EmptyUART0SendBufNum[1];
	//���UART1���ͻ�����
	for(EmptyUART0SendBufNum[0]=0;EmptyUART0SendBufNum[0]<UART1_SEND_BUF_NUM_MAX;EmptyUART0SendBufNum[0]++)
	{
		McuWorkInfo.UartInfo.UART1SendBuf[EmptyUART0SendBufNum[0]] = 0;//UART1���ͻ�����
	}
	McuWorkInfo.UartInfo.UART1SendBufNum = 0;//UART1���ͻ������±��
	
}






/******************************************************************************************
  * @brief  �Զ����UART1���ջ�����
  * @param  ��
  * @retval ��
******************************************************************************************/
void AutoEmptyUART0ReceiveBuf(void)//�Զ����UART1���ջ�����
{
//	unsigned char EmptyUART0ReceiveBufNum[1];
	//�Զ���մ������ݻ���������ʱ����յ��������޷�ͨ��У�飬����
	if(McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] >= 250)//��ʱ��մ��ڽ��ջ�����
	{
		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 0;//��ʱ��մ��ڽ��ջ�����
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum != 0)//UART1���ջ������±��
		{//�����ݲŽ���
			EmptyUART0ReceiveBuf();//���UART1���ջ�����
		}
	}
}


///******************************************************************************************
//  * @brief  ����ʶ���WiFi����
//  * @param  ��
//  * @retval ����0˵��û��ִ�У�����1˵���Ѿ�ִ����
//******************************************************************************************/
//unsigned char ConfigDiscernWiFiSwitch(unsigned char ConfigValue)//����ʶ���WiFi����
//{
//	unsigned char ConfigDiscernWiFiSwitchNum[1];
//	unsigned char ConfigDiscernWiFiSwitchResult = 0;//����ʶ���WiFi���ط���ֵ
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
//	//����������Э��
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x11;//�����볤��
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x03;//������
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=McuConfigInfo.DeviceInfo.CurrentReaderPosi;//��ǰͨѶ��ͷ��λ
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x07;//��������
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x01;//���ݳ���
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=ConfigValue;//��������
//	
//	
//	for(ConfigDiscernWiFiSwitchNum[0]=0;ConfigDiscernWiFiSwitchNum[0]<10;ConfigDiscernWiFiSwitchNum[0]++)
//	{
//		McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x00;
//	}
//	
//	McuWorkInfo.UartInfo.UART1SendBufCRC = Get_Crc8_LookUp(McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum,0,CRC_8_TAB);
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x04)&0x0F;//���ͻ�����
//	McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x00)&0x0F;//���ͻ�����
//	
//	McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
//	return ConfigDiscernWiFiSwitchResult;//����ʶ���WiFi���ط���ֵ
//}



/******************************************************************************************
  * @brief  ���ڿ��Ƶƹ�
  * @param  ControlCode��0Ϊ�أ�1Ϊ��
  * @retval ��
******************************************************************************************/
void USART1ControlLight(unsigned char ControlCode,unsigned char ControlType)//���ڿ��Ƶƹ�
{
	unsigned char USART1ControlLightNum[1];
	if(McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] >= 250)//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
	{
		if(McuWorkInfo.UartInfo.UART1SendDataStatus == 0)//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
		{//
			McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] = 0;//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
			
			
			if((McuConfigInfo.DeviceInfo.CurrentReaderPosi <= 0) || (McuConfigInfo.DeviceInfo.CurrentReaderPosi >= 5))//��ǰͨѶ��ͷ��λ
			{
				McuConfigInfo.DeviceInfo.CurrentReaderPosi = 1;//��ǰͨѶ��ͷ��λ
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
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=McuConfigInfo.DeviceInfo.CurrentReaderPosi;//��ǰͨѶ��ͷ��λ
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x02;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=0x01;
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=ControlCode;

			McuWorkInfo.Upgrade.UncertainData[1] = 0x10;//��������	ǿ��ת��������ģʽ
			for(USART1ControlLightNum[0]=0;USART1ControlLightNum[0]<10;USART1ControlLightNum[0]++)
			{
				McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++] = McuWorkInfo.Upgrade.UncertainData[USART1ControlLightNum[0]];//��������
			}
			
			
			McuWorkInfo.UartInfo.UART1SendBufCRC = Get_Crc8_LookUp(McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum,0,CRC_8_TAB);
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x04)&0x0F;//���ͻ�����
			McuWorkInfo.UartInfo.UART1SendBuf[McuWorkInfo.UartInfo.UART1SendBufNum++]=(McuWorkInfo.UartInfo.UART1SendBufCRC >>0x00)&0x0F;//���ͻ�����
			
			McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
			
		}
	}
}

/******************************************************************************************
  * @brief  ��ʶ���ƹ��Զ�����
  * @param  ��
  * @retval ��
******************************************************************************************/
void AutoTurnOnDiscernLightDeal(void)//��ʶ���ƹ��Զ�����
{
	unsigned char LT8900ReplayGetMahjNum[1];
	USART1ControlLight(1,11);//���ڿ��Ƶƹ�
}

/******************************************************************************************
  * @brief  UART��������
  * @param  ��
  * @retval ��
******************************************************************************************/
unsigned char UartUserSwitch = 0;
unsigned char UARTMainDeal(void)//UART��������
{
	unsigned char UARTMainDealNum[2];
	unsigned char UARTMainDealResult = 0;//UART������������ֵ
	
	if(McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] >= 250)//�Զ���ʼ�����ڼ�ʱ
	{
		McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 0;//�Զ���ʼ�����ڼ�ʱ
		USART2Init(0);//����2��ʼ��
	}
	AutoTurnOnDiscernLightDeal();//��ʶ���ƹ��Զ�����
	
	USART0_TX_DMA_AutoClrStat();//����0����DMA�Զ����״̬
	if(McuWorkInfo.UartInfo.UART1SendDataStatus == 1)//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
	{//��Ҫ������ͨ�����ڷ��ͳ�ȥ
		USART0ForWordSendData((unsigned char *)McuWorkInfo.UartInfo.UART1SendBuf,McuWorkInfo.UartInfo.UART1SendBufNum);//���ڷ���ת������
		McuWorkInfo.UartInfo.UART1SendDataStatus = 0;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
		UARTMainDealResult = 1;//UART������������ֵ
	}
	AutoEmptyUART0ReceiveBuf();//�Զ����UART1���ջ�����
	return UARTMainDealResult;//UART������������ֵ
}






void Uart0_IRQHandler(void)//UART0�жϺ���
{
	unsigned char USART2_IRQHandlerTemp=0;
	if(Uart_GetStatus(M0P_UART0, UartRC))         //UART0���ݽ���
	{
		Uart_ClrStatus(M0P_UART0, UartRC);        //���ж�״̬λ
		USART2_IRQHandlerTemp=Uart_ReceiveData(M0P_UART0);   //���������ֽ�
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= LT8900_RECEIVE_BUF_NUM_MAX)//UART1���ջ������±��
		{//��������˵�����������������
			McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1���ջ������±��
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
		{//˵��������ͬ��ͷ���
			McuWorkInfo.UartInfo.UART1ReceiveBufNum = 0;//UART1���ջ������±��
		}
		
		McuWorkInfo.UartInfo.UART1ReceiveBuf[McuWorkInfo.UartInfo.UART1ReceiveBufNum++] = USART2_IRQHandlerTemp;//UART1���ջ�����
		if(McuWorkInfo.UartInfo.UART1ReceiveBufNum >= 2)//UART1���ջ������±��
		{
			AutoReceiveUartReaderSourceData(0);//�Զ����մ��ڶ�ͷԭʼ����
		}
			
			
		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 0;//��ʱ��մ��ڽ��ջ�����
	}
	if(Uart_GetStatus(M0P_UART0, UartTC))         //UART0���ݷ���
	{
			Uart_ClrStatus(M0P_UART0, UartTC);        //���ж�״̬λ
			UARRT0_SendByteStatus = 1;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
	}
}

