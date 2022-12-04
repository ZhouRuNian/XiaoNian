#ifndef _VOLTAGE_H
#define _VOLTAGE_H

#include "WHOLE_LIBRARY.h"


#if BOARD_TYPE == 1//�������ͣ�0Ϊ˫ģ�壬1Ϊ���߰�

//�ߵ�ѹ���ܽŶ���
#define VOLTAGE_PORT					GpioPortB
#define VOLTAGE_PIN						GpioPin11

//ʶ����Դ�ܽŶ���
#define DISCERN_POWER_PORT					GpioPortA
#define DISCERN_POWER_PIN						GpioPin4

//ʶ��廽�ѹܽŶ���
#define DISCERN_WAKEUP_PORT					GpioPortB
#define DISCERN_WAKEUP_PIN					GpioPin5


#else

//�ߵ�ѹ���ܽŶ���
#define VOLTAGE_PORT					GpioPortB
#define VOLTAGE_PIN						GpioPin11

//ʶ����Դ�ܽŶ���
#define DISCERN_POWER_PORT					GpioPortB
#define DISCERN_POWER_PIN						GpioPin5



//LT8900��Դ���ƹܽŶ���
#define LT8900_POWER_PORT					GpioPortB
#define LT8900_POWER_PIN					GpioPin3



#endif


extern void CheckVoltageIOInit(void);//����ѹio�ڳ�ʼ��
extern unsigned char CheckVoltageIO_LEVEL_READ(void);//����ѹio�ڵ�ƽ��ȡ
extern void DiscernPowerIOInit(void);//ʶ����Դio�ڳ�ʼ��
extern void DiscernPowerOFF(void);//ʶ���ϵ�
extern void DiscernPowerON(void);//ʶ����ϵ�
extern void DiscernResetBoot(void);//ʶ�����������
extern void DiscernWakeUp(void);//ʶ��廽��
extern void CheckVoltageAutoDeal(void);//����ѹ�Զ�����
extern void CheckVoltageAutoDeal(void);//����ѹ�Զ�����
extern void AutoWakeUPDeal(unsigned char DealType);//�Զ����Ѵ���
extern void AutoDormancyDeal(void);//�Զ����ߴ���
extern void DiscernDormancyIOLevel(unsigned char IO_Level);//ʶ������߻���io�ڵ�ƽ����



extern unsigned char CameraMotoControl(unsigned char ControlType);//����ͷ�������
extern void ForwardAndReverseCheckAutoDeal(void);//����ת����Զ�����	

extern void DiscernPowerJump(void);//ʶ����Դ��˸



extern void DiscernPowerControl(unsigned char IO_Level);//ʶ����Դ����




extern void LowPowerModeConfig(unsigned char Mode);//�͹���ģʽ����
#endif

