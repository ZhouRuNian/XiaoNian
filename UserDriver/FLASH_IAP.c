#include "WHOLE_LIBRARY.h"


iap IAP;
iapfun Jump_To_Application; 

//��ת��Ӧ�ó����
//appxaddr:�û�������ʼ��ַ.
void iap_load_app(uint32_t appxaddr)
{
	if(((*(__IO uint32_t*)appxaddr)&0x2FFE0000)==0x20000000)	     //���ջ����ַ�Ƿ�Ϸ�.
	//if(1)
	{ 
		Jump_To_Application=(iapfun)*(__IO uint32_t*)(appxaddr+4);	 //�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(__IO uint32_t*)appxaddr);					                 //��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		Jump_To_Application();									                     //��ת��APP.
	}
}		 

//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(unsigned int addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}


//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI  
__asm void WFI_SET(void)
{
        WFI;                  
}
//�ر������ж�(���ǲ�����fault��NMI�ж�)
__asm void INTX_DISABLE(void)
{
        CPSID   I
        BX      LR          
}
//���������ж�
__asm void INTX_ENABLE(void)
{
        CPSIE   I
        BX      LR  
}









