#include "WHOLE_LIBRARY.h"



volatile unsigned int FLASH_EEPROM_BASE_ADDR=0;//����flash eeprom�洢��ʼλ��
volatile unsigned int FLASH_EEPROM_MAX_ADDR=0;//Flash eeprom�洢���λ��
volatile unsigned int FLASH_EEPROM_MCU_INFO_BASE_ADDR = 0;//����flash eeprom�洢MCU��Ϣ��ʼλ��
volatile unsigned char FlashEepromAutoSaveScanf[2];//flash eeprom�Զ�����ɨ��
volatile unsigned char FlashInitStatus = 0;//��ʼ��Flash״̬��0Ϊû��ʼ����1Ϊ�Ѿ���ʼ��





/******************************************************************************************
  * @brief  ��ȡflash��С
  * @param  ��
  * @retval ����flash��С
******************************************************************************************/
unsigned short int GetFlashSize(void)//��ȡflash��С
{
	volatile unsigned short int FlashSizeTemp=0;
//	#ifdef STM32F0XX
//	FlashSizeTemp = *(unsigned short int*)(0x1FFFF7CC);//���������Ĵ���
//	#else
//	FlashSizeTemp = *(unsigned short int*)(0x1FFFF7E0);//����.�����Ĵ���
//	#endif
	FlashSizeTemp = 64;
	return FlashSizeTemp;
}


///******************************************************************************************
//  * @brief  ��ȡоƬID
//  * @param  *McuIDBuf��оƬID�洢����
//  * @retval ��
//******************************************************************************************/
//void GetMcuID(unsigned int *McuIDBuf)//��ȡоƬID
//{
//	unsigned char GetMcuIDNum[2];
//	volatile unsigned short int McuIDBufTemp[2];
//	for(GetMcuIDNum[0]=0;GetMcuIDNum[0]<4;GetMcuIDNum[0]++)
//	{
//		McuIDBuf[GetMcuIDNum[0]]=*(unsigned short int*)(0x1FFFF7AC+GetMcuIDNum[0]*2);//������˫����ַ���в���
//	}
//	for(GetMcuIDNum[0]=0;GetMcuIDNum[0]<4;GetMcuIDNum[0]++)
//	{
//		McuIDBuf[GetMcuIDNum[0]]	&= 0xFF;
//	}
//	
//}




/******************************************************************************************
  * @brief  eeprom��ʼ��
  * @param  ��
  * @retval ��
******************************************************************************************/
unsigned char EepromInit(void)//eeprom��ʼ��
{
	///< ����FLASH����ʱ��
	Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);
	FLASH_EEPROM_MAX_ADDR		=	0x00000000+(GetFlashSize()*1024);//Flash eeprom�洢���λ��
	FLASH_EEPROM_BASE_ADDR	=	FLASH_EEPROM_MAX_ADDR-FLASH_EEPROM_SIZE;//����flash eeprom�洢��ʼλ��
	FLASH_EEPROM_MCU_INFO_BASE_ADDR	= FLASH_EEPROM_BASE_ADDR;//����flash eeprom�洢MCU��Ϣ��ʼλ��
	while(Ok != Flash_Init(12, TRUE))
	{
			;
	}
	FlashInitStatus = 1;//��ʼ��Flash״̬��0Ϊû��ʼ����1Ϊ�Ѿ���ʼ��
	return 0;
}




