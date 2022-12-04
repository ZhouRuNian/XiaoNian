#include "WHOLE_LIBRARY.h"



unsigned char UARRT1_SendByteStatus = 1;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
///******************************************************************************************
//  * @brief  ����1��ʼ��
//  * @param  BaudRate��������
//            StopBits��ֹͣλ
//  * @retval ��
//******************************************************************************************/
//void USART1Init(unsigned char InitType)//����1��ʼ��
//{
//	
//	stc_gpio_cfg_t stcGpioCfg;
//	stc_uart_cfg_t    stcCfg;

//	DDL_ZERO_STRUCT(stcGpioCfg);

//	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio,TRUE); //ʹ��GPIOģ��ʱ��

//	///<TX
//	stcGpioCfg.enDir = GpioDirOut;
//	Gpio_Init(GpioPortD, GpioPin0, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortD, GpioPin0, GpioAf3);          //����PD00 �˿�ΪURART1_TX

//	///<RX
//	stcGpioCfg.enDir = GpioDirIn;
//	Gpio_Init(GpioPortD, GpioPin1, &stcGpioCfg);
//	Gpio_SetAfMode(GpioPortD, GpioPin1, GpioAf3);          //����PD01 �˿�ΪURART1_RX
//	

//	DDL_ZERO_STRUCT(stcCfg);

//	///< ��������ʱ��
//	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1,TRUE);///<ʹ��uart1ģ��ʱ��

//	///<UART Init
//	stcCfg.enRunMode        = UartMskMode1;          //ģʽ
//	stcCfg.enStopBit        = UartMsk1bit;           //1bitֹͣλ
//	stcCfg.enMmdorCk        = UartMskEven;           //ż����
//	stcCfg.stcBaud.u32Baud  = 115200;                //������
//	stcCfg.stcBaud.enClkDiv = UartMsk8Or16Div;       ///<ͨ��������Ƶ����
//	stcCfg.stcBaud.u32Pclk  = Sysctrl_GetPClkFreq(); ///<�������ʱ�ӣ�PCLK��Ƶ��ֵ
//	Uart_Init(M0P_UART1, &stcCfg);                   ///<���ڳ�ʼ��

//	///<UART�ж�ʹ��
//	Uart_ClrStatus(M0P_UART1,UartRC);                ///<���������
//	Uart_ClrStatus(M0P_UART1,UartTC);                ///<���������
//	Uart_EnableIrq(M0P_UART1,UartRxIrq);             ///<ʹ�ܴ��ڽ����ж�
//	Uart_EnableIrq(M0P_UART1,UartTxIrq);             ///<ʹ�ܴ��ڷ����ж�
//	EnableNvic(UART1_IRQn, IrqLevel3, TRUE);       ///<ϵͳ�ж�ʹ��
//	    
//	
//	if(InitType == 0)
//	{
//		DDL_ZERO_STRUCT(stcGpioCfg);
//		
//		///< �˿ڷ�������->����
//		stcGpioCfg.enDir = GpioDirIn;
//		///< �˿�������������->����������
//		stcGpioCfg.enDrv = GpioDrvL;
//		///< �˿�����������->��
//		stcGpioCfg.enPu = GpioPuDisable;
//		stcGpioCfg.enPd = GpioPdDisable;
//		///< �˿ڿ�©�������->��©����ر�
//		stcGpioCfg.enOD = GpioOdDisable;
//		///< �˿�����/���ֵ�Ĵ������߿���ģʽ����->AHB
//		stcGpioCfg.enCtrlMode = GpioAHB;
//		///< GPIO IO USER KEY��ʼ��
//		Gpio_Init(GpioPortD, GpioPin0, &stcGpioCfg); 
//	}
//}





///******************************************************************************************
//  * @brief  ���͵�������
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void USART1SendByte(unsigned char Byte)//���͵�������
//{ 
//	unsigned char USART1SendByteWaitCount[2] = {0,0};
//	while(UARRT1_SendByteStatus == 0)//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
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
//	UARRT1_SendByteStatus = 0;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
//	Uart_SendDataIt(M0P_UART1,Byte); //����UART0���͵�һ���ֽ�
//}


