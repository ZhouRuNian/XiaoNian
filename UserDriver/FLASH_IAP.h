#ifndef _FLASH_IAP_H
#define _FLASH_IAP_H

#define FLASH_FIRMWARE_ADDR		0x00000000  	//�̼�������ʼ��ַ
#define FLASH_APP1_ADDR				0x00005000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
#define FLASH_PAGE_SIZE       0x200


typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.

typedef struct
{
	unsigned char write_buf[256];  //IAPд�뻺��
	unsigned long write_addr;      //IAPд���ַ
	unsigned int  write_len;       //IARд�볤��
	unsigned char comm_Keyaddr;    //�������ݼ��ܵ�ַ
}iap;
extern iap IAP;
void iap_load_app(unsigned int appxaddr);			//ִ��flash�����app����
void iap_load_appsram(unsigned int appxaddr);		//ִ��sram�����app����
void iap_write_appbin(unsigned int appxaddr,unsigned char *appbuf,unsigned int applen);	//��ָ����ַ��ʼ,д��bin
__asm void MSR_MSP(unsigned int addr);
__asm void INTX_DISABLE(void);

__asm void INTX_ENABLE(void);//���������ж�
void IAP_Write(unsigned long addr,unsigned int len,unsigned char *buf);
void IAP_Read(unsigned long addr,unsigned int len,unsigned char *p);



#endif