/******************************************************************************************
  * @brief  EEPROM��ȡ��Ҫ��Ϣ
  * @param  ��
  * @retval 
******************************************************************************************/
unsigned char EepromReadImportantInfo(void)//EEPROM��ȡ��Ҫ��Ϣ
{
	unsigned char EepromReadImportantInfoNum[2];
	volatile unsigned short int *EepromReadImportantInfoAddress;//EEPROM��ȡ��Ҫ��Ϣ��ʼ��ַ
	unsigned char EepromReadImportantInfoResult=0;//EEPROM��ȡ��Ҫ��Ϣ����ֵ
	volatile unsigned short int EepromReadImportantInfoBuf[1];//EEPROM��ȡ��Ҫ��Ϣ������
	volatile unsigned char *pMcuConfigInfo;//��Ҫ��Ϣָ��
	volatile unsigned char McuConfigInfoLen=sizeof(McuConfigInfo);//��Ҫ��Ϣ����
	unsigned char EepromReadImportantInfoCRC=0;//EEPROM��ȡ��Ҫ��ϢCRC
	volatile unsigned char CRCStartIndex = 0;//
	

	
	pMcuConfigInfo=&McuConfigInfo.Sync[0];//��Ҫ��Ϣָ��
	EepromReadImportantInfoAddress=(unsigned short int *)FLASH_EEPROM_MCU_INFO_BASE_ADDR;//EEPROM��ȡ��Ҫ��Ϣ��ʼ��ַ

	CRCStartIndex = 3;
	if((McuConfigInfoLen%2)!=0)//��Ҫ��Ϣ����
	{//�������϶�һ������
		McuConfigInfoLen=McuConfigInfoLen+1;//��Ҫ��Ϣ����
		CRCStartIndex = 4;
	}
	for(EepromReadImportantInfoNum[0]=0;EepromReadImportantInfoNum[0]<McuConfigInfoLen;)
	{
		EepromReadImportantInfoBuf[0]	= *EepromReadImportantInfoAddress++;//EEPROM��ȡ��Ҫ��Ϣ������
		pMcuConfigInfo[EepromReadImportantInfoNum[0]++]=(EepromReadImportantInfoBuf[0]>>8)&0xFF;//��Ҫ��Ϣָ��
		pMcuConfigInfo[EepromReadImportantInfoNum[0]++]=(EepromReadImportantInfoBuf[0]>>0)&0xFF;//��Ҫ��Ϣָ��
	}
	
	McuConfigInfo.INFO_CRCTemp = Get_Crc8_LookUp(&McuConfigInfo.Sync[0],McuConfigInfoLen-CRCStartIndex,0,CRC_8_TAB);//��ϢУ��CRC��ʱ�洢
	if(	(McuConfigInfo.INFO_CRC[0] !=	(McuConfigInfo.INFO_CRCTemp>>0x04))//��ϢУ��CRC
		||(McuConfigInfo.INFO_CRC[1] !=	(McuConfigInfo.INFO_CRCTemp&0x0F))//��ϢУ��CRC
	)
	{//��������˵��У�鲻ͨ��
		memset(&McuConfigInfo,0,sizeof(McuConfigInfo));//ֱ������������ݣ����´洢
//		McuConfigInfo.StartOverCount = 250;//�������������ڱ�ǹ̼���������
//		McuConfigInfo.UpgradeStatus = 1;//����״̬��0Ϊ����״̬��1Ϊ��Ҫ����״̬
	}
	
	return EepromReadImportantInfoResult;//EEPROM��ȡ��Ҫ��Ϣ����ֵ
}