///******************************************************************************************
//  * @brief  ���ڷ���ת������
//  * @param  *LT8900SendBuf�����ͻ�����
//  * @retval ��
//******************************************************************************************/
//void USART1ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen)//���ڷ���ת������
//{
//	unsigned int USART1ForWordSendDataNum[2];
//	unsigned int USART1ForWordSendDataCount = 0;
//	USART1Init(1);//����1��ʼ��
//	Delay_ms(1);//��ʱms
//	for(USART1ForWordSendDataNum[1]=0;USART1ForWordSendDataNum[1]<1;USART1ForWordSendDataNum[1]++)
//	{
//		for(USART1ForWordSendDataNum[0]=0;USART1ForWordSendDataNum[0]<USART1SendBufLen;USART1ForWordSendDataNum[0]++)
//		{
//			USART1SendByte(USART1SendBuf[USART1ForWordSendDataNum[0]]);//���͵�������
//			Delay_us(50);//��ʱus
//		}
//		Delay_ms(1);//��ʱms
//	}
//	Delay_ms(5);//��ʱms
//	USART1Init(0);//����1��ʼ��
//}

///******************************************************************************************
//  * @brief  ���UART1���ջ�����
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void EmptyUART1ReceiveBuf(void)//���UART1���ջ�����
//{
//	unsigned char EmptyUART1ReceiveBufNum[1];
//	//���UART1���ջ�����
//	for(EmptyUART1ReceiveBufNum[0]=0;EmptyUART1ReceiveBufNum[0]<UART1_RECEIVE_BUF_NUM_MAX;EmptyUART1ReceiveBufNum[0]++)
//	{
//		McuWorkInfo.Uart1Info.UART1ReceiveBuf[EmptyUART1ReceiveBufNum[0]] = 0;//UART1���ջ�����
//	}
//	McuWorkInfo.Uart1Info.UART1ReceiveBufNum = 0;//UART1���ջ������±��
//	
//}

///******************************************************************************************
//	* @brief  ���UART1���ͻ�����
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void EmptyUART1SendBuf(void)//���UART1���ͻ�����
//{
//	unsigned char EmptyUART1SendBufNum[1];
//	//���UART1���ͻ�����
//	for(EmptyUART1SendBufNum[0]=0;EmptyUART1SendBufNum[0]<UART1_SEND_BUF_NUM_MAX;EmptyUART1SendBufNum[0]++)
//	{
//		McuWorkInfo.Uart1Info.UART1SendBuf[EmptyUART1SendBufNum[0]] = 0;//UART1���ͻ�����
//	}
//	McuWorkInfo.Uart1Info.UART1SendBufNum = 0;//UART1���ͻ������±��
//	
//}


///******************************************************************************************
//  * @brief  �Զ����UART1���ջ�����
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void AutoEmptyUART1ReceiveBuf(void)//�Զ����UART1���ջ�����
//{
//	unsigned char EmptyUART1ReceiveBufNum[1];
//	//�Զ���մ������ݻ���������ʱ����յ��������޷�ͨ��У�飬����
//	if(McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] >= 250)//��ʱ��մ��ڽ��ջ�����
//	{
//		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] = 0;//��ʱ��մ��ڽ��ջ�����
//		if(McuWorkInfo.Uart1Info.UART1ReceiveBufNum != 0)//UART1���ջ������±��
//		{//�����ݲŽ���
//			EmptyUART1ReceiveBuf();//���UART1���ջ�����
//		}
//	}
//}



