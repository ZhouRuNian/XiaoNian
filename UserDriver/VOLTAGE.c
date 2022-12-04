
#include "WHOLE_LIBRARY.h"



unsigned char CheckVoltageIOInitStatus = 0;
unsigned char CheckVoltageIOStatus = 1;

/******************************************************************************************
  * @brief  ����ѹio�ڳ�ʼ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void CheckVoltageIOInit(void)
{
	
	stc_gpio_cfg_t stcGpioCfg;
  //if(CheckVoltageIOInitStatus == 0)
	if(1)
	{
		CheckVoltageIOInitStatus = 1;
		
		///< ��GPIO����ʱ���ſ�
		Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);
		
		///< �˿ڷ�������->����
		stcGpioCfg.enDir = GpioDirIn;
		///< �˿�������������->����������
		stcGpioCfg.enDrv = GpioDrvL;
		///< �˿�����������->��
		stcGpioCfg.enPu = GpioPuDisable;
		stcGpioCfg.enPd = GpioPdDisable;
		///< �˿ڿ�©�������->��©����ر�
		stcGpioCfg.enOD = GpioOdDisable;
		///< �˿�����/���ֵ�Ĵ������߿���ģʽ����->AHB
		stcGpioCfg.enCtrlMode = GpioAHB;
		///< GPIO IO USER KEY��ʼ��
		Gpio_Init(VOLTAGE_PORT, VOLTAGE_PIN, &stcGpioCfg); 
		
		
		///< �򿪲�����USER KEYΪ�½����ж�
		Gpio_EnableIrq(VOLTAGE_PORT, VOLTAGE_PIN, GpioIrqRising);
		///< ʹ�ܶ˿�PORTAϵͳ�ж�
		EnableNvic(PORTB_IRQn, IrqLevel0, TRUE);
	}
	
}

unsigned char PortB_IRQHandledr[1];

void PortB_IRQHandler(void)//PortB�жϷ�����
{
    if(TRUE == Gpio_GetIrqStatus(VOLTAGE_PORT, VOLTAGE_PIN))
    {
      Gpio_ClearIrq(VOLTAGE_PORT, VOLTAGE_PIN);
    }
		

} 

/******************************************************************************************
  * @brief  ����ѹio�ڵ�ƽ��ȡ
  * @param  ��
  * @retval ��
******************************************************************************************/
unsigned char CheckVoltageIO_LEVEL_READ(void)//����ѹio�ڵ�ƽ��ȡ
{
	unsigned char CheckVoltageIO_LEVEL_READResult = 0;//����ѹio�ڵ�ƽ��ȡ
	if(FALSE != Gpio_GetInputIO(VOLTAGE_PORT, VOLTAGE_PIN))
	{
		CheckVoltageIO_LEVEL_READResult = 1;//����ѹio�ڵ�ƽ��ȡ
	}
	else 
	{
		CheckVoltageIO_LEVEL_READResult = 0;//����ѹio�ڵ�ƽ��ȡ
	}
	//return 1;//����ѹio�ڵ�ƽ��ȡ
	#if DEBUG_MODE == 0//����ģʽ��0Ϊ������1Ϊ����ģʽ
	#else
	CheckVoltageIO_LEVEL_READResult = 1;//����ѹio�ڵ�ƽ��ȡ
	#endif
	return CheckVoltageIO_LEVEL_READResult;//����ѹio�ڵ�ƽ��ȡ
	
}



