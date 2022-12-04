
#ifndef _LED_H
#define _LED_H

#define LED0_PORT        GpioPortB
#define LED0_PIN         GpioPin7

#define LED1_PORT        GpioPortB
#define LED1_PIN         GpioPin6



extern unsigned char LEDIOInitStatus;
extern unsigned char LEDAutoJumpStatus[3];//LED���Զ���˸״̬


extern void LEDIOInit(void);//LED IO�ڳ�ʼ��
extern void LEDOnOrOff(unsigned char LEDx,unsigned char OnOrOffStatus);//LED�ƿ�������
extern void LEDAutoJump(unsigned char LEDx);//LED�Զ���˸
extern void LEDAutoLamp(unsigned char LampType);//LED���Զ���ˮ��



#endif

