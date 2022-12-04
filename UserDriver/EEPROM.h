#ifndef __EEPROM_H
#define __EEPROM_H
#include "WHOLE_LIBRARY.h"


#define FLASH_EEPROM_PAGE	1			//flash eepromҳ
#define FLASH_EEPROM_SIZE	(FLASH_EEPROM_PAGE*1024)//flash eeprom��С����λΪbyte��//FLASH_EEPROM_PAGE*1024
#define FLASH_EEPROM_PAGE_DATA_NUM	170		//flash eepromһҳ���ݸ���
#define FLASH_EEPROM_PAGE_DATA_SIZE	(FLASH_EEPROM_PAGE_DATA_NUM*6)//flash eepromһҳ���ݳ��ȣ���160�����ݣ�1������6byte//FLASH_EEPROM_PAGE_DATA_NUM*6



extern volatile unsigned int FLASH_EEPROM_BASE_ADDR;//����flash eeprom�洢��ʼλ��
extern volatile unsigned int FlashEepromBufLen;//flash eeprom��������ǰ����
extern volatile unsigned int FlashEepromBufStringPosi;//flash eeprom�������ַ�����Ӧλ��
extern volatile unsigned int FLASH_EEPROM_MAX_ADDR;//Flash eeprom�洢���λ��
extern volatile unsigned int FLASH_EEPROM_MCU_INFO_BASE_ADDR;//����flash eeprom�洢MCU��Ϣ��ʼλ��
extern volatile unsigned char FlashEepromAutoSaveScanf[2];//flash eeprom�Զ�����ɨ��




extern unsigned short int GetFlashSize(void);//��ȡflash��С
extern void GetMcuID(unsigned int *McuIDBuf);//��ȡоƬID
extern unsigned char EepromInit(void);//eeprom��ʼ��
extern unsigned char EepromEraseImportantInfo(void);//EEPROM������Ҫ��Ϣ
extern unsigned char EepromSaveImportantInfo(void);//EEPROM�洢��Ҫ��Ϣ
extern unsigned char EepromReadImportantInfo(void);//EEPROM��ȡ��Ҫ��Ϣ
extern unsigned char WorkInfoUpdateImportantInfo(void);//������Ϣ���µ���Ҫ��Ϣ
extern unsigned char ImportantInfoUpdateWorkInfo(void);//��Ҫ��Ϣ���µ�������Ϣ

extern unsigned char FindkNonzeroIndex(unsigned char *FindBuf,unsigned char FindBufLen);//Ѱ�ҷ�������

extern unsigned char AutoSaveImportantInfo(void);//�Զ�������Ҫ��Ϣ
extern unsigned char McuWorkInfoAutoDeal(void);//MCU������Ϣ�Զ�����





extern unsigned char FlashWriteData(unsigned int FlashWriteDataAddress,unsigned char *FlashWriteDataBuf,unsigned char FlashWriteDataBufLen);//Flashд������
#endif

