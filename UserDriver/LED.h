
#ifndef _LED_H
#define _LED_H

#define LED0_PORT        GpioPortB
#define LED0_PIN         GpioPin7

#define LED1_PORT        GpioPortB
#define LED1_PIN         GpioPin6



extern unsigned char LEDIOInitStatus;
extern unsigned char LEDAutoJumpStatus[3];//LED灯自动闪烁状态


extern void LEDIOInit(void);//LED IO口初始化
extern void LEDOnOrOff(unsigned char LEDx,unsigned char OnOrOffStatus);//LED灯控制亮灭
extern void LEDAutoJump(unsigned char LEDx);//LED自动闪烁
extern void LEDAutoLamp(unsigned char LampType);//LED灯自动流水灯



#endif