unsigned char ReceiveRebootCount = 0;
/******************************************************************************************
  * @brief  �����ظ�ָ������
  * @param  ReplyPortNum��0Ϊʶ��崮�ڣ�1Ϊ��ͷ����
  * @retval ��
******************************************************************************************/
void UpgradeReplyCommandCreate(unsigned char ReplyPortNum,unsigned char CommandCode,unsigned char *ControlCommandBuf,unsigned char ControlCommandBufLen,unsigned char FaultCode)//�����ظ�ָ������
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
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = 0x00;//�����볤��	//����Ҫ���¸�ֵ
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = CommandCode;//������
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = FaultCode;//������
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = McuConfigInfo.DeviceInfo.CurrentReaderPosi;//��λ

	for(UpgradeReplyCommandNum[0]=0;UpgradeReplyCommandNum[0]<ControlCommandBufLen;UpgradeReplyCommandNum[0]++)
	{
		UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = ControlCommandBuf[UpgradeReplyCommandNum[0]];
	}
	
	//ֲ���������
	//McuWorkInfo.Upgrade.UncertainData[1] = 0x10;
	for(UpgradeReplyCommandNum[0]=0;UpgradeReplyCommandNum[0]<10;UpgradeReplyCommandNum[0]++)
	{
		UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++] = McuWorkInfo.Upgrade.UncertainData[UpgradeReplyCommandNum[0]];//��������
	}

	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen-4] = 1;//ʶ���״̬��0Ϊ�����ߣ�1Ϊ���ߣ�2Ϊ���ߣ�3Ϊ����
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen-3] = 1;//ʶ���״̬��0Ϊ�����ߣ�1Ϊ���ߣ�2Ϊ���ߣ�3Ϊ����
	
	UpgradeReplyCommandBuf[7] = UpgradeReplyCommandBufLen - 6;//�����볤��
	UpgradeReplyCommandCRC = Get_Crc8_LookUp(UpgradeReplyCommandBuf,UpgradeReplyCommandBufLen,0,CRC_8_TAB);
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++]=(volatile unsigned char)(UpgradeReplyCommandCRC >>0x04)&0x0F;//���ͻ�����
	UpgradeReplyCommandBuf[UpgradeReplyCommandBufLen++]=(volatile unsigned char)(UpgradeReplyCommandCRC >>0x00)&0x0F;//���ͻ�����
	if(ReplyPortNum == 0)//0Ϊʶ��崮��
	{
		McuWorkInfo.UartInfo.UART1SendBufNum = UpgradeReplyCommandBufLen;//���ͻ������±��
		memcpy((unsigned char *)McuWorkInfo.UartInfo.UART1SendBuf,(unsigned char *)UpgradeReplyCommandBuf,McuWorkInfo.UartInfo.UART1SendBufNum);//�ַ�������
		McuWorkInfo.UartInfo.UART1SendDataStatus = 1;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
	}
	else
	{
		McuWorkInfo.Uart1Info.UART1SendBufNum = UpgradeReplyCommandBufLen;//���ͻ������±��
		memcpy((unsigned char *)McuWorkInfo.Uart1Info.UART1SendBuf,(unsigned char *)UpgradeReplyCommandBuf,McuWorkInfo.Uart1Info.UART1SendBufNum);//�ַ�������
		McuWorkInfo.Uart1Info.UART1SendDataStatus = 1;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
	}
				
}