/******************************************************************************************
  * @brief  ʶ����Դio�ڳ�ʼ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void DiscernPowerIOInit(void)//ʶ����Դio�ڳ�ʼ��
{
	stc_gpio_cfg_t stcGpioCfg;
    
	///< ��GPIO����ʱ���ſ�
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	
	///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
	stcGpioCfg.enDir = GpioDirOut;
	///< �˿�����������->����
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	
	
	stcGpioCfg.enDrv = GpioDrvL;
	stcGpioCfg.enOD = GpioOdDisable;
	stcGpioCfg.enCtrlMode = GpioFastIO;
	///< GPIO IO�˿ڳ�ʼ��
	Gpio_Init(DISCERN_POWER_PORT, DISCERN_POWER_PIN, &stcGpioCfg);
	
}




/******************************************************************************************
  * @brief  ʶ����Դ����
	* @param  ��
	* @retval ��
******************************************************************************************/
void DiscernPowerControl(unsigned char IO_Level)//ʶ����Դ����
{
	DiscernPowerIOInit();//ʶ����Դio�ڳ�ʼ��
  if(IO_Level == 1)
	{
		Gpio_SetIO(DISCERN_POWER_PORT, DISCERN_POWER_PIN);
	}
	else
	{
		Gpio_ClrIO(DISCERN_POWER_PORT, DISCERN_POWER_PIN);
	}
}




///******************************************************************************************
//  * @brief  ʶ����Դ��˸
//	* @param  ��
//	* @retval ��
//******************************************************************************************/
//void DiscernPowerJump(void)//ʶ����Դ��˸
//{
//	unsigned char DiscernPowerJumpNum[1];
//	for(DiscernPowerJumpNum[0]=0;DiscernPowerJumpNum[0]<20;DiscernPowerJumpNum[0]++)
//	{
//		LEDOnOrOff(0xFF,1);//LED�ƿ�������
//		DiscernPowerControl(1);//ʶ����Դ����
//		Delay_ms(100);//��ʱms
//		LEDOnOrOff(0xFF,0);//LED�ƿ�������
//		DiscernPowerControl(0);//ʶ����Դ����
//		Delay_ms(100);//��ʱms
//		WatchDogFeed(1);//���Ź�ι��
//	}
//	
//}


///******************************************************************************************
//  * @brief  ʶ�����������
//	* @param  ��
//	* @retval ��
//******************************************************************************************/
//void DiscernResetBoot(void)//ʶ�����������
//{
//	unsigned char DiscernResetBootNum[1];
//	
//	StartUpAllMcuIoInit();//�ϵ�����MCU io �ڳ�ʼ��
//	DiscernPowerControl(1);//ʶ����Դ����
//}















void PortC_IRQHandler(void)//PortC�жϷ�����
{
    
} 



