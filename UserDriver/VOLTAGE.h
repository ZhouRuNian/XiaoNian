#ifndef _VOLTAGE_H
#define _VOLTAGE_H

#include "WHOLE_LIBRARY.h"


#if BOARD_TYPE == 1//板子类型，0为双模板，1为有线板

//高电压检测管脚定义
#define VOLTAGE_PORT					GpioPortB
#define VOLTAGE_PIN						GpioPin11

//识别板电源管脚定义
#define DISCERN_POWER_PORT					GpioPortA
#define DISCERN_POWER_PIN						GpioPin4

//识别板唤醒管脚定义
#define DISCERN_WAKEUP_PORT					GpioPortB
#define DISCERN_WAKEUP_PIN					GpioPin5


#else

//高电压检测管脚定义
#define VOLTAGE_PORT					GpioPortB
#define VOLTAGE_PIN						GpioPin11

//识别板电源管脚定义
#define DISCERN_POWER_PORT					GpioPortB
#define DISCERN_POWER_PIN						GpioPin5



//LT8900电源控制管脚定义
#define LT8900_POWER_PORT					GpioPortB
#define LT8900_POWER_PIN					GpioPin3



#endif


extern void CheckVoltageIOInit(void);//检测电压io口初始化
extern unsigned char CheckVoltageIO_LEVEL_READ(void);//检测电压io口电平读取
extern void DiscernPowerIOInit(void);//识别板电源io口初始化
extern void DiscernPowerOFF(void);//识别板断电
extern void DiscernPowerON(void);//识别板上电
extern void DiscernResetBoot(void);//识别板重新启动
extern void DiscernWakeUp(void);//识别板唤醒
extern void CheckVoltageAutoDeal(void);//检测电压自动处理
extern void CheckVoltageAutoDeal(void);//检测电压自动处理
extern void AutoWakeUPDeal(unsigned char DealType);//自动唤醒处理
extern void AutoDormancyDeal(void);//自动休眠处理
extern void DiscernDormancyIOLevel(unsigned char IO_Level);//识别板休眠唤醒io口电平设置



extern unsigned char CameraMotoControl(unsigned char ControlType);//摄像头电机控制
extern void ForwardAndReverseCheckAutoDeal(void);//正反转检测自动处理	

extern void DiscernPowerJump(void);//识别板电源闪烁



extern void DiscernPowerControl(unsigned char IO_Level);//识别板电源控制




extern void LowPowerModeConfig(unsigned char Mode);//低功耗模式配置
#endif

