#ifndef _WHOLE_LIBRARY_H_
#define _WHOLE_LIBRARY_H_


#define BOARD_TYPE 0//板子类型，0为双模板，1为有线板

/******************************************************************************
 官方库
 ******************************************************************************/
#include "gpio.h"
#include "flash.h"
#include "uart.h"
#include "dmac.h"
#include "lptim.h"
#include "lpm.h"
#include "bt.h"






/******************************************************************************
 自定义库
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





#define MCU_VERSION	"wd1.2"//本设备版本


#define IWDG_SWITCH	1//看门狗开关，0为关闭看门狗，1为开启看门狗


#define TEST_LED_SWITCH	1//测试LED开关，0为关闭，1为开启
#define USER_UART_PORT	0//使用串口端号，0为UART0，1为UART1
#define USER_ADC_SWITCH	1	//使用ADC，0为不使用，1为使用	使用后LED1用不了

#if IWDG_SWITCH	== 1//看门狗开关，0为关闭看门狗，1为开启看门狗
#define IWDG_EM6323_SWITCH	1//看门狗EM6323开关，0为关闭看门狗，1为开启看门狗
#define SLEEP_MODE_SWITCH	1//睡眠模式开关，0为关闭，1为开启
#else
#define IWDG_EM6323_SWITCH	0//看门狗EM6323开关，0为关闭看门狗，1为开启看门狗
#define SLEEP_MODE_SWITCH	0//睡眠模式开关，0为关闭，1为开启
#endif





#define LT8900_SEND_BUF_NUM_MAX					180                //LT8900发送缓冲区最大个数
#define LT8900_RECEIVE_BUF_NUM_MAX			180                //LT8900接收缓冲区最大个数
#define UART1_SEND_BUF_NUM_MAX					180                //串口发送缓冲区最大个数
#define UART1_RECEIVE_BUF_NUM_MAX				180                //串口接收缓冲区最大个数
#define DORMANCY_SEND_BUF_NUM_MAX				80                //休眠发送缓冲区最大个数

typedef struct{
	volatile unsigned char DeviceTestMode;//设备测试模式，0为正常模式，1为K30V无线底板测试模式
	volatile unsigned char MCUResetStatus;//MCU复位状态，0为正常状态，1为需要复位状态
	
}CURRENT_STATUS;//当前状态

typedef struct{
	volatile unsigned char UART1SendDataStatus;//UART1发送数据状态，0为正常状态，1为需要发送，2为正在发送
	volatile unsigned char UART1SendBuf[UART1_SEND_BUF_NUM_MAX];//UART1发送缓冲区
	volatile unsigned char UART1SendBufNum;//UART1发送缓冲区下标号
	volatile unsigned char UART1SendBufCRC;//UART1发送缓冲区CRC
	volatile unsigned char DMASendBuf[UART1_SEND_BUF_NUM_MAX];//DMA发送缓冲区
	volatile unsigned char DMASendBufNum;//DMA发送缓冲区下标号
	volatile unsigned char UART1ReceiveBuf[UART1_RECEIVE_BUF_NUM_MAX];//UART1接收缓冲区
	volatile unsigned char UART1ReceiveBufNum;//UART1接收缓冲区下标号
	volatile unsigned char UART1ReceiveBufCRC;//UART1接收缓冲区CRC
	volatile unsigned char UncertainData[10];//待定数据
	
	
	
	volatile unsigned char UART1CommunicationTimeOut[2];//UART1通讯超时
}UART_INFO;//UART信息


#define UpgradeDataBufMax				128//升级数据缓冲区最大个数
typedef struct{
	volatile unsigned char UpgradeDeviceStatus;//升级状态，0为正常，1为正在升级
	volatile unsigned char CommunicationPortNum;//升级通讯端口，1为识别板串口，2为读头串口，用于标识当前升级通讯所在的端口
	volatile unsigned int UpgradeDeviceType;//当前升级设备类型，0为固件，1为主程序
	volatile unsigned long long int UpgradePacketAddress[2];//当前升级包地址
	volatile unsigned int UpgradePacketLen;//当前升级包长度
	volatile unsigned char UpgradeDataBuf[UpgradeDataBufMax];//升级数据缓冲区
	volatile unsigned char UpgradeDataBufNum;//升级数据缓冲区下标号
	
	
	volatile unsigned char CreateCommand;//生成命令
	volatile unsigned char CreateFaultCode;//生成故障码
	volatile unsigned char CreateDataBuf[100];//生成数据
	volatile unsigned char CreateDataBufNum;//生成数据下标号
	
	
	volatile unsigned char UpdateReplyResult;//升级回复结果，0为失败，1为成功
	
	volatile unsigned char UncertainData[10];//待定数据
	

	
	
	
	volatile unsigned char UART1CommunicationTimeOut[2];//UART1通讯超时
}UPGRADE_INFO;//升级信息




typedef struct{
	volatile unsigned char WorkTimeCount[2];//工作计时
	volatile unsigned char UpgradeWaitTimeCount[2];//升级等待计时
	volatile unsigned char DelayEmptyUARTReceiveBufCount[2];//延时清空串口接收缓冲区
	volatile unsigned char MCUResetCountdown[2];//MCU复位倒计时
	
	volatile unsigned char LEDJumpCount[2];//
	volatile unsigned char AutoInitUartTime[2];//自动初始化串口计时
	volatile unsigned char TurnOnDiscernLightStatus[3];//打开识别板灯光状态，0元素(0为正常状态，1为等待打开灯光，2为需要打开灯光，3为等待关闭灯光，4为需要关闭灯光)，1元素为延时，3为次数控制
	volatile unsigned char TurnOnDiscernLightTimeOut[3];//打开识别板灯光超时计时
	
}AUTO_WORK_INFO;//自动工作信息




typedef struct{
	
		
		CURRENT_STATUS CurrentStatus;//当前状态
		UART_INFO UartInfo;//UART信息
		UART_INFO Uart1Info;//UART1信息
		AUTO_WORK_INFO AutoWorkInfo;//自动工作信息
		UPGRADE_INFO Upgrade;//升级信息
}MCU_WORK_INFO;//MCU工作信息



#define MCU_CONFIG_INFO_SYNC_MAX	13//McuConfigInfo同步头长度


#define VERSION_LEN_MAX 10//版本最大长度
typedef struct{
							volatile unsigned char MasterDeviceID[4];//主设备ID
							volatile unsigned char AccessoryID[6];//配件ID
							volatile unsigned char SerialNumbers[13];//序列号
							volatile unsigned char DiscernVersion[VERSION_LEN_MAX];//识别板版本
							volatile unsigned char DiscernVersionLen;//识别板版本长度
							volatile unsigned char BaseBoardVersion[VERSION_LEN_MAX];//底板版本
							volatile unsigned char BaseBoardVersionLen;//底板版本长度
							volatile unsigned char CurrentReaderPosi;//当前通讯读头方位
							volatile unsigned char CurrentChannel;//当前通讯频道
							volatile unsigned char TungNum;//洗牌栋数
							volatile unsigned char CameraCheckRange[2];//识别范围
							volatile unsigned char HightVoltageIntoSleepDelay;//高电压进入休眠模式延迟时间
							volatile unsigned char MasterDeviceOnOffStatus;//主设备开关机状态，1为关机状态，2为开机状态
							volatile unsigned char MasterDeviceFinishStatus;//主设备洗牌结束状态，1为正在获取状态，2为获取牌数量达到或者进入算法
							volatile unsigned char WiFiSwitchStatus;//WiFi开关状态，0为正常，1为关闭，2为开启
							volatile unsigned char ServerConnectStatus;//服务器连接状态，0为正常，1为未连接，2为已连接
							volatile unsigned char ServerOnlineStatus;//服务器注册状态，0为正常，1为未注册，2为已注册
							volatile unsigned char LightIntensity;//灯光亮度
							volatile unsigned char AccessoryReceiveTimeOut;//配件接收超时时间(灯光延时时间)
}DEVICE_INFO;//设备信息


typedef struct{
							volatile unsigned char Sync[MCU_CONFIG_INFO_SYNC_MAX];//同步头
							volatile unsigned char InfoLen;//信息长度
	
							volatile unsigned char UpgradeStatus;//升级状态，0为正常状态，1为需要升级状态
							volatile unsigned char PowerOnStatus;//上电状态，0为正常状态，1为软件重启状态，2为准备升级状态
							
							volatile unsigned char BatteryProtectionStatus;//电池保护状态，0为正常，1为处于电池保护状态
							
							DEVICE_INFO DeviceInfo;//设备信息
	
	
							volatile unsigned char StartOverCount;//启动次数，用于标记固件启动次数
							volatile unsigned char UndeterminedData[10];//待定数据
							volatile unsigned char INFO_CRCTemp;//信息校验CRC临时存储
							volatile unsigned char INFO_CRC[2];//信息校验CRC
}MCU_CONFIG_INFO;//MCU配置信息


/**
 ******************************************************************************
 ** \brief wdt溢出后复位或中断配置
 *****************************************************************************/
