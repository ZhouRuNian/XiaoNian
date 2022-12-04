#ifndef _WHOLE_LIBRARY_H_
#define _WHOLE_LIBRARY_H_


#define BOARD_TYPE 0//�������ͣ�0Ϊ˫ģ�壬1Ϊ���߰�

/******************************************************************************
 �ٷ���
 ******************************************************************************/
#include "gpio.h"
#include "flash.h"
#include "uart.h"
#include "dmac.h"
#include "lptim.h"
#include "lpm.h"
#include "bt.h"






/******************************************************************************
 �Զ����
 ******************************************************************************/
 
#include "CRC-8.h"
#include "DELAY.h"
#include "LED.h"
#include "FLASH_IAP.h"
#include "UART_MAIN.h"
#include "EEPROM.h"
#include "UART_READER.h"
#include "IWDG.h"
#include "VOLTAGE.h"
#include "TIMER.h"





#define MCU_VERSION	"wd1.2"//���豸�汾


#define IWDG_SWITCH	1//���Ź����أ�0Ϊ�رտ��Ź���1Ϊ�������Ź�


#define TEST_LED_SWITCH	1//����LED���أ�0Ϊ�رգ�1Ϊ����
#define USER_UART_PORT	0//ʹ�ô��ڶ˺ţ�0ΪUART0��1ΪUART1
#define USER_ADC_SWITCH	1	//ʹ��ADC��0Ϊ��ʹ�ã�1Ϊʹ��	ʹ�ú�LED1�ò���

#if IWDG_SWITCH	== 1//���Ź����أ�0Ϊ�رտ��Ź���1Ϊ�������Ź�
#define IWDG_EM6323_SWITCH	1//���Ź�EM6323���أ�0Ϊ�رտ��Ź���1Ϊ�������Ź�
#define SLEEP_MODE_SWITCH	1//˯��ģʽ���أ�0Ϊ�رգ�1Ϊ����
#else
#define IWDG_EM6323_SWITCH	0//���Ź�EM6323���أ�0Ϊ�رտ��Ź���1Ϊ�������Ź�
#define SLEEP_MODE_SWITCH	0//˯��ģʽ���أ�0Ϊ�رգ�1Ϊ����
#endif





#define LT8900_SEND_BUF_NUM_MAX					180                //LT8900���ͻ�����������
#define LT8900_RECEIVE_BUF_NUM_MAX			180                //LT8900���ջ�����������
#define UART1_SEND_BUF_NUM_MAX					180                //���ڷ��ͻ�����������
#define UART1_RECEIVE_BUF_NUM_MAX				180                //���ڽ��ջ�����������
#define DORMANCY_SEND_BUF_NUM_MAX				80                //���߷��ͻ�����������

typedef struct{
	volatile unsigned char DeviceTestMode;//�豸����ģʽ��0Ϊ����ģʽ��1ΪK30V���ߵװ����ģʽ
	volatile unsigned char MCUResetStatus;//MCU��λ״̬��0Ϊ����״̬��1Ϊ��Ҫ��λ״̬
	
}CURRENT_STATUS;//��ǰ״̬

typedef struct{
	volatile unsigned char UART1SendDataStatus;//UART1��������״̬��0Ϊ����״̬��1Ϊ��Ҫ���ͣ�2Ϊ���ڷ���
	volatile unsigned char UART1SendBuf[UART1_SEND_BUF_NUM_MAX];//UART1���ͻ�����
	volatile unsigned char UART1SendBufNum;//UART1���ͻ������±��
	volatile unsigned char UART1SendBufCRC;//UART1���ͻ�����CRC
	volatile unsigned char DMASendBuf[UART1_SEND_BUF_NUM_MAX];//DMA���ͻ�����
	volatile unsigned char DMASendBufNum;//DMA���ͻ������±��
	volatile unsigned char UART1ReceiveBuf[UART1_RECEIVE_BUF_NUM_MAX];//UART1���ջ�����
	volatile unsigned char UART1ReceiveBufNum;//UART1���ջ������±��
	volatile unsigned char UART1ReceiveBufCRC;//UART1���ջ�����CRC
	volatile unsigned char UncertainData[10];//��������
	
	
	
	volatile unsigned char UART1CommunicationTimeOut[2];//UART1ͨѶ��ʱ
}UART_INFO;//UART��Ϣ


