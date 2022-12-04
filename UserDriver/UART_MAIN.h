#ifndef _UART_MAIN_H_
#define _UART_MAIN_H_


extern unsigned char RestoreFactorySettingsDiscernWiFiName[6];//默认WiFi名称
extern unsigned char RestoreFactorySettingsDiscernWiFiPassword[9];//默认WiFi密码

extern void USART2Init(unsigned char InitType);//串口2初始化
extern void USART0_TX_DMA_AutoClrStat(void);//串口0发送DMA自动清除状态
extern void USART1Close(void);//串口1关闭
extern unsigned char FigureOutXOR_CRC(volatile unsigned char *ValidArray,volatile unsigned char ValidArrayLen);//算出异或CRC


extern void AutoEmptyUART0ReceiveBuf(void);//自动清空UART1接收缓冲区
extern unsigned char AutoUSART1RequestDeviceInfo(void);//自动串口请求设备信息
extern void USART1GetMahjBuf(void);//串口获取麻将缓冲区
extern void USART1ControlLight(unsigned char ControlCode,unsigned char ControlType);//串口控制灯光
extern void USART1SetDeviceSleep(unsigned char SetSleepType);//串口设置设备休眠模式
extern void USART1RestoreFactorySettingsDiscern(void);//串口发送恢复出厂设置指令到识别板
extern void LT8900HandAutoSend(void);//LT8900握手指令自动发送
extern unsigned char ConfigDiscernDeviceName(unsigned char ConfigValue);//配置识别板设备名称
extern void USART0ForWordSendData(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen);//串口发送转发数据
extern void USART1ForWordSendData_DMA(unsigned char *USART1SendBuf,unsigned char USART1SendBufLen);//串口发送转发数据(DMA方式)
extern unsigned char USART1SendDataDMAWait(unsigned char WaitType);//等待串口DMA发送完成
extern void LT8900Replay(void);//LT8900回复

extern void EmptyUART0ReceiveBuf(void);//清空UART1接收缓冲区
extern void DebugModeAutoDeal(void);//调试模式自动处理
extern unsigned char ConfigDiscernWiFiSwitch(unsigned char ConfigValue);//配置识别板WiFi开关

extern unsigned char UARTMainDeal(void);//UART主处理函数



#endif


