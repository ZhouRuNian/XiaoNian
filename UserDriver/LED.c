#include "WHOLE_LIBRARY.h"


unsigned char LEDIOInitStatus = 0;
unsigned char LEDAutoJumpStatus[3];//LED���Զ���˸״̬
unsigned char LEDAutoLampStatus[3];//
/******************************************************************************************
  * @brief  LED IO�ڳ�ʼ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void LEDIOInit(void)//LED IO�ڳ�ʼ��
{
	stc_gpio_cfg_t stcGpioCfg;
  if(LEDIOInitStatus == 0)
	//if(1)
	{
		LEDIOInitStatus = 1;
		///< ��GPIO����ʱ���ſ�
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
		
		///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
		stcGpioCfg.enDir = GpioDirOut;
		///< �˿�����������->����
		stcGpioCfg.enPu = GpioPuEnable;
		stcGpioCfg.enPd = GpioPdDisable;
		stcGpioCfg.enDrv = GpioDrvH;
		stcGpioCfg.enOD = GpioOdDisable;
		stcGpioCfg.enCtrlMode = GpioFastIO;
		
		///< GPIO IO LED�˿ڳ�ʼ��
		Gpio_Init(LED0_PORT, LED0_PIN, &stcGpioCfg);
		Gpio_ClrIO(LED0_PORT, LED0_PIN);  
		
		///< GPIO IO LED�˿ڳ�ʼ��
		Gpio_Init(LED1_PORT, LED1_PIN, &stcGpioCfg);
		Gpio_ClrIO(LED1_PORT, LED1_PIN);  
	}
	
}

/******************************************************************************************
  * @brief  LED�ƿ�������
	* @param  OnOrOffStatus������״̬��0Ϊ��ƣ�1Ϊ����
	* @retval ��
******************************************************************************************/
void LEDOnOrOff(unsigned char LEDx,unsigned char OnOrOffStatus)//LED�ƿ�������
{
	#if TEST_LED_SWITCH==1//����LED���أ�0Ϊ�رգ�1Ϊ����
	LEDIOInit();//LED IO�ڳ�ʼ��
	switch(LEDx)
	{
		case 0:
						if(OnOrOffStatus==1)//����״̬��0Ϊ��ƣ�1Ϊ����
						{
							///< LED����
							Gpio_SetIO(LED0_PORT, LED0_PIN);
						}
						else
						{
							///< LED�ر�
							Gpio_ClrIO(LED0_PORT, LED0_PIN);  
						}
						break;
		case 1:
						if(OnOrOffStatus==1)//����״̬��0Ϊ��ƣ�1Ϊ����
						{
							///< LED����
							Gpio_SetIO(LED1_PORT, LED1_PIN);
						}
						else
						{
							///< LED�ر�
							Gpio_ClrIO(LED1_PORT, LED1_PIN);  
						}
						break;
		case 2:
		case 3:
		case 0xFF:
						if(OnOrOffStatus==1)//����״̬��0Ϊ��ƣ�1Ϊ����
						{
							///< LED����
							Gpio_SetIO(LED0_PORT, LED0_PIN);
							Gpio_SetIO(LED1_PORT, LED1_PIN);
						}
						else
						{
							///< LED�ر�
							Gpio_ClrIO(LED0_PORT, LED0_PIN); 
							Gpio_ClrIO(LED1_PORT, LED1_PIN);  
						}
						break;
		default:break;
	}
	
	#endif
}


/******************************************************************************************
  * @brief  LED���Զ���˸
	* @param  ��
	* @retval ��
******************************************************************************************/
void LEDAutoJump(unsigned char LEDx)//LED���Զ���˸
{
	//��Χ����
	if(LEDx >= 3)
	{
		LEDx = 2;
	}
	#if TEST_LED_SWITCH==1//����LED���أ�0Ϊ�رգ�1Ϊ����
	if(LEDAutoJumpStatus[LEDx]==0)//LED���Զ���˸״̬
	{
		LEDOnOrOff(LEDx,1);//LED�ƿ�������
		LEDAutoJumpStatus[LEDx]=1;//LED���Զ���˸״̬
	}
	else
	{
		LEDOnOrOff(LEDx,0);//LED�ƿ�������
		LEDAutoJumpStatus[LEDx]=0;//LED���Զ���˸״̬
	}
	#endif
}


/******************************************************************************************
  * @brief  LED���Զ���ˮ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void LEDAutoLamp(unsigned char LampType)//LED���Զ���ˮ��
{
	if(++LEDAutoLampStatus[0] >= 8)
	{
		LEDAutoLampStatus[0] = 0;
	}
	if(LEDAutoLampStatus[0] == 0)
	{
		LEDOnOrOff(0,0);//LED�ƿ�������
		LEDOnOrOff(1,0);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 1)
	{
		LEDOnOrOff(0,1);//LED�ƿ�������
		LEDOnOrOff(1,0);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 2)
	{
		LEDOnOrOff(0,1);//LED�ƿ�������
		LEDOnOrOff(1,1);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 3)
	{
		LEDOnOrOff(0,0);//LED�ƿ�������
		LEDOnOrOff(1,1);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 4)
	{
		LEDOnOrOff(0,0);//LED�ƿ�������
		LEDOnOrOff(1,0);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 5)
	{
		LEDOnOrOff(0,0);//LED�ƿ�������
		LEDOnOrOff(1,1);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 6)
	{
		LEDOnOrOff(0,1);//LED�ƿ�������
		LEDOnOrOff(1,1);//LED�ƿ�������
	}
	else if(LEDAutoLampStatus[0] == 7)
	{
		LEDOnOrOff(0,1);//LED�ƿ�������
		LEDOnOrOff(1,0);//LED�ƿ�������
	}
}