#define UpgradeDataBufMax				128//�������ݻ�����������
typedef struct{
	volatile unsigned char UpgradeDeviceStatus;//����״̬��0Ϊ������1Ϊ��������
	volatile unsigned char CommunicationPortNum;//����ͨѶ�˿ڣ�1Ϊʶ��崮�ڣ�2Ϊ��ͷ���ڣ����ڱ�ʶ��ǰ����ͨѶ���ڵĶ˿�
	volatile unsigned int UpgradeDeviceType;//��ǰ�����豸���ͣ�0Ϊ�̼���1Ϊ������
	volatile unsigned long long int UpgradePacketAddress[2];//��ǰ��������ַ
	volatile unsigned int UpgradePacketLen;//��ǰ����������
	volatile unsigned char UpgradeDataBuf[UpgradeDataBufMax];//�������ݻ�����
	volatile unsigned char UpgradeDataBufNum;//�������ݻ������±��
	
	
	volatile unsigned char CreateCommand;//��������
	volatile unsigned char CreateFaultCode;//���ɹ�����
	volatile unsigned char CreateDataBuf[100];//��������
	volatile unsigned char CreateDataBufNum;//���������±��
	
	
	volatile unsigned char UpdateReplyResult;//�����ظ������0Ϊʧ�ܣ�1Ϊ�ɹ�
	
	volatile unsigned char UncertainData[10];//��������
	

	
	
	
	volatile unsigned char UART1CommunicationTimeOut[2];//UART1ͨѶ��ʱ
}UPGRADE_INFO;//������Ϣ




typedef struct{
	volatile unsigned char WorkTimeCount[2];//������ʱ
	volatile unsigned char UpgradeWaitTimeCount[2];//�����ȴ���ʱ
	volatile unsigned char DelayEmptyUARTReceiveBufCount[2];//��ʱ��մ��ڽ��ջ�����
	volatile unsigned char MCUResetCountdown[2];//MCU��λ����ʱ
	
	volatile unsigned char LEDJumpCount[2];//
	volatile unsigned char AutoInitUartTime[2];//�Զ���ʼ�����ڼ�ʱ
	volatile unsigned char TurnOnDiscernLightStatus[3];//��ʶ���ƹ�״̬��0Ԫ��(0Ϊ����״̬��1Ϊ�ȴ��򿪵ƹ⣬2Ϊ��Ҫ�򿪵ƹ⣬3Ϊ�ȴ��رյƹ⣬4Ϊ��Ҫ�رյƹ�)��1Ԫ��Ϊ��ʱ��3Ϊ��������
	volatile unsigned char TurnOnDiscernLightTimeOut[3];//��ʶ���ƹⳬʱ��ʱ
	
}AUTO_WORK_INFO;//�Զ�������Ϣ




typedef struct{
	
		
		CURRENT_STATUS CurrentStatus;//��ǰ״̬
		UART_INFO UartInfo;//UART��Ϣ
		UART_INFO Uart1Info;//UART1��Ϣ
		AUTO_WORK_INFO AutoWorkInfo;//�Զ�������Ϣ
		UPGRADE_INFO Upgrade;//������Ϣ
}MCU_WORK_INFO;//MCU������Ϣ



#define MCU_CONFIG_INFO_SYNC_MAX	13//McuConfigInfoͬ��ͷ����


#define VERSION_LEN_MAX 10//�汾��󳤶�
typedef struct{
							volatile unsigned char MasterDeviceID[4];//���豸ID
							volatile unsigned char AccessoryID[6];//���ID
							volatile unsigned char SerialNumbers[13];//���к�
							volatile unsigned char DiscernVersion[VERSION_LEN_MAX];//ʶ���汾
							volatile unsigned char DiscernVersionLen;//ʶ���汾����
							volatile unsigned char BaseBoardVersion[VERSION_LEN_MAX];//�װ�汾
							volatile unsigned char BaseBoardVersionLen;//�װ�汾����
							volatile unsigned char CurrentReaderPosi;//��ǰͨѶ��ͷ��λ
							volatile unsigned char CurrentChannel;//��ǰͨѶƵ��
							volatile unsigned char TungNum;//ϴ�ƶ���
							volatile unsigned char CameraCheckRange[2];//ʶ��Χ
							volatile unsigned char HightVoltageIntoSleepDelay;//�ߵ�ѹ��������ģʽ�ӳ�ʱ��
							volatile unsigned char MasterDeviceOnOffStatus;//���豸���ػ�״̬��1Ϊ�ػ�״̬��2Ϊ����״̬
							volatile unsigned char MasterDeviceFinishStatus;//���豸ϴ�ƽ���״̬��1Ϊ���ڻ�ȡ״̬��2Ϊ��ȡ�������ﵽ���߽����㷨
							volatile unsigned char WiFiSwitchStatus;//WiFi����״̬��0Ϊ������1Ϊ�رգ�2Ϊ����
							volatile unsigned char ServerConnectStatus;//����������״̬��0Ϊ������1Ϊδ���ӣ�2Ϊ������
							volatile unsigned char ServerOnlineStatus;//������ע��״̬��0Ϊ������1Ϊδע�ᣬ2Ϊ��ע��
							volatile unsigned char LightIntensity;//�ƹ�����
							volatile unsigned char AccessoryReceiveTimeOut;//������ճ�ʱʱ��(�ƹ���ʱʱ��)
}DEVICE_INFO;//�豸��Ϣ


