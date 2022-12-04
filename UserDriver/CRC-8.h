/****************************************Copyright (c)**************************************************
**                               Microwide Development Co.,LTD.
**                                 Embedded Systems Division 
**                                    
**
**--------------File Info-------------------------------------------------------------------------------
** File name:			CRC-8.h
** Last modified Date:  2013-01-01
** Last Version:		1.0
** Descriptions:		CRC-8??????
**
**------------------------------------------------------------------------------------------------------
** Created by:			Tengxinxin
** Created date:		2013-01-01
** Version:				1.0
** Descriptions:		????CRC-8???
**
********************************************************************************************************/
#ifndef _CRC_8_h_
#define	_CRC_8_h_

#define CRC_8	0x31       /* x8+x5+x4+1*/
//
extern const unsigned char CRC_8_TAB[];
//
/*********************************************************************************************************
** Function name:			Get_Crc8_LookUp
**
** Descriptions:			?????CRC?,???????,????????“CRC16 ??.txt”
**							
** input parameters:		pData		->	??????????
**							nLen		->	????
**							Crc			->	??Crc?
**							pCrc_Tab	->	CRC-16????
**
** Returned value:			CRC?					
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Tengxinxin
** Created Date:			2013-01-01
**-------------------------------------------------------------------------------------------------------
** Modified by:				Tengxinxin
** Modified date:			2013-01-05
** Descriptions:			????Crc??,????????
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern unsigned char Get_Crc8_LookUp(const volatile unsigned char *pData, unsigned short nLen, unsigned char Crc, const unsigned char *pCrc_Tab);
/*********************************************************************************************************
** Function name:			Build_Crc8_Tab
**
** Descriptions:			??CRC8????,????:??0-255???8CRC???
**							
**							
** input parameters:		pTab		->	??????????,??256??
**							gEnpoly		->	gEnpoly??????????
**
** Returned value:			None					
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Tengxinxin
** Created Date:			2013-01-01
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void Build_Crc8_Tab(unsigned char *pTab, unsigned char gEnpoly);
/*********************************************************************************************************
** Function name:			Block_CRC8_Algorithm
**
** Descriptions:			??CRC8???,??bit????
**							
**							
** input parameters:		pData		->	??????????
**							nLen		->	gEnpoly??????????
**							gEnpoly		->	????
**
** Returned value:			None					
**         
** Used global variables:	None
** Calling modules:			None
**
** Created by:				Tengxinxin
** Created Date:			2013-01-01
**-------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern unsigned char Block_CRC8_Algorithm(const unsigned char *pData, unsigned short nLen, unsigned char gEnpoly);

extern unsigned char Get_crc8tab_LookUp(const volatile unsigned char *pData, unsigned short nLen, unsigned char Crc, const unsigned char *pCrc_Tab);

#endif	//_CRC_8_H_

