#include "WHOLE_LIBRARY.h"



volatile unsigned int FLASH_EEPROM_BASE_ADDR=0;//定义flash eeprom存储起始位置
volatile unsigned int FLASH_EEPROM_MAX_ADDR=0;//Flash eeprom存储最大位置
volatile unsigned int FLASH_EEPROM_MCU_INFO_BASE_ADDR = 0;//定义flash eeprom存储MCU信息起始位置
volatile unsigned char FlashEepromAutoSaveScanf[2];//flash eeprom自动保存扫描
volatile unsigned char FlashInitStatus = 0;//初始化Flash状态，0为没初始化，1为已经初始化





/******************************************************************************************
  * @brief  获取flash大小
  * @param  无
  * @retval 返回flash大小
******************************************************************************************/
unsigned short int GetFlashSize(void)//获取flash大小
{
	volatile unsigned short int FlashSizeTemp=0;
//	#ifdef STM32F0XX
//	FlashSizeTemp = *(unsigned short int*)(0x1FFFF7CC);//闪存容量寄存器
//	#else
//	FlashSizeTemp = *(unsigned short int*)(0x1FFFF7E0);//闪存.容量寄存器
//	#endif
	FlashSizeTemp = 64;
	return FlashSizeTemp;
}


///******************************************************************************************
//  * @brief  获取芯片ID
//  * @param  *McuIDBuf：芯片ID存储数组
//  * @retval 无
//******************************************************************************************/
//void GetMcuID(unsigned int *McuIDBuf)//获取芯片ID
//{
//	unsigned char GetMcuIDNum[2];
//	volatile unsigned short int McuIDBufTemp[2];
//	for(GetMcuIDNum[0]=0;GetMcuIDNum[0]<4;GetMcuIDNum[0]++)
//	{
//		McuIDBuf[GetMcuIDNum[0]]=*(unsigned short int*)(0x1FFFF7AC+GetMcuIDNum[0]*2);//必须是双数地址进行操作
//	}
//	for(GetMcuIDNum[0]=0;GetMcuIDNum[0]<4;GetMcuIDNum[0]++)
//	{
//		McuIDBuf[GetMcuIDNum[0]]	&= 0xFF;
//	}
//	
//}




/******************************************************************************************
  * @brief  eeprom初始化
  * @param  无
  * @retval 无
******************************************************************************************/
unsigned char EepromInit(void)//eeprom初始化
{
	///< 开启FLASH外设时钟
	Sysctrl_SetPeripheralGate(SysctrlPeripheralFlash, TRUE);
	FLASH_EEPROM_MAX_ADDR		=	0x00000000+(GetFlashSize()*1024);//Flash eeprom存储最大位置
	FLASH_EEPROM_BASE_ADDR	=	FLASH_EEPROM_MAX_ADDR-FLASH_EEPROM_SIZE;//定义flash eeprom存储起始位置
	FLASH_EEPROM_MCU_INFO_BASE_ADDR	= FLASH_EEPROM_BASE_ADDR;//定义flash eeprom存储MCU信息起始位置
	while(Ok != Flash_Init(12, TRUE))
	{
			;
	}
	FlashInitStatus = 1;//初始化Flash状态，0为没初始化，1为已经初始化
	return 0;
}