typedef struct{
							volatile unsigned char Sync[MCU_CONFIG_INFO_SYNC_MAX];//ͬ��ͷ
							volatile unsigned char InfoLen;//��Ϣ����
	
							volatile unsigned char UpgradeStatus;//����״̬��0Ϊ����״̬��1Ϊ��Ҫ����״̬
							volatile unsigned char PowerOnStatus;//�ϵ�״̬��0Ϊ����״̬��1Ϊ�������״̬��2Ϊ׼������״̬
							
							volatile unsigned char BatteryProtectionStatus;//��ر���״̬��0Ϊ������1Ϊ���ڵ�ر���״̬
							
							DEVICE_INFO DeviceInfo;//�豸��Ϣ
	
	
							volatile unsigned char StartOverCount;//�������������ڱ�ǹ̼���������
							volatile unsigned char UndeterminedData[10];//��������
							volatile unsigned char INFO_CRCTemp;//��ϢУ��CRC��ʱ�洢
							volatile unsigned char INFO_CRC[2];//��ϢУ��CRC
}MCU_CONFIG_INFO;//MCU������Ϣ


/**
 ******************************************************************************
 ** \brief wdt�����λ���ж�����
 *****************************************************************************/
typedef enum en_wdt_func
{
    WdtResetEn    = 0,   ///<��λʹ��
    WdtIntEn      = 1,   ///<�ж�ʹ��
}en_wdt_func_t;

/**
 ******************************************************************************
 ** \brief wdt��ǰ����ʱ�������������Ͷ���
 *****************************************************************************/

typedef enum en_wdt_time
{
    WdtT1ms6   = 0u,       ///<1.6ms
    WdtT3ms2   = 1u,       ///<3.2ms
    WdtT6ms4   = 2u,       ///<6.4ms
    WdtT13ms   = 3u,       ///<13ms
    WdtT26ms   = 4u,       ///<26ms
    WdtT51ms   = 5u,       ///<51ms
    WdtT102ms  = 6u,       ///<102ms
    WdtT205ms  = 7u,       ///<205ms
    WdtT500ms  = 8u,       ///<500ms
    WdtT820ms  = 9u,       ///<820ms
    WdtT1s64   = 10u,      ///<1.64s
    WdtT3s28   = 11u,      ///<3.28s
    WdtT6s55   = 12u,      ///<6.55s
    WdtT13s1   = 13u,      ///<13.1s
    WdtT26s2   = 14u,      ///<26.2s
    WdtT52s4   = 15u,      ///<52.4s
}en_wdt_time_t;




extern MCU_WORK_INFO McuWorkInfo;//MCU������Ϣ
extern MCU_CONFIG_INFO McuConfigInfo;//MCU������Ϣ
extern const char MCU_CONFIG_INFO_SYNC[MCU_CONFIG_INFO_SYNC_MAX];//McuConfigInfoͬ��ͷ
extern const char LT8900SyncSend[7];//LT8900ͬ��ͷ�����ͣ�
extern const char K30VSyncSend[7];//K30Vͬ��ͷ�����ͣ�
extern const char K30VSyncReveive[7];//K30Vͬ��ͷ(����)




extern uint32_t SystemCoreClock;

extern unsigned char iap_load_app_status;//��ת��Ӧ��״̬��0Ϊ��Ҫ��ת��1Ϊ��ֹ��ת




extern unsigned char ErrorFlag;//������

extern void MCURestart(void);//MCU����
extern void MCUAutoRestartDeal(unsigned char DealCount);//MCU����



extern unsigned char WatchDogEM6323DelayFeed;
extern void WatchDogFeed(unsigned char FeedFjlag);//���Ź�ι��
extern void WatchDogEM6323Feed(void);//���Ź�EM6323оƬι��



extern void StartUpAllMcuIoInit(void);//�ϵ�����MCU io �ڳ�ʼ��

#endif