/******************************************************************************************
  * @brief  �͹���ģʽ����
	* @param  Mode��0Ϊ����ģʽ��1Ϊ����ģʽ��2Ϊ�������ģʽ
	* @retval ��
******************************************************************************************/
void LowPowerModeConfig(unsigned char Mode)//�͹���ģʽ����
{
	
	stc_gpio_cfg_t stcGpioCfg;
	StartUpAllMcuIoInit();//�ϵ�����MCU io �ڳ�ʼ��
	INTX_ENABLE();//���������ж�
	DiscernPowerControl(0);//ʶ����Դ����
	CheckVoltageIOInit();//����ѹio�ڳ�ʼ��
	
	///< �˿ڷ�������->���(�������������ϣ����룩���ò���һ��)
	stcGpioCfg.enDir = GpioDirIn;
	///< �˿�����������->����
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	stcGpioCfg.enDrv = GpioDrvH;
	stcGpioCfg.enOD = GpioOdDisable;
	stcGpioCfg.enCtrlMode = GpioFastIO;
	
	///< GPIO IO LED�˿ڳ�ʼ��
	Gpio_Init(LED0_PORT, LED0_PIN, &stcGpioCfg);
	Gpio_ClrIO(LED0_PORT, LED0_PIN);  
	
	///< GPIO IO LED�˿ڳ�ʼ��
	Gpio_Init(LED1_PORT, LED1_PIN, &stcGpioCfg);
	Gpio_ClrIO(LED1_PORT, LED1_PIN);
	
	///< �˿ڷ�������->���
	stcGpioCfg.enDir = GpioDirIn;
	///< �˿�������������->����������
	stcGpioCfg.enDrv = GpioDrvH;
	///< �˿�����������->����
	stcGpioCfg.enPu = GpioPuDisable;
	stcGpioCfg.enPd = GpioPdEnable;
	///< �˿ڿ�©�������->��©����ر�
	stcGpioCfg.enOD = GpioOdDisable;
	///< �˿�����/���ֵ�Ĵ������߿���ģʽ����->AHB
	stcGpioCfg.enCtrlMode = GpioAHB;
	///< GPIO IO��ʼ��
	Gpio_Init(LT8900_POWER_PORT, LT8900_POWER_PIN, &stcGpioCfg); 
	Gpio_ClrIO(LT8900_POWER_PORT, LT8900_POWER_PIN);
	
	
	USART2Init(0xF0);//����2��ʼ��
	if(Mode == 1)
	{
		
	}
	else if(Mode == 2)
	{
//		///< ��GPIO����ʱ���ſ�
//    Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE);

//    //swd as gpio
//    Sysctrl_SetFunc(SysctrlSWDUseIOEn, TRUE);

//    ///< ����Ϊ���ֶ˿�
//    M0P_GPIO->PAADS = 0;
//    M0P_GPIO->PBADS = 0;
//    M0P_GPIO->PCADS = 0;
//    M0P_GPIO->PDADS = 0;

//    ///< ����Ϊ�˿�����
//    M0P_GPIO->PADIR = 0XFFFF;
//    M0P_GPIO->PBDIR = 0XFFFF;
//    M0P_GPIO->PCDIR = 0XFFFF;
//    M0P_GPIO->PDDIR = 0XFFFF;

//    ///< ��������
//    M0P_GPIO->PAPD = 0xFFFF;
//    M0P_GPIO->PBPD = 0xFFFF;
//    M0P_GPIO->PCPD = 0xFFFF;
//    M0P_GPIO->PDPD = 0xFFFF;


//		stc_lptim_cfg_t    stcLptCfg;
//    DDL_ZERO_STRUCT(stcLptCfg);

//    ///< ʹ��LPTIM0 ����ʱ��
//    Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, TRUE);

//    stcLptCfg.enGate   = LptimGateLow;
//    stcLptCfg.enGatep  = LptimGatePLow;
//    stcLptCfg.enTcksel = LptimRcl;
//    stcLptCfg.enTogen  = LptimTogEnLow;
//    stcLptCfg.enCt     = LptimCntFun;           //����������
//    stcLptCfg.enMd     = LptimMode2;            //����ģʽΪģʽ2���Զ���װ��16λ������/��ʱ��
//    stcLptCfg.u16Arr   = 65530;                 //Ԥװ�ؼĴ���ֵ��������ֵ
//    Lptim_Init(M0P_LPTIMER, &stcLptCfg);

//    Lptim_ClrItStatus(M0P_LPTIMER);            //����жϱ�־λ
//    Lptim_ConfIt(M0P_LPTIMER, TRUE);           //����LPTIMER�ж�
//    EnableNvic(LPTIM_IRQn, IrqLevel3, TRUE);
//		Lptim_Cmd(M0P_LPTIMER, TRUE);   ///< ����lptimer0����
//		while(1)
//		{
//			WatchDogFeed(42);//���Ź�ι��
//		}
	
			Lpm_GotoDeepSleep(FALSE);///< �������˯��ģʽ��ʹ���˳��жϷ�����ٴν�����������
	}
	
}

/**
 ******************************************************************************
 ** \brief  LPTIMER�жϷ�����
 **
 ** \return ��
 ******************************************************************************/
void LpTim_IRQHandler(void)//LPTIMER�жϷ�����
{
    if (TRUE == Lptim_GetItStatus(M0P_LPTIMER))
    {
        Lptim_ClrItStatus(M0P_LPTIMER);//���LPTIMER���жϱ�־λ
				if(CheckVoltageIO_LEVEL_READ() != 0)//����ѹio�ڵ�ƽ��ȡ
				{//˵���иߵ�ѹ�����ˣ���ʱֱ�Ӹ�λ��Ƭ��
					MCURestart();//MCU����
				}
    }
}
