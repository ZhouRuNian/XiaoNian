#include "WHOLE_LIBRARY.h"

unsigned int Timer0Count[2];//��ʱ��0����

/******************************************************************************************
  * @brief  ��ʱ��0��ʼ��
	* @param  ��
	* @retval ��
******************************************************************************************/
void Timer0Init(void)//��ʱ��0��ʼ��
{
	uint16_t                  u16ArrValue;
	uint16_t                  u16CntValue;
	
	unsigned int Timer0Period = 0;
	
	//Timer0���ó�ʼ��(���� = Timer0Period*(1/48M)*256 = 10ms)
	
	stc_bt_mode0_cfg_t     stcBtBaseCfg;
	SystemCoreClockUpdate();//����ϵͳƵ��ֵ
	
	DDL_ZERO_STRUCT(stcBtBaseCfg);
	Timer0Period = 30000;
	
	Sysctrl_SetPeripheralGate(SysctrlPeripheralBaseTim, TRUE); //Base Timer����ʱ��ʹ��
	
	stcBtBaseCfg.enWorkMode = BtWorkMode0;                  //��ʱ��ģʽ
	stcBtBaseCfg.enCT       = BtTimer;                      //��ʱ�����ܣ�����ʱ��Ϊ�ڲ�PCLK
	stcBtBaseCfg.enPRS      = BtPCLKDiv16;                 //PCLK/256
	stcBtBaseCfg.enCntMode  = Bt16bitArrMode;               //�Զ�����16λ������/��ʱ��
	stcBtBaseCfg.bEnTog     = FALSE;
	stcBtBaseCfg.bEnGate    = FALSE;
	stcBtBaseCfg.enGateP    = BtGatePositive;
	Bt_Mode0_Init(TIM0, &stcBtBaseCfg);                     //TIM0 ��ģʽ0���ܳ�ʼ��
	
	Bt_M0_ARRSet(TIM0, (0x10000 - Timer0Period));                        //��������ֵ(ARR = 0x10000 - ����)
	Bt_M0_Cnt16Set(TIM0, (0x10000 - Timer0Period));                      //���ü�����ֵ
	
	
	
	Bt_ClearIntFlag(TIM0,BtUevIrq);                         //���жϱ�־   
	Bt_Mode0_EnableIrq(TIM0);                               //ʹ��TIM0�ж�(ģʽ0ʱֻ��һ���ж�)
	EnableNvic(TIM0_IRQn, IrqLevel3, TRUE);                 //TIM0�ж�ʹ��
	
	Bt_M0_Run(TIM0);        //TIM0 ���С�
}



void Tim0_IRQHandler(void)//TIM0�жϷ�����
{//10ms����1���ж�
	
	//Timer0 ģʽ0 ����ж�
	if(TRUE == Bt_GetIntFlag(TIM0, BtUevIrq))
	{
		
		//USART0_TX_DMA_AutoClrStat();//����0����DMA�Զ����״̬
		if(++Timer0Count[1] >= 5)
		{//��������1��
			
			Timer0Count[1] = 0;
			if(McuWorkInfo.Upgrade.UpgradeDeviceStatus == 0)//����״̬��0Ϊ������1Ϊ��������
			{
				LEDAutoJump(0xFF);//LED���Զ���˸
			}
		}
		
		if(++Timer0Count[0] >= 10)
		{//100ms��������1��
			
			Timer0Count[0] = 0;
			if(McuWorkInfo.Upgrade.UpgradeDeviceStatus == 0)//����״̬��0Ϊ������1Ϊ��������
			{
				McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//�����ȴ���ʱ
				if(++McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] >= 150)//�����ȴ���ʱ
				{
					McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//�����ȴ���ʱ//������ʱ�Զ��˳�����״̬
					iap_load_app_status=0;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת
				}
			}
			else
			{
				McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[1] = 0;//�����ȴ���ʱ
				if(++McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] >= 100)//�����ȴ���ʱ
				{
					McuWorkInfo.AutoWorkInfo.UpgradeWaitTimeCount[0] = 0;//�����ȴ���ʱ//������ʱ�Զ��˳�����״̬
					McuWorkInfo.Upgrade.UpgradeDeviceStatus = 0;//����״̬��0Ϊ������1Ϊ��������
				}
			}
			
			if(++McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] >= 100)//�Զ���ʼ�����ڼ�ʱ
			{
				McuWorkInfo.AutoWorkInfo.AutoInitUartTime[1] = 250;//�Զ���ʼ�����ڼ�ʱ
			}															
			if((McuConfigInfo.DeviceInfo.CurrentReaderPosi <= 0) || (McuConfigInfo.DeviceInfo.CurrentReaderPosi >= 5))//��ǰͨѶ��ͷ��λ
			{
				McuConfigInfo.DeviceInfo.CurrentReaderPosi = 1;//��ǰͨѶ��ͷ��λ
			}
		}
		
		if(++McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[0] >= 10)//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
		{
			McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[0] = 0;//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
			if(++McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] >= 20)//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
			{
				McuWorkInfo.AutoWorkInfo.TurnOnDiscernLightStatus[1] = 250;//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ
			}
		}
		if(++McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] >= 50)//��ʱ��մ��ڽ��ջ�����
		{
			McuWorkInfo.AutoWorkInfo.DelayEmptyUARTReceiveBufCount[0] = 250;//��ʱ��մ��ڽ��ջ�����
		}
		
		Bt_ClearIntFlag(TIM0,BtUevIrq); //�жϱ�־����
	}
}