/******************************************************************************************
  * @brief  EEPROM�洢��Ҫ��Ϣ
  * @param  ��
  * @retval ����0˵�����ʧ�ܣ�����1˵����ճɹ�
******************************************************************************************/
unsigned char EepromSaveImportantInfo(void)//EEPROM�洢��Ҫ��Ϣ
{
	unsigned char EepromSaveImportantInfoNum[2];
	volatile unsigned int EepromSaveImportantInfoAddress=0;//EEPROM�洢��Ҫ��Ϣ��ʼ��ַ
	unsigned char EepromSaveImportantInfoResult=0;//EEPROM�洢��Ҫ��Ϣ����ֵ
	unsigned short int EepromSaveImportantInfoBuf[1];//EEPROM�洢��Ҫ��Ϣ������
	volatile unsigned char *pMcuConfigInfo;//��Ҫ��Ϣָ��
	volatile unsigned char McuConfigInfoLen=sizeof(McuConfigInfo);//��Ҫ��Ϣ����
	volatile unsigned char CRCStartIndex = 0;//
	
	en_result_t FlashState;
	
	if(FlashInitStatus == 0)//��ʼ��Flash״̬��0Ϊû��ʼ����1Ϊ�Ѿ���ʼ��
	{
		EepromInit();//eeprom��ʼ��
	}
	if(FLASH_EEPROM_MCU_INFO_BASE_ADDR == 0)//EEPROM�洢��Ҫ��Ϣ��ʼ��ַ
	{//�洢��ַ���Ϸ����Ͳ��洢
		return 0;
	}
	CRCStartIndex = 3;
	if((McuConfigInfoLen%2)!=0)//��Ҫ��Ϣ����
	{//�������϶�һ������
		McuConfigInfoLen=McuConfigInfoLen+1;//��Ҫ��Ϣ����
		CRCStartIndex = 4;
	}
	for(EepromSaveImportantInfoNum[0]=0;EepromSaveImportantInfoNum[0]<MCU_CONFIG_INFO_SYNC_MAX;EepromSaveImportantInfoNum[0]++)
	{
		McuConfigInfo.Sync[EepromSaveImportantInfoNum[0]]=MCU_CONFIG_INFO_SYNC[EepromSaveImportantInfoNum[0]];//ͬ��ͷ
	}
	McuConfigInfo.InfoLen=McuConfigInfoLen;//��Ϣ����
	
	McuConfigInfo.INFO_CRCTemp = Get_Crc8_LookUp(&McuConfigInfo.Sync[0],McuConfigInfoLen-CRCStartIndex,0,CRC_8_TAB);//��ϢУ��CRC��ʱ�洢
	McuConfigInfo.INFO_CRC[0]	=	McuConfigInfo.INFO_CRCTemp>>0x04;//��ϢУ��CRC
	McuConfigInfo.INFO_CRC[1]	=	McuConfigInfo.INFO_CRCTemp&0x0F;//��ϢУ��CRC
	
	
	
	
	
	
	
	
	
	
	
	pMcuConfigInfo=&McuConfigInfo.Sync[0];//��Ҫ��Ϣָ��
	EepromSaveImportantInfoAddress=FLASH_EEPROM_MCU_INFO_BASE_ADDR;//EEPROM�洢��Ҫ��Ϣ��ʼ��ַ
	
	
	while(Ok != Flash_Init(12, TRUE))
	{
			;
	}
	FlashState = Flash_SectorErase(EepromSaveImportantInfoAddress);//������ǰ����ҳ����
	if(FlashState != Ok)
	{
		return 0;
	}
	
	for(EepromSaveImportantInfoNum[0]=0;EepromSaveImportantInfoNum[0]<McuConfigInfoLen;)
	{
		if((EepromSaveImportantInfoAddress%2)!=0)
		{//д���ַ������ż��
			EepromSaveImportantInfoAddress=EepromSaveImportantInfoAddress+1;
		}
		EepromSaveImportantInfoBuf[0]	=		*pMcuConfigInfo++;
		EepromSaveImportantInfoBuf[0]	<<=	8;
		EepromSaveImportantInfoBuf[0]	+=	*pMcuConfigInfo++;
		FlashState = Flash_WriteHalfWord(EepromSaveImportantInfoAddress,EepromSaveImportantInfoBuf[0]);//flashд��������ݣ�16bit��
		if(FlashState != Ok)
		{
			return 0;
		}
		EepromSaveImportantInfoAddress += 2;
		EepromSaveImportantInfoNum[0]	+=	2;
	}
	return EepromSaveImportantInfoResult;//EEPROM�洢��Ҫ��Ϣ����ֵ
}