/******************************************************************************************
  * @brief  EEPROM读取重要信息
  * @param  无
  * @retval 
******************************************************************************************/
unsigned char EepromReadImportantInfo(void)//EEPROM读取重要信息
{
	unsigned char EepromReadImportantInfoNum[2];
	volatile unsigned short int *EepromReadImportantInfoAddress;//EEPROM读取重要信息起始地址
	unsigned char EepromReadImportantInfoResult=0;//EEPROM读取重要信息返回值
	volatile unsigned short int EepromReadImportantInfoBuf[1];//EEPROM读取重要信息缓冲区
	volatile unsigned char *pMcuConfigInfo;//重要信息指针
	volatile unsigned char McuConfigInfoLen=sizeof(McuConfigInfo);//重要信息长度
	unsigned char EepromReadImportantInfoCRC=0;//EEPROM读取重要信息CRC
	volatile unsigned char CRCStartIndex = 0;//
	

	
	pMcuConfigInfo=&McuConfigInfo.Sync[0];//重要信息指针
	EepromReadImportantInfoAddress=(unsigned short int *)FLASH_EEPROM_MCU_INFO_BASE_ADDR;//EEPROM读取重要信息起始地址

	CRCStartIndex = 3;
	if((McuConfigInfoLen%2)!=0)//重要信息长度
	{//单数加上多一个数据
		McuConfigInfoLen=McuConfigInfoLen+1;//重要信息长度
		CRCStartIndex = 4;
	}
	for(EepromReadImportantInfoNum[0]=0;EepromReadImportantInfoNum[0]<McuConfigInfoLen;)
	{
		EepromReadImportantInfoBuf[0]	= *EepromReadImportantInfoAddress++;//EEPROM读取重要信息缓冲区
		pMcuConfigInfo[EepromReadImportantInfoNum[0]++]=(EepromReadImportantInfoBuf[0]>>8)&0xFF;//重要信息指针
		pMcuConfigInfo[EepromReadImportantInfoNum[0]++]=(EepromReadImportantInfoBuf[0]>>0)&0xFF;//重要信息指针
	}
	
	McuConfigInfo.INFO_CRCTemp = Get_Crc8_LookUp(&McuConfigInfo.Sync[0],McuConfigInfoLen-CRCStartIndex,0,CRC_8_TAB);//信息校验CRC临时存储
	if(	(McuConfigInfo.INFO_CRC[0] !=	(McuConfigInfo.INFO_CRCTemp>>0x04))//信息校验CRC
		||(McuConfigInfo.INFO_CRC[1] !=	(McuConfigInfo.INFO_CRCTemp&0x0F))//信息校验CRC
	)
	{//进到这里说明校验不通过
		memset(&McuConfigInfo,0,sizeof(McuConfigInfo));//直接清空所有数据，重新存储
//		McuConfigInfo.StartOverCount = 250;//启动次数，用于标记固件启动次数
//		McuConfigInfo.UpgradeStatus = 1;//升级状态，0为正常状态，1为需要升级状态
	}
	
	return EepromReadImportantInfoResult;//EEPROM读取重要信息返回值
}



/******************************************************************************************
  * @brief  EEPROM存储重要信息
  * @param  无
  * @retval 返回0说明清空失败，返回1说明清空成功
******************************************************************************************/
unsigned char EepromSaveImportantInfo(void)//EEPROM存储重要信息
{
	unsigned char EepromSaveImportantInfoNum[2];
	volatile unsigned int EepromSaveImportantInfoAddress=0;//EEPROM存储重要信息起始地址
	unsigned char EepromSaveImportantInfoResult=0;//EEPROM存储重要信息返回值
	unsigned short int EepromSaveImportantInfoBuf[1];//EEPROM存储重要信息缓冲区
	volatile unsigned char *pMcuConfigInfo;//重要信息指针
	volatile unsigned char McuConfigInfoLen=sizeof(McuConfigInfo);//重要信息长度
	volatile unsigned char CRCStartIndex = 0;//
	
	en_result_t FlashState;
	
	if(FlashInitStatus == 0)//初始化Flash状态，0为没初始化，1为已经初始化
	{
		EepromInit();//eeprom初始化
	}
	if(FLASH_EEPROM_MCU_INFO_BASE_ADDR == 0)//EEPROM存储重要信息起始地址
	{//存储地址不合法，就不存储
		return 0;
	}
	CRCStartIndex = 3;
	if((McuConfigInfoLen%2)!=0)//重要信息长度
	{//单数加上多一个数据
		McuConfigInfoLen=McuConfigInfoLen+1;//重要信息长度
		CRCStartIndex = 4;
	}
	for(EepromSaveImportantInfoNum[0]=0;EepromSaveImportantInfoNum[0]<MCU_CONFIG_INFO_SYNC_MAX;EepromSaveImportantInfoNum[0]++)
	{
		McuConfigInfo.Sync[EepromSaveImportantInfoNum[0]]=MCU_CONFIG_INFO_SYNC[EepromSaveImportantInfoNum[0]];//同步头
	}
	McuConfigInfo.InfoLen=McuConfigInfoLen;//信息长度
	
	McuConfigInfo.INFO_CRCTemp = Get_Crc8_LookUp(&McuConfigInfo.Sync[0],McuConfigInfoLen-CRCStartIndex,0,CRC_8_TAB);//信息校验CRC临时存储
	McuConfigInfo.INFO_CRC[0]	=	McuConfigInfo.INFO_CRCTemp>>0x04;//信息校验CRC
	McuConfigInfo.INFO_CRC[1]	=	McuConfigInfo.INFO_CRCTemp&0x0F;//信息校验CRC
	
	
	
	
	
	
	
	
	
	
	
	pMcuConfigInfo=&McuConfigInfo.Sync[0];//重要信息指针
	EepromSaveImportantInfoAddress=FLASH_EEPROM_MCU_INFO_BASE_ADDR;//EEPROM存储重要信息起始地址
	
	
	while(Ok != Flash_Init(12, TRUE))
	{
			;
	}
	FlashState = Flash_SectorErase(EepromSaveImportantInfoAddress);//擦除当前扇区页数据
	if(FlashState != Ok)
	{
		return 0;
	}
	
	for(EepromSaveImportantInfoNum[0]=0;EepromSaveImportantInfoNum[0]<McuConfigInfoLen;)
	{
		if((EepromSaveImportantInfoAddress%2)!=0)
		{//写入地址必须是偶数
			EepromSaveImportantInfoAddress=EepromSaveImportantInfoAddress+1;
		}
		EepromSaveImportantInfoBuf[0]	=		*pMcuConfigInfo++;
		EepromSaveImportantInfoBuf[0]	<<=	8;
		EepromSaveImportantInfoBuf[0]	+=	*pMcuConfigInfo++;
		FlashState = Flash_WriteHalfWord(EepromSaveImportantInfoAddress,EepromSaveImportantInfoBuf[0]);//flash写入半字数据（16bit）
		if(FlashState != Ok)
		{
			return 0;
		}
		EepromSaveImportantInfoAddress += 2;
		EepromSaveImportantInfoNum[0]	+=	2;
	}
	return EepromSaveImportantInfoResult;//EEPROM存储重要信息返回值
}




