#ifndef __EEPROM_H
#define __EEPROM_H
#include "WHOLE_LIBRARY.h"


#define FLASH_EEPROM_PAGE	1			//flash eeprom页
#define FLASH_EEPROM_SIZE	(FLASH_EEPROM_PAGE*1024)//flash eeprom大小（单位为byte）//FLASH_EEPROM_PAGE*1024
#define FLASH_EEPROM_PAGE_DATA_NUM	170		//flash eeprom一页数据个数
#define FLASH_EEPROM_PAGE_DATA_SIZE	(FLASH_EEPROM_PAGE_DATA_NUM*6)//flash eeprom一页数据长度，存160个数据，1个数据6byte//FLASH_EEPROM_PAGE_DATA_NUM*6



extern volatile unsigned int FLASH_EEPROM_BASE_ADDR;//定义flash eeprom存储起始位置
extern volatile unsigned int FlashEepromBufLen;//flash eeprom缓冲区当前长度
extern volatile unsigned int FlashEepromBufStringPosi;//flash eeprom缓冲区字符串对应位置
extern volatile unsigned int FLASH_EEPROM_MAX_ADDR;//Flash eeprom存储最大位置
extern volatile unsigned int FLASH_EEPROM_MCU_INFO_BASE_ADDR;//定义flash eeprom存储MCU信息起始位置
extern volatile unsigned char FlashEepromAutoSaveScanf[2];//flash eeprom自动保存扫描




extern unsigned short int GetFlashSize(void);//获取flash大小
extern void GetMcuID(unsigned int *McuIDBuf);//获取芯片ID
extern unsigned char EepromInit(void);//eeprom初始化
extern unsigned char EepromEraseImportantInfo(void);//EEPROM擦除重要信息
extern unsigned char EepromSaveImportantInfo(void);//EEPROM存储重要信息
extern unsigned char EepromReadImportantInfo(void);//EEPROM读取重要信息
extern unsigned char WorkInfoUpdateImportantInfo(void);//工作信息更新到重要信息
extern unsigned char ImportantInfoUpdateWorkInfo(void);//重要信息更新到工作信息

extern unsigned char FindkNonzeroIndex(unsigned char *FindBuf,unsigned char FindBufLen);//寻找非零索引

extern unsigned char AutoSaveImportantInfo(void);//自动保存重要信息
extern unsigned char McuWorkInfoAutoDeal(void);//MCU工作信息自动处理





extern unsigned char FlashWriteData(unsigned int FlashWriteDataAddress,unsigned char *FlashWriteDataBuf,unsigned char FlashWriteDataBufLen);//Flash写入数据
#endif