/******************************************************************************************
  * @brief  Flashд������
	* @param  ��
	* @retval ����0��ʾд��ʧ�ܣ�����1��ʾд��ɹ�
******************************************************************************************/
unsigned char FlashWriteData(unsigned int FlashWriteDataAddress,unsigned char *FlashWriteDataBuf,unsigned char FlashWriteDataBufLen)//Flashд������
{
	unsigned int FlashWriteDataNum[2];
	unsigned int FlashWriteDataTemp=0;//Flashд��������ʱ�洢
//	unsigned int FlashWriteDataStatus=0;//Flashд������״̬
	unsigned int EraseUserFlashStatus=0;//�����û�FLASH״̬
	unsigned char FlashWriteWaitCount = 0;
	unsigned char FlashWriteDataResult = 0;//Flashд�����ݷ���ֵ
	
	
	///< ȷ����ʼ����ȷִ�к��ܽ���FLASH��̲�����FLASH��ʼ�������ʱ��,����ģʽ���ã�
	FlashWriteDataResult = 1;//Flashд�����ݷ���ֵ
	
	if(FlashWriteDataResult == 1)//Flashд�����ݷ���ֵ
	{
		FlashWriteWaitCount = 0;
		while(Ok != Flash_Init(12, TRUE))
		{
			if(FlashWriteWaitCount++ >= 100)
			{
				FlashWriteDataResult = 0;//Flashд�����ݷ���ֵ
				break;
			}
		}
		if(FlashWriteDataResult == 1)//Flashд�����ݷ���ֵ
		{
			if(FlashWriteDataAddress <= (FLASH_EEPROM_MAX_ADDR - FLASH_APP1_ADDR))
			{//��ַҪ�ںϷ���Χ
				FlashWriteDataAddress = FlashWriteDataAddress + FLASH_APP1_ADDR;
			}
			else
			{
				FlashWriteDataResult = 0;//Flashд�����ݷ���ֵ
			}
			if(FlashWriteDataResult == 1)//Flashд�����ݷ���ֵ
			{
				if((FlashWriteDataAddress%2)!=0)
				{//д���ַ������ż��
					FlashWriteDataAddress=FlashWriteDataAddress+1;
				}
				if((FlashWriteDataBufLen%2)!=0)
				{//д�볤�Ȳ����Ļ���+1
					FlashWriteDataBufLen=FlashWriteDataBufLen+1;
				}
				
				//��ҳ����
				if((FlashWriteDataAddress%FLASH_PAGE_SIZE)==0)//˵����ҳ���׵�ַ����ʱ���в���
				{
					FlashWriteWaitCount = 0;///< FLASHĿ����������
					while(Ok != Flash_SectorErase(FlashWriteDataAddress))
					{
						if(FlashWriteWaitCount++ >= 100)
						{
							FlashWriteDataResult = 0;//Flashд�����ݷ���ֵ
							break;
						}
					}
				}
				if(FlashWriteDataResult == 1)//Flashд�����ݷ���ֵ
				{
					for(FlashWriteDataNum[0]=0;FlashWriteDataNum[0]<FlashWriteDataBufLen;)
					{
						FlashWriteDataTemp=0;//Flashд��������ʱ�洢
						FlashWriteDataTemp=FlashWriteDataTemp+(FlashWriteDataBuf[FlashWriteDataNum[0]++]<<0);//Flashд��������ʱ�洢
						FlashWriteDataTemp=FlashWriteDataTemp+(FlashWriteDataBuf[FlashWriteDataNum[0]++]<<8);//Flashд��������ʱ�洢
						if(Flash_WriteHalfWord(FlashWriteDataAddress,FlashWriteDataTemp) != Ok)
						{//˵��д��ʧ��
							FlashWriteDataResult = 0;//Flashд�����ݷ���ֵ
							break;
						}
						else
						{
							FlashWriteDataAddress+=2;
						}
					}
				}
			}
		}
	}
	
	
	
	
	return FlashWriteDataResult;//Flashд�����ݷ���ֵ
}
