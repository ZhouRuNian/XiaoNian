/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/******************************************************************************/
/** \file main.c
 **
 ** A detailed description is available at
 ** @link Sample Group Some description @endlink
 **
 **   - 2017-05-28 LiuHL    First Version
 **
 ******************************************************************************/

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "WHOLE_LIBRARY.h"
#include "adc.h"
#include "gpio.h"
#include "bgr.h"
/******************************************************************************
 * Local pre-processor symbols/macros ('#define')                            
 ******************************************************************************/


/******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/
 
unsigned char ErrorFlag=0;//������



const char MCU_CONFIG_INFO_SYNC[MCU_CONFIG_INFO_SYNC_MAX]="McuConfigInfo";//McuConfigInfoͬ��ͷ
const char LT8900SyncSend[7]="Reader";//LT8900ͬ��ͷ�����ͣ�
const char K30VSyncSend[7]="Vision";//K30Vͬ��ͷ�����ͣ�
const char K30VSyncReveive[7]="LT8900";//K30Vͬ��ͷ(����)

MCU_WORK_INFO McuWorkInfo;//MCU������Ϣ
MCU_CONFIG_INFO McuConfigInfo;//MCU������Ϣ


unsigned char iap_load_app_status=0;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
/******************************************************************************
 * Local type definitions ('typedef')                                         
 ******************************************************************************/

/******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/******************************************************************************
 * Local variable definitions ('static')                                      *
 ******************************************************************************/

/*****************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
 


#define RC_TRIM_BASE_ADDR           ((volatile uint16_t*) (0x00100C00ul))
#define RCH_CR_TRIM_24M_VAL         (*((volatile uint16_t*) (0x00100C00ul)))
#define RCH_CR_TRIM_22_12M_VAL      (*((volatile uint16_t*) (0x00100C02ul)))
#define RCH_CR_TRIM_16M_VAL         (*((volatile uint16_t*) (0x00100C04ul)))
#define RCH_CR_TRIM_8M_VAL          (*((volatile uint16_t*) (0x00100C06ul)))
#define RCH_CR_TRIM_4M_VAL          (*((volatile uint16_t*) (0x00100C08ul)))
	
void _SysctrlUnlock(void)
{
    M0P_SYSCTRL->SYSCTRL2 = 0x5A5A;
    M0P_SYSCTRL->SYSCTRL2 = 0xA5A5;
}
/******************************************************************************************
  * @brief  ϵͳʱ������
  * @param  ��
  * @retval ��
******************************************************************************************/
void SetSysClockConfig(void)//ϵͳʱ������
{
	unsigned char temp=0;   
	
//	stc_sysctrl_clk_cfg_t stcCfg;
//	
	///< ����FLASH����ʱ��
	Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);

	
	en_flash_waitcycle_t      enWaitCycle;
	stc_sysctrl_pll_cfg_t     stcPLLCfg;
	
	//�ṹ���ʼ������
	DDL_ZERO_STRUCT(stcPLLCfg);
	
	enWaitCycle = FlashWaitCycle1;
	Flash_WaitCycle(enWaitCycle);
	
	stcPLLCfg.enInFreq    = SysctrlPllInFreq4_6MHz;     //RCH 4MHz
	stcPLLCfg.enOutFreq   = SysctrlPllOutFreq36_48MHz;  //PLL ���48MHz
	stcPLLCfg.enPllClkSrc = SysctrlPllRch;              //����ʱ��Դѡ��RCH
	stcPLLCfg.enPllMul    = SysctrlPllMul12;            //4MHz x 12 = 48MHz
	Sysctrl_SetPLLFreq(&stcPLLCfg);
	Sysctrl_SetPLLStableTime(SysctrlPllStableCycle16384);
	Sysctrl_ClkSourceEnable(SysctrlClkPLL, TRUE);
	
	Sysctrl_SysClkSwitch(SysctrlClkPLL);  ///< ʱ���л�//ʹ��RCL
  //Sysctrl_ClkSourceEnable(SysctrlClkRCL, TRUE);
	
}	


