#include "WHOLE_LIBRARY.h"


iap IAP;
iapfun Jump_To_Application; 

//跳转到应用程序段
//appxaddr:用户代码起始地址.
void iap_load_app(uint32_t appxaddr)
{
	if(((*(__IO uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)	     //检查栈顶地址是否合法.
	//if(1)
	{ 
		Jump_To_Application=(iapfun)*(__IO uint32_t*)(appxaddr+4);	 //用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(__IO uint32_t*)appxaddr);					                 //初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		Jump_To_Application();									                     //跳转到APP.
	}
}		 

//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(unsigned int addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
        WFI;                  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
        CPSID   I
        BX      LR          
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
        CPSIE   I
        BX      LR  
}









