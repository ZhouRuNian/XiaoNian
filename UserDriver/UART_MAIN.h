#ifndef _UART_MAIN_H_
#define _UART_MAIN_H_


extern unsigned char RestoreFactorySettingsDiscernWiFiName[6];//Ĭ��WiFi����
extern unsigned char RestoreFactorySettingsDiscernWiFiPassword[9];//Ĭ��WiFi����

extern void USART2Init(unsigned char InitType);//����2��ʼ��
extern void USART0_TX_DMA_AutoClrStat(void);//����0����DMA�Զ����״̬
extern void USART1Close(void);//����1�ر�
extern unsigned char FigureOutXOR_CRC(volatile unsigned char *ValidArray,volatile unsigned char ValidArrayLen);//������CRC


extern void AutoEmptyUART0ReceiveBuf(void);//�Զ����UART1���ջ�����
extern unsigned char AutoUSART1RequestDeviceInfo(void);//�Զ����������豸��Ϣ
extern void USART1GetMahjBuf(void);//���ڻ�ȡ�齫������
extern void USART1ControlLight(unsigned char ControlCode,unsigned char ControlType);//���ڿ��Ƶƹ�
extern void USART1SetDeviceSleep(unsigned char SetSleepType);//���������豸����ģʽ
extern void USART1RestoreFactorySettingsDiscern(void);//���ڷ��ͻָ���������ָ�ʶ���
extern void LT8900HandAutoSend(void);//LT8900����ָ���Զ�����
extern unsigned char ConfigDiscernDeviceName(unsigned char ConfigValue);//����ʶ����豸����
extern void USART0ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen);//���ڷ���ת������
extern void USART1ForWordSendData_DMA(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen);//���ڷ���ת������(DMA��ʽ)
extern unsigned char USART1SendDataDMAWait(unsigned char WaitType);//�ȴ�����DMA�������
extern void LT8900Replay(void);//LT8900�ظ�

extern void EmptyUART0ReceiveBuf(void);//���UART1���ջ�����
extern void DebugModeAutoDeal(void);//����ģʽ�Զ�����
extern unsigned char ConfigDiscernWiFiSwitch(unsigned char ConfigValue);//����ʶ���WiFi����

extern unsigned char UARTMainDeal(void);//UART��������



#endif