typedef enum en_wdt_func
{
    WdtResetEn    = 0,   ///<复位使能
    WdtIntEn      = 1,   ///<中断使能
}en_wdt_func_t;

/**
 ******************************************************************************
 ** \brief wdt当前运行时间配置数据类型定义
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




extern MCU_WORK_INFO McuWorkInfo;//MCU工作信息
extern MCU_CONFIG_INFO McuConfigInfo;//MCU配置信息
extern const char MCU_CONFIG_INFO_SYNC[MCU_CONFIG_INFO_SYNC_MAX];//McuConfigInfo同步头
extern const char LT8900SyncSend[7];//LT8900同步头（发送）
extern const char K30VSyncSend[7];//K30V同步头（发送）
extern const char K30VSyncReveive[7];//K30V同步头(接收)




extern uint32_t SystemCoreClock;

extern unsigned char iap_load_app_status;//跳转到应用状态，0为需要跳转，1为禁止跳转




extern unsigned char ErrorFlag;//错误标记

extern void MCURestart(void);//MCU重启
extern void MCUAutoRestartDeal(unsigned char DealCount);//MCU重启



extern unsigned char WatchDogEM6323DelayFeed;
extern void WatchDogFeed(unsigned char FeedFjlag);//看门狗喂狗
extern void WatchDogEM6323Feed(void);//看门狗EM6323芯片喂狗



extern void StartUpAllMcuIoInit(void);//上电所有MCU io 口初始化

#endif


