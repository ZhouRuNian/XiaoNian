#ifndef _FLASH_IAP_H
#define _FLASH_IAP_H

#define FLASH_FIRMWARE_ADDR		0x00000000  	//固件程序起始地址
#define FLASH_APP1_ADDR				0x00005000  	//第一个应用程序起始地址(存放在FLASH)
#define FLASH_PAGE_SIZE       0x200


typedef  void (*iapfun)(void);				//定义一个函数类型的参数.

typedef struct
{
	unsigned char write_buf[256];  //IAP写入缓存
	unsigned long write_addr;      //IAP写入地址
	unsigned int  write_len;       //IAR写入长度
	unsigned char comm_Keyaddr;    //命令数据加密地址
}iap;
extern iap IAP;
void iap_load_app(unsigned int appxaddr);			//执行flash里面的app程序
void iap_load_appsram(unsigned int appxaddr);		//执行sram里面的app程序
void iap_write_appbin(unsigned int appxaddr,unsigned char *appbuf,unsigned int applen);	//在指定地址开始,写入bin
__asm void MSR_MSP(unsigned int addr);
__asm void INTX_DISABLE(void);

__asm void INTX_ENABLE(void);//开启所有中断
void IAP_Write(unsigned long addr,unsigned int len,unsigned char *buf);
void IAP_Read(unsigned long addr,unsigned int len,unsigned char *p);



#endif
