/*
 * BootLoader.h
 *
 *  Created on: Feb 23, 2024
 *      Author: Ahmed Ashraf
 */

#ifndef INC_BOOTLOADER_H_
#define INC_BOOTLOADER_H_

#include "usart.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "crc.h"


#define BL_Debug_Usart					&huart1
#define BL_Host_Cummunication_Usart		&huart2
#define Uart_MAX_DELAY					0XFFFF
#define Host_Buffer_recevied_Length		200
#define Host_Packet_recevied_Length		1
#define CRC_handler						&hcrc
#define CRC_Size_Byte					4
#define ACK_Length						2
#define NACK_Length						1
/*read the boot loader version*/
#define CBL_GET_VER_CMD              0x10
#define CBL_GET_HELP_CMD             0x11
#define CBL_GET_CID_CMD              0x12
/* Get Read Protection Status */
#define CBL_GET_RDP_STATUS_CMD       0x13
#define CBL_GO_TO_ADDR_CMD           0x14
#define CBL_FLASH_ERASE_CMD          0x15
#define CBL_MEM_WRITE_CMD            0x16
/* Enable/Disable Write Protection */
#define CBL_ED_W_PROTECT_CMD         0x17
#define CBL_MEM_READ_CMD             0x18
/* Get Sector Read/Write Protection Status */
#define CBL_READ_SECTOR_STATUS_CMD   0x19
#define CBL_OTP_READ_CMD             0x20
/* Change Read Out Protection Level */
#define CBL_CHANGE_ROP_Level_CMD     0x21
/* Execute the user application (go to APP address) */
#define CBL_JumpTO_User_APP_CMD      0x22
/*boot loader information*/
#define CBL_VENDOR_ID                100
#define CBL_SW_MAJOR_VERSION         1
#define CBL_SW_MINOR_VERSION         1
#define CBL_SW_PATCH_VERSION         0

#define CBL_SEND_NACK                0xAB
#define CBL_SEND_ACK                 0xCD

#define NUM_BL_CMD					 12

#define FLASH_APP_Address			 FLASH_BASE	////

#define BL_DEBUG					 0xFF
#define BL_NO_DEBUG					 0x00
#define CODE_DEBUG	(BL_DEBUG)

/* available addresses */
#define FLASH_SIZE					(64*1024)	/// back to stm utility to find out the size
#define SRAM_SIZE					(20*1024)

#define FLASH_ADD_END				(FLASH_BASE+FLASH_SIZE)
#define SRAM_ADD_END				(SRAM_BASE+SRAM_SIZE)
/* flash pages [0-->127] */
#define Page_size							0x400 				/*1 Kbyte*/
#define Flash_Page_Base(Page_number)		(Page_number * Page_size + FLASH_BASE)
#define Number_OF_Pages_MAX					128
#define Successful_Erase					0xFFFFFFFF

#define RDP_LEVEL_0							OB_RDP_LEVEL_0
#define RDP_LEVEL_1							OB_RDP_LEVEL_1

typedef void (*Ptr_Function) (void);

typedef enum
{
	BL_NACK =0	,
	BL_ACK
}BL_status;

typedef enum
{
	CRC_NOK =0	,
	CRC_OK
}BL_CRC_status;

typedef enum
{
	ADD_Not_Available = 0 ,
	ADD_Available = 1
}BL_ADD_Verification;

typedef enum
{
	FLASH_ERASE_NOK = 0 ,
	FLASH_ERASE_OK = 1
}BL_FLASH_ERASE;

typedef enum
{
	Memory_Write_NOK = 0 ,
	Memory_Write_OK = 1
}BL_Memory_Write;

typedef enum
{
	RDP_NOK = 0 ,
	RDP_OK = 1
}BL_RDP_status;

//void BL_Print_Message(uint8_t* message,...);
BL_status fetch_data(void);

#endif /* INC_BOOTLOADER_H_ */
