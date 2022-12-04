#include "WHOLE_LIBRARY.h"

#if BOARD_TYPE == 1//�������ͣ�0Ϊ˫ģ�壬1Ϊ���߰�
//�ⲿ���Ź��ܽŶ���
#define IWDG_EM6323_PORT        GpioPortA
#define IWDG_EM6323_PIN         GpioPin7
#else
//�ⲿ���Ź��ܽŶ���
#define IWDG_EM6323_PORT        GpioPortA
#define IWDG_EM6323_PIN         GpioPin8
#endif



/**
 ******************************************************************************
 ** \brief  WDT��λ����������
 **
 ** \param [in] ��
 **
 ** \retval ��
 **
 ******************************************************************************/
void Wdt_Start(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/**
 ******************************************************************************
 ** \brief  WDTι��
 **
 ** \param [in] ��
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_Feed(void)//WDTι��
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
	
//		Gpio_ClrIO(IWDG_EM6323_PORT, IWDG_EM6323_PIN); 
//		Delay_us(1000);//��ʱus
//		Gpio_SetIO(IWDG_EM6323_PORT, IWDG_EM6323_PIN);
}


/******************************************************************************************
  * @brief  ���Ź�ι��
	* @param  ��
	* @retval ��
******************************************************************************************/
void WatchDogFeed(unsigned char FeedFjlag)//���Ź�ι��
{
	Wdt_Feed();   // ι��
}

/**
 ******************************************************************************
 ** \brief  WDT�жϱ�־���
 **
 ** \param [in] ��
 **
 ** \retval Ok
 **
 ******************************************************************************/
void Wdt_IrqClr(void)
{ 
    M0P_WDT->RST = 0x1E;
    M0P_WDT->RST = 0xE1;
}

/******************************************************************************************
  * @brief  ���Ź���ʼ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void WatchDogInit(void)//���Ź���ʼ��
{
	#if IWDG_SWITCH==1//���Ź����أ�0Ϊ�رտ��Ź���1Ϊ�������Ź�
	SetBit((uint32_t)(&(M0P_SYSCTRL->PERI_CLKEN)), SysctrlPeripheralWdt, TRUE);
	M0P_WDT->CON_f.WOV = WdtT3s28;
	//M0P_WDT->CON_f.WINT_EN = WdtResetEn;
	M0P_WDT->CON_f.WINT_EN = WdtIntEn;
	EnableNvic(WDT_IRQn, IrqLevel3, TRUE);
	///< ���� WDT
	Wdt_Start();
	#endif
}


void Wdt_IRQHandler(void)///< WDT �жϷ������
{
	if((M0P_WDT->CON&0x80u))
	{
			Wdt_IrqClr();       ///<��� wdt �жϱ��

			MCURestart();//MCU����
	}
}
