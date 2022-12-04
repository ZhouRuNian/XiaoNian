#ifndef _UART_READER_H
#define _UART_READER_H

extern void USART1Init(unsigned char InitType);//串口1初始化
extern void USART1SendByte(unsigned char Byte);//发送单个数据	
extern void USART1SendString(unsigned char *String);//发送字符串
extern void USART1AutoDeal(void);//串口1自动处理
extern void Uart1_IRQHandler(void);//UART1中断函数
extern unsigned char AutoReceiveUartReaderSourceData(unsigned char UartPortNum);//自动接收串口读头原始数据
extern void UpgradeReplyCommandCreate(unsigned char ReplyPortNum,unsigned char CommandCode,unsigned char *ControlCommandBuf,unsigned char ControlCommandBufLen,unsigned char FaultCode);//升级回复指令生成


#endif