/******************************************************************************************
  * @brief  �Զ����մ��ڶ�ͷԭʼ����
  * @param  ReceiveSourceData�����յ���ԭʼ����
  * @retval ��
******************************************************************************************/
unsigned char AutoReceiveUartReaderSourceData(unsigned char UartPortNum)//�Զ����մ��ڶ�ͷԭʼ����
{
	unsigned char ReceiveReaderDataNum[1];
	unsigned char ReceiveUartReaderAnalysis = 0;
	unsigned char *pReceiveDataAnalysisBuf;
	unsigned char ReceiveDataAnalysisBufLen = 0;
	unsigned char ReceiveDataAnalysisBufCRC = 0;
  unsigned char pReceiveDataIndex = 0;//ָ��ָ�������
  unsigned char pReceiveDataDeviationIndex = 0;//ָ��ƫ������

	
	if(UartPortNum == 0)//ʶ��崮��
	{
		pReceiveDataAnalysisBuf = (unsigned char *)&McuWorkInfo.UartInfo.UART1ReceiveBuf[0];
		ReceiveDataAnalysisBufLen = McuWorkInfo.UartInfo.UART1ReceiveBufNum;
	}
	else
	{//��ͷ����
		
		pReceiveDataAnalysisBuf = (unsigned char *)&McuWorkInfo.Uart1Info.UART1ReceiveBuf[0];
		ReceiveDataAnalysisBufLen = McuWorkInfo.Uart1Info.UART1ReceiveBufNum;
	}
	if(	(ReceiveDataAnalysisBufLen >= (pReceiveDataAnalysisBuf[7]+8))
		&&(pReceiveDataAnalysisBuf[7] != 0)
		)
	{//˵��������֤�ɹ�
		if(pReceiveDataAnalysisBuf[6] == 'M')
		{//˵����K20VЭ��
			ReceiveDataAnalysisBufLen = pReceiveDataAnalysisBuf[7]+8;//����У׼����
			ReceiveDataAnalysisBufCRC = Get_Crc8_LookUp(pReceiveDataAnalysisBuf,ReceiveDataAnalysisBufLen - 2,0,CRC_8_TAB);
			if(	(pReceiveDataAnalysisBuf[ReceiveDataAnalysisBufLen-1] == ((ReceiveDataAnalysisBufCRC&0x0F)>>0))
				&&(pReceiveDataAnalysisBuf[ReceiveDataAnalysisBufLen-2] == ((ReceiveDataAnalysisBufCRC&0xF0)>>4))
				)
			{//У��ͨ����
				
				pReceiveDataIndex = pReceiveDataAnalysisBuf[7] + 8 - 12;//ָ��ָ�������
				//��ȡ��������
				for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<10;ReceiveReaderDataNum[0]++)
				{
					McuWorkInfo.Upgrade.UncertainData[ReceiveReaderDataNum[0]] = pReceiveDataAnalysisBuf[pReceiveDataIndex + ReceiveReaderDataNum[0]];//��������
				}
				
				if(pReceiveDataAnalysisBuf[0] == K30VSyncReveive[0])
				{//˵����ʶ��巢������
					pReceiveDataDeviationIndex = 1;//ָ��ƫ������
					McuConfigInfo.DeviceInfo.CurrentReaderPosi = pReceiveDataAnalysisBuf[10];//��ǰͨѶ��ͷ��λ
					
				}
				else
				{
					pReceiveDataDeviationIndex = 0;//ָ��ƫ������
				}
//				
//	volatile unsigned int 
//	volatile unsigned int UpgradePacketLen;//��ǰ����������
//	volatile unsigned char UpgradeDataBuf[UpgradeDataBufMax];//�������ݻ�����
//	volatile unsigned char UpgradeDataBufNum;//�������ݻ������±��
//	
//	
//	volatile unsigned char UncertainData[10];//��������
				if(UartPortNum == 0)
				{
					McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 0;//�Զ���ʼ�����ڼ�ʱ
					McuWorkInfo.Upgrade.CommunicationPortNum = 1;//����ͨѶ�˿ڣ�1Ϊʶ��崮�ڣ�2Ϊ��ͷ����
				}
				else
				{
					McuWorkInfo.AutoWorkInfo.AutoInitUartTime[0] = 0;//�Զ���ʼ�����ڼ�ʱ
					McuWorkInfo.Upgrade.CommunicationPortNum = 2;//����ͨѶ�˿ڣ�1Ϊʶ��崮�ڣ�2Ϊ��ͷ����
				}
				
				McuWorkInfo.Upgrade.CreateDataBufNum = 0;//���������±��
				
				McuWorkInfo.Upgrade.CreateFaultCode = 0x01;//���ɹ�����
				switch(pReceiveDataAnalysisBuf[8])//������
				{
					
					case 8://����������Ϣ
									if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//��ǰͨѶ��ͷ��λ
									{//�����Ǳ���λ�ĲŽ���
										McuConfigInfo.DeviceInfo.BaseBoardVersionLen = 5;//���ߵװ�汾����
										
										McuWorkInfo.Upgrade.CreateCommand = 4;//��������
										McuWorkInfo.Upgrade.CreateFaultCode = 0xF0;//���ɹ�����
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x04;//ͨ��
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x01;//��ȡ����	˵����ʶ�����Ϣ
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 15 + 12 + 5 + McuConfigInfo.DeviceInfo.BaseBoardVersionLen + 5;//��Ϣ����	10Byte�̶��ֽ� + 12Byte���к� + 5Byteʶ���汾 + 5Byte�װ�汾
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x12;//ϴ�ƶ���
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0xFF;//ʶ��Χ��8λ
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0xFF;//ʶ��Χ��8λ
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x01;//����ͷ�ƹ�
										//ֲ�����豸ID
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<4;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0;//���豸ID
										}
										//ֲ�����к�
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=12;//���кų���
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<12;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuConfigInfo.DeviceInfo.CurrentReaderPosi;//���к�
										}
										
										
										//ֲ��ʶ���汾
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=5;//ʶ���汾����
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<5;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = MCU_VERSION[ReceiveReaderDataNum[0]];//ʶ���汾
										}
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//�ӳٽ�������ʱ��	����ʱ��	�ٵ�
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=0;//�ƹ�����
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//�ƹ��ӳ�ʱ��	��ص���	�ٵ�
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=250;//��ص�ѹ��ǰֵ	�ٵ�
										
										//ֲ�����ߵװ�汾
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=5;//���ߵװ�汾����
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<5;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = MCU_VERSION[ReceiveReaderDataNum[0]];//���ߵװ�汾
										}
										//ֲ��WiFi�װ�汾
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++]=McuConfigInfo.DeviceInfo.BaseBoardVersionLen;//���ߵװ�汾����
										for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<McuConfigInfo.DeviceInfo.BaseBoardVersionLen;ReceiveReaderDataNum[0]++)
										{
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuConfigInfo.DeviceInfo.BaseBoardVersion[ReceiveReaderDataNum[0]];//���ߵװ�汾
										}
										
										
									}
									break;
					case 20://Ѱ���豸
									if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//��ǰͨѶ��ͷ��λ
									{//�����Ǳ���λ�ĲŽ���
										
										McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 0x04;//ͨ��
										
									}
									break;
					case 0x30://����׼��
									McuWorkInfo.Upgrade.CreateCommand = pReceiveDataAnalysisBuf[8];//��������
									pReceiveDataIndex = 10 + pReceiveDataDeviationIndex;//ָ��ָ�������
									McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = pReceiveDataAnalysisBuf[pReceiveDataIndex];//������
									McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = 1;//���,0Ϊʧ�ܣ�1Ϊ�ɹ�
					
					
