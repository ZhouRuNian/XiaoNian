#ifndef _UART_READER_H
#define _UART_READER_H

extern void USART1Init(unsigned char InitType);//����1��ʼ��
extern void USART1SendByte(unsigned char Byte);//���͵�������	
extern void USART1SendString(unsigned char *String);//�����ַ���
extern void USART1AutoDeal(void);//����1�Զ�����
extern void Uart1_IRQHandler(void);//UART1�жϺ���
extern unsigned char AutoReceiveUartReaderSourceData(unsigned char UartPortNum);//�Զ����մ��ڶ�ͷԭʼ����
extern void UpgradeReplyCommandCreate(unsigned char ReplyPortNum,unsigned char CommandCode,unsigned char *ControlCommandBuf,unsigned char ControlCommandBufLen,unsigned char FaultCode);//�����ظ�ָ������


#endif