/******************************************************************************************
  * @brief  �ϵ�����MCU io �ڳ�ʼ��
  * @param  ��
  * @retval ��
******************************************************************************************/
void StartUpAllMcuIoInit(void)//�ϵ�����MCU io �ڳ�ʼ��
{
	unsigned char StartUpAllMcuIoInitNum[1];
	stc_gpio_cfg_t stcGpioCfg;
	Bt_M0_Stop(TIM0);

	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralUart1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpUart1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralI2c1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi0, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralSpi1, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralLpTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdvTim, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTim3, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralWdt, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralAdcBgr, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralTick, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, FALSE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralDma, FALSE); 
	
	
	
	///< ��GPIO����ʱ���ſ�
	//Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	Sysctrl_SetPeripheralGate(SysctrlPeripheralGpio, TRUE); 
	///< �˿ڷ�������->����
	stcGpioCfg.enDir = GpioDirIn;
	///< �˿�����������->����
	stcGpioCfg.enPu = GpioPuEnable;
	stcGpioCfg.enPd = GpioPdDisable;
	
	stcGpioCfg.enDrv = GpioDrvL;//���������� 
	stcGpioCfg.enOD = GpioOdDisable;//��©����ر�
	stcGpioCfg.enCtrlMode = GpioFastIO;
	
	///< GPIO IO �˿ڳ�ʼ��
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortA, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortB, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
	{
		Gpio_Init(GpioPortC, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
	}
//	for(StartUpAllMcuIoInitNum[0]=0;StartUpAllMcuIoInitNum[0]<16;StartUpAllMcuIoInitNum[0]++)
//	{
//		Gpio_Init(GpioPortD, StartUpAllMcuIoInitNum[0], &stcGpioCfg);
//	}
	
	
	
	
	
	
}




extern unsigned char CheckVoltageIOStatus;
unsigned char CurrentChannelTemp = 18;
unsigned char MainNum[3];

/******************************************************************************************
  * @brief  �ϵ��ʼ��
  * @param  ��
  * @retval ��
******************************************************************************************/
void StartUpInit(void)//�ϵ��ʼ��
{
  volatile uint32_t u32Val = 0;
	unsigned int StartUpInitNum[2]={0,0};
	unsigned char StartUpDormancyDelay[2]={0,0};//�ϵ���ʱ����
	DiscernPowerControl(1);//ʶ����Դ����
	
	
	INTX_ENABLE();//���������ж�
	CheckVoltageIOInit();//����ѹio�ڳ�ʼ��
	
	while(CheckVoltageIO_LEVEL_READ() == 0)//����ѹio�ڵ�ƽ��ȡ
	{//������˵����û�иߵ�ѹ������׼����������
		for(MainNum[0]=0;MainNum[0]<20;MainNum[0]++)
		{
			WatchDogFeed(9);//���Ź�ι��
			LEDAutoJump(0xFF);//LED���Զ���˸
			Delay_ms(10);//��ʱms
		}
		#if SLEEP_MODE_SWITCH == 1//˯��ģʽ���أ�0Ϊ�رգ�1Ϊ����
		LowPowerModeConfig(2);//�͹���ģʽ����
		//�������ˣ���һ�£����ж��ǲ��Ǹߵ�ѹ����
		//Delay_ms(10);//��ʱms
		#endif
		WatchDogFeed(8);//���Ź�ι��
		MCURestart();//MCU����
	}
	
	SetSysClockConfig();//ϵͳʱ������
	WatchDogInit();//���Ź���ʼ��
	EepromInit();//eeprom��ʼ��
	EepromReadImportantInfo();//EEPROM��ȡ��Ҫ��Ϣ
	
	if(McuConfigInfo.StartOverCount != 0)//�������������ڱ�ǹ̼���������
	{
		for(MainNum[0]=0;MainNum[0]<20;MainNum[0]++)
		{
			WatchDogFeed(9);//���Ź�ι��
			LEDOnOrOff(0,1);//LED�ƿ�������
			LEDOnOrOff(1,1);//LED�ƿ�������
			Delay_ms(30);//��ʱms
		}
		for(MainNum[0]=0;MainNum[0]<50;MainNum[0]++)
		{
			WatchDogFeed(9);//���Ź�ι��
			LEDAutoJump(0xFF);//LED���Զ���˸
			Delay_ms(30);//��ʱms
		}
	}
	if(McuConfigInfo.StartOverCount++ >= 3)//�������������ڱ�ǹ̼���������
	{//���ֵҪ�������������㣬����ۼӵ�һ��������˵������������ʧ�ܣ���ʱ��Ҫ��������������
		McuConfigInfo.StartOverCount = 250;//�������������ڱ�ǹ̼���������
		McuConfigInfo.UpgradeStatus = 1;//����״̬��0Ϊ����״̬��1Ϊ��Ҫ����״̬
	}
	
	
	if(McuConfigInfo.UpgradeStatus == 1)//����״̬��0Ϊ����״̬��1Ϊ��Ҫ����״̬
	{//��Ҫ�����ģ��Ͳ�����ʶ�����
		iap_load_app_status=1;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
		DiscernPowerControl(1);//ʶ����Դ����
	}
	else
	{
		
		USART2Init(0xF0);//����2��ʼ��
		DiscernPowerControl(0);//ʶ����Դ����
		Delay_ms(100);//��ʱms
		DiscernPowerControl(1);//ʶ����Դ����
	}
	
	Timer0Init();//��ʱ��0��ʼ��
	//USART1Init(0);//����1��ʼ��
	USART2Init(0);//����2��ʼ��
	
	
	
	McuWorkInfo.CurrentStatus.MCUResetStatus = 0;//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
	McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU��λ����ʱ
	McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU��λ����ʱ
	
	McuWorkInfo.Upgrade.UpgradeDeviceStatus = 0;//����״̬��0Ϊ������1Ϊ��������
	
	INTX_ENABLE();//���������ж�
}