//									McuConfigInfo.UpgradeStatus = 0;//����״̬��0Ϊ����״̬��1Ϊ��Ҫ����״̬
//									EepromSaveImportantInfo();//EEPROM�洢��Ҫ��Ϣ
					
					
					
									iap_load_app_status=0;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
									if(pReceiveDataAnalysisBuf[10] == 0)
									{//˵���ǿ���������
										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU��λ����ʱ
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU��λ����ʱ
									}
									else if(pReceiveDataAnalysisBuf[10] == 1)
									{//˵���ǲ���
//										iap_load_app_status=0;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
//										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
//										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU��λ����ʱ
//										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU��λ����ʱ
									}
									else if(pReceiveDataAnalysisBuf[10] == 3)
									{//˵���ǿ�����ת��
										iap_load_app_status=0;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
										McuWorkInfo.CurrentStatus.MCUResetStatus = 1;//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU��λ����ʱ
										McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU��λ����ʱ
									}
									ReceiveRebootCount++;
									break;
					case 0x31://��������
									//if(McuConfigInfo.DeviceInfo.CurrentReaderPosi == pReceiveDataAnalysisBuf[9+pReceiveDataDeviationIndex])//��ǰͨѶ��ͷ��λ
									if(1)
									{//�����Ǳ���λ�ĲŽ���
										
											LEDAutoLamp(0);//LED���Զ���ˮ��
											McuWorkInfo.Upgrade.UpgradeDeviceStatus = 1;//����״̬��0Ϊ������1Ϊ��������
											McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//�����ȴ���ʱ
											McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//�����ȴ���ʱ
							
											McuWorkInfo.Upgrade.CreateCommand = pReceiveDataAnalysisBuf[8];//��������
											McuWorkInfo.Upgrade.UpdateReplyResult = 1;//�����ظ������0Ϊʧ�ܣ�1Ϊ�ɹ�
											pReceiveDataIndex = 10 + pReceiveDataDeviationIndex;//ָ��ָ�������
							
											McuWorkInfo.Upgrade.UpgradeDeviceType = pReceiveDataAnalysisBuf[pReceiveDataIndex++];//��ǰ�����豸���ͣ�0Ϊ�̼���1Ϊ������
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = 0;//��ǰ��������ַ
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//��ǰ��������ַ
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//��ǰ��������ַ
											McuWorkInfo.Upgrade.UpgradePacketAddress[0] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<0;//��ǰ��������ַ
											if(McuWorkInfo.Upgrade.UpgradePacketAddress[0] <= McuWorkInfo.Upgrade.UpgradePacketAddress[1])
											{//��������˵�����Ϸ�
												McuWorkInfo.Upgrade.UpgradePacketAddress[1] = 0;
											}
											
											//if(McuWorkInfo.Upgrade.UpgradePacketAddress[0] == (McuWorkInfo.Upgrade.UpgradePacketAddress[1] + McuWorkInfo.Upgrade.UpgradePacketLen))
											if(1)
											{//˵����ַ�ǶԵģ�
												McuWorkInfo.Upgrade.UpgradePacketLen = 0;//��ǰ����������
												McuWorkInfo.Upgrade.UpgradePacketLen = (McuWorkInfo.Upgrade.UpgradePacketLen + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<8;//��ǰ����������
												McuWorkInfo.Upgrade.UpgradePacketLen = (McuWorkInfo.Upgrade.UpgradePacketLen + pReceiveDataAnalysisBuf[pReceiveDataIndex++])<<0;//��ǰ����������
												
												
												if(McuWorkInfo.Upgrade.UpgradePacketLen <= UpgradeDataBufMax)//��ǰ����������
												{//˵�������ݳ���û�г�����Χ
													McuWorkInfo.Upgrade.UpgradeDataBufNum = McuWorkInfo.Upgrade.UpgradePacketLen;//�������ݻ������±��
													//��ȡ����������
													for(ReceiveReaderDataNum[0]=0;ReceiveReaderDataNum[0]<McuWorkInfo.Upgrade.UpgradeDataBufNum;ReceiveReaderDataNum[0]++)
													{
														McuWorkInfo.Upgrade.UpgradeDataBuf[ReceiveReaderDataNum[0]] = pReceiveDataAnalysisBuf[pReceiveDataIndex + ReceiveReaderDataNum[0]];//�������ݻ�����
													}
													//׼��������д��Flash
													if(FlashWriteData(McuWorkInfo.Upgrade.UpgradePacketAddress[0],(unsigned char *)McuWorkInfo.Upgrade.UpgradeDataBuf,McuWorkInfo.Upgrade.UpgradeDataBufNum) == 0)//Flashд������
													{//��������˵��д��ʧ��
														McuWorkInfo.Upgrade.UpdateReplyResult = 0;//�����ظ������0Ϊʧ�ܣ�1Ϊ�ɹ�
													}
													
												}
												else
												{
													McuWorkInfo.Upgrade.UpdateReplyResult = 0;//�����ظ������0Ϊʧ�ܣ�1Ϊ�ɹ�
												}
											}
											else
											{//��ַ�ǲ��Ϸ���
												McuWorkInfo.Upgrade.UpdateReplyResult = 0;//�����ظ������0Ϊʧ�ܣ�1Ϊ�ɹ�
											}
											
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuWorkInfo.Upgrade.UpgradeDeviceType;//��������
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 16) & 0xFF;//��������ַ
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 8) & 0xFF;//��������ַ
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketAddress[0] >> 0) & 0xFF;//��������ַ
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketLen >> 8) & 0xFF;//����������
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = (McuWorkInfo.Upgrade.UpgradePacketLen >> 0) & 0xFF;//����������
											McuWorkInfo.Upgrade.CreateDataBuf[McuWorkInfo.Upgrade.CreateDataBufNum++] = McuWorkInfo.Upgrade.UpdateReplyResult;//�������
											
											
									}
									
									break;
					default:break;
				}
				
				if(McuWorkInfo.Upgrade.CreateDataBufNum != 0)//���������±��
				{
					if(McuWorkInfo.Upgrade.CommunicationPortNum == 1)//����ͨѶ�˿ڣ�1Ϊʶ��崮�ڣ�2Ϊ��ͷ����
					{
						UpgradeReplyCommandCreate(0,McuWorkInfo.Upgrade.CreateCommand,(unsigned char *)McuWorkInfo.Upgrade.CreateDataBuf,McuWorkInfo.Upgrade.CreateDataBufNum,McuWorkInfo.Upgrade.CreateFaultCode);//�����ظ�ָ������
					}
					else
					{
						UpgradeReplyCommandCreate(1,McuWorkInfo.Upgrade.CreateCommand,(unsigned char *)McuWorkInfo.Upgrade.CreateDataBuf,McuWorkInfo.Upgrade.CreateDataBufNum,McuWorkInfo.Upgrade.CreateFaultCode);//�����ظ�ָ������
					}
				}
			}
		}
		
		if(UartPortNum == 0)
		{
			EmptyUART0ReceiveBuf();//���UART1���ջ�����
		}
		else
		{
			//EmptyUART1ReceiveBuf();//���UART1���ջ�����
		}
		
	}
}