/******************************************************************************************
  * @brief  Flash写入数据
	* @param  无
	* @retval 返回0表示写入失败，返回1表示写入成功
******************************************************************************************/
unsigned char FlashWriteData(unsigned int FlashWriteDataAddress,unsigned char *FlashWriteDataBuf,unsigned char FlashWriteDataBufLen)//Flash写入数据
{
	unsigned int FlashWriteDataNum[2];
	unsigned int FlashWriteDataTemp=0;//Flash写入数据临时存储
//	unsigned int FlashWriteDataStatus=0;//Flash写入数据状态
	unsigned int EraseUserFlashStatus=0;//擦除用户FLASH状态
	unsigned char FlashWriteWaitCount = 0;
	unsigned char FlashWriteDataResult = 0;//Flash写入数据返回值
	
	
	///< 确保初始化正确执行后方能进行FLASH编程操作，FLASH初始化（编程时间,休眠模式配置）
	FlashWriteDataResult = 1;//Flash写入数据返回值
	
	if(FlashWriteDataResult == 1)//Flash写入数据返回值
	{
		FlashWriteWaitCount = 0;
		while(Ok != Flash_Init(12, TRUE))
		{
			if(FlashWriteWaitCount++ >= 100)
			{
				FlashWriteDataResult = 0;//Flash写入数据返回值
				break;
			}
		}
		if(FlashWriteDataResult == 1)//Flash写入数据返回值
		{
			if(FlashWriteDataAddress <= (FLASH_EEPROM_MAX_ADDR - FLASH_APP1_ADDR))
			{//地址要在合法范围
				FlashWriteDataAddress = FlashWriteDataAddress + FLASH_APP1_ADDR;
			}
			else
			{
				FlashWriteDataResult = 0;//Flash写入数据返回值
			}
			if(FlashWriteDataResult == 1)//Flash写入数据返回值
			{
				if((FlashWriteDataAddress%2)!=0)
				{//写入地址必须是偶数
					FlashWriteDataAddress=FlashWriteDataAddress+1;
				}
				if((FlashWriteDataBufLen%2)!=0)
				{//写入长度不够的话，+1
					FlashWriteDataBufLen=FlashWriteDataBufLen+1;
				}
				
				//单页擦除
				if((FlashWriteDataAddress%FLASH_PAGE_SIZE)==0)//说明是页的首地址，此时进行擦除
				{
					FlashWriteWaitCount = 0;///< FLASH目标扇区擦除
					while(Ok != Flash_SectorErase(FlashWriteDataAddress))
					{
						if(FlashWriteWaitCount++ >= 100)
						{
							FlashWriteDataResult = 0;//Flash写入数据返回值
							break;
						}
					}
				}
				if(FlashWriteDataResult == 1)//Flash写入数据返回值
				{
					for(FlashWriteDataNum[0]=0;FlashWriteDataNum[0]<FlashWriteDataBufLen;)
					{
						FlashWriteDataTemp=0;//Flash写入数据临时存储
						FlashWriteDataTemp=FlashWriteDataTemp+(FlashWriteDataBuf[FlashWriteDataNum[0]++]<<0);//Flash写入数据临时存储
						FlashWriteDataTemp=FlashWriteDataTemp+(FlashWriteDataBuf[FlashWriteDataNum[0]++]<<8);//Flash写入数据临时存储
						if(Flash_WriteHalfWord(FlashWriteDataAddress,FlashWriteDataTemp) != Ok)
						{//说明写入失败
							FlashWriteDataResult = 0;//Flash写入数据返回值
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
	
	
	
	
	return FlashWriteDataResult;//Flash写入数据返回值
}