/**
 ******************************************************************************
 ** \brief  Main function of project
 **
 ** \return uint32_t return value, if needed
 **
 ** This sample
 **
 ******************************************************************************/

int32_t main(void)
{

	StartUpInit();//�ϵ��ʼ��
	
	while(1)
	{
		if(iap_load_app_status==0)//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
		{
			EepromSaveImportantInfo();//EEPROM�洢��Ҫ��Ϣ
			Wdt_Feed();// ι��
			StartUpAllMcuIoInit();//�ϵ�����MCU io �ڳ�ʼ��
			INTX_DISABLE();//�ر������ж�(���ǲ�����fault��NMI�ж�)
			iap_load_app(FLASH_APP1_ADDR);//��ת��Ӧ��
			//iap_load_app_status=1;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
			StartUpInit();//�ϵ��ʼ��
			INTX_ENABLE();//���������ж�
			MCURestart();//MCU����
		}
		Wdt_Feed();   // ι��
		UARTMainDeal();//UART��������
	}
}



/******************************************************************************************
  * @brief  MCU�����Զ�����
  * @param  ��
  * @retval ��
******************************************************************************************/
void MCUAutoRestartDeal(unsigned char DealCount)//MCU�����Զ�����
{
//	if(McuWorkInfo.CurrentStatus.MCUResetStatus != 0)//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
//	{
//		if(McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0]++ >= DealCount)//MCU��λ����ʱ
//		{
//			McuWorkInfo.AutoWorkInfo.MCUResetCountdown[0] = 0;//MCU��λ����ʱ
//			if(McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1]++ >= 5)//MCU��λ����ʱ
//			{
//				McuWorkInfo.AutoWorkInfo.MCUResetCountdown[1] = 0;//MCU��λ����ʱ
//				
//				MCURestart();//MCU����
//			}
//		}
//	}
}


/******************************************************************************************
  * @brief  MCU����
  * @param  ��
  * @retval ��
******************************************************************************************/
void MCURestart(void)//MCU����
{
	unsigned char MCURestartStatus = 0;
	#if DEBUG_MODE == 0//����ģʽ��0Ϊ������1Ϊ����ģʽ
	if(MCURestartStatus == 0)
	{
		NVIC_SystemReset();//��λ
	}
	
	#else
	
	#endif
}



/******************************************************************************************
  * @brief  �ָ���������
	* @param  ��
	* @retval ��
******************************************************************************************/
//void RestoreFactorySettings(void)//�ָ���������
//{
//	
//}

/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