///******************************************************************************************
//  * @brief  ����1�Զ�����
//  * @param  ��
//  * @retval ��
//******************************************************************************************/
//void USART1AutoDeal(void)//����1�Զ�����
//{
//	
//	if(McuWorkInfo.Uart1Info.UART1SendDataStatus == 1)//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
//	{//��Ҫ������ͨ�����ڷ��ͳ�ȥ
//		USART1ForWordSendData((unsigned char *)McuWorkInfo.Uart1Info.UART1SendBuf,McuWorkInfo.Uart1Info.UART1SendBufNum);//���ڷ���ת������
//		McuWorkInfo.Uart1Info.UART1SendDataStatus = 0;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
//	}
//	
//	
//	AutoEmptyUART1ReceiveBuf();//�Զ����UART1���ջ�����
//	
//}




//void Uart1_IRQHandler(void)//UART1�жϺ���
//{
//	unsigned char USART1_IRQHandlerTemp=0;
//	if(Uart_GetStatus(M0P_UART1, UartRC))         //UART1���ݽ���
//	{
//		Uart_ClrStatus(M0P_UART1, UartRC);        //���ж�״̬λ
//		USART1_IRQHandlerTemp=Uart_ReceiveData(M0P_UART1);   //���������ֽ�
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
//		{//˵��������ͬ��ͷ���
//			McuWorkInfo.Uart1Info.UART1ReceiveBufNum = 0;//UART1���ջ������±��
//		}
//		
//		McuWorkInfo.Uart1Info.UART1ReceiveBuf[McuWorkInfo.Uart1Info.UART1ReceiveBufNum++] = USART1_IRQHandlerTemp;//UART1���ջ�����
//		if(McuWorkInfo.Uart1Info.UART1ReceiveBufNum >= 2)//UART1���ջ������±��
//		{
//			AutoReceiveUartReaderSourceData(1);//�Զ����մ��ڶ�ͷԭʼ����
//		}
//		
//		
//		
//		
//		
//		McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[1] = 0;//��ʱ��մ��ڽ��ջ�����
//	}
//	if(Uart_GetStatus(M0P_UART1, UartTC))         //UART0���ݷ���
//	{
//			Uart_ClrStatus(M0P_UART1, UartTC);        //���ж�״̬λ
//			UARRT1_SendByteStatus = 1;//���͵��ֽ����״̬��0Ϊ������1Ϊ�������
//	}
//}

