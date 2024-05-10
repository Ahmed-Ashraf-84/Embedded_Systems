/*
 * BootLoader.c
 *
 *  Created on: Feb 23, 2024
 *      Author: Ahmed Ashraf
 */

#include "BootLoader.h"


static uint8_t Host_Buffer [Host_Buffer_recevied_Length];
static uint8_t BL_VERSION[4] = {CBL_VENDOR_ID,CBL_SW_MAJOR_VERSION,CBL_SW_MINOR_VERSION
						,CBL_SW_PATCH_VERSION};

static uint8_t BL_CMD[NUM_BL_CMD] = {CBL_GET_VER_CMD ,
							  CBL_GET_HELP_CMD ,
							  CBL_GET_CID_CMD ,
							  CBL_GET_RDP_STATUS_CMD ,
							  CBL_GO_TO_ADDR_CMD  ,
							  CBL_FLASH_ERASE_CMD ,
							  CBL_MEM_WRITE_CMD  ,
							  CBL_ED_W_PROTECT_CMD ,
							  CBL_MEM_READ_CMD  ,
							  CBL_READ_SECTOR_STATUS_CMD,
							  CBL_OTP_READ_CMD ,
							  CBL_CHANGE_ROP_Level_CMD } ;


static BL_status Bootloader_Get_Version(uint8_t* Host_Packet);
static BL_status Bootloader_Get_Help(uint8_t* Host_Packet);
static BL_status Bootloader_Get_Chip_ID(uint8_t* Host_Packet);
static BL_status Bootloader_JumpTo_APP(uint8_t* Host_Packet);
static BL_status Bootloader_JumpTo_ADD(uint8_t* Host_Packet);
static BL_status Bootloader_Flash_Erase(uint8_t* Host_Packet);
static BL_status Bootloader_Memory_Write(uint8_t* Host_Packet);
static BL_status Bootloader_Read_Protection_Level(uint8_t* Host_Packet);
static BL_status Bootloader_Change_Protection_Level(uint8_t* Host_Packet);
/*helper function*/
static BL_CRC_status Bootloader_CRC_Verify(uint8_t *pData, uint8_t Data_Length, uint32_t Host_CRC);
static void Bootloader_Send_NACK(void);
static void Bootloader_Send_ACK(uint8_t Replay_Len);
static void Bootloader_Send_Data_To_Host(uint8_t *BL_Buffer, uint8_t Data_Len);
static BL_ADD_Verification Bootloader_ADD_Verification(uint32_t Address);
static void BL_Print_Message(uint8_t* message,...);
static void print_ahmed (void)
{
	BL_Print_Message((uint8_t*)"Ahmed Ashraf");
}

static BL_FLASH_ERASE Perform_Flash_Erase(uint8_t Page_Number ,uint8_t Number_OF_Pages);
static BL_Memory_Write Perform_Memory_Write(uint32_t Destination_ADD ,uint32_t* APP_Data ,uint8_t Payload_len);
static BL_RDP_status Get_RDP_Level(uint8_t* RDP_Level);
static BL_RDP_status Change_ROP_Level(uint8_t RDP_Level);
/*helper function*/

static void BL_Print_Message(uint8_t* message,...)
{
	uint8_t Buffer[100]={0};
	/*create a variable-length argument list */
	va_list arguments;
	/*make the list from arguments passed after message */
	va_start(arguments,message);
	/*format a string and store it in a character array [Buffer]*/
	vsprintf((char*)Buffer,(const char*)message,arguments);
	/*send Buffer array using usart */
	HAL_UART_Transmit(BL_Debug_Usart, Buffer,sizeof(Buffer), Uart_MAX_DELAY);

}




BL_status fetch_data(void)
{
	BL_status status = BL_NACK ;
	HAL_StatusTypeDef HAL_Status = HAL_ERROR ;
	uint8_t Data_Length = 0 ;

	memset(Host_Buffer,0,Host_Buffer_recevied_Length);
	HAL_Status = HAL_UART_Receive(BL_Host_Cummunication_Usart, Host_Buffer,
								  Host_Packet_recevied_Length, Uart_MAX_DELAY);
	if(HAL_Status == HAL_OK)
	{
		Data_Length = Host_Buffer[0];
		HAL_Status = HAL_UART_Receive(BL_Host_Cummunication_Usart, Host_Buffer+1,
									  Data_Length, Uart_MAX_DELAY);
		if(HAL_Status == HAL_OK)
		{
			switch (Host_Buffer[1]){
				case CBL_GET_VER_CMD:
					BL_Print_Message((uint8_t*)"read the boot loader version\r\n");
					Bootloader_Get_Version(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_GET_HELP_CMD:
					BL_Print_Message((uint8_t*)"show the supported commands by boot loader\r\n");
					Bootloader_Get_Help(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_GET_CID_CMD:
					BL_Print_Message((uint8_t*)"read the device ID\r\n");
					Bootloader_Get_Chip_ID(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_JumpTO_User_APP_CMD:
					BL_Print_Message((uint8_t*)"Execute the user application\r\n");
					Bootloader_JumpTo_APP(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_GET_RDP_STATUS_CMD:
					BL_Print_Message((uint8_t*)"get protection level \r\n");
					Bootloader_Read_Protection_Level(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_GO_TO_ADDR_CMD:
					BL_Print_Message((uint8_t*)"jump to specified address considering the add is function\r\n");
					Bootloader_JumpTo_ADD(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_FLASH_ERASE_CMD:
					BL_Print_Message((uint8_t*)"Erase specified number of pages from FLASH\r\n");
					Bootloader_Flash_Erase(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_MEM_WRITE_CMD:
					BL_Print_Message((uint8_t*)"write data to specified address \r\n");/*which may be code*/
					Bootloader_Memory_Write(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_ED_W_PROTECT_CMD:
					BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
					//Bootloader_Get_Version(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_MEM_READ_CMD:
					BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
					//Bootloader_Get_Version(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_READ_SECTOR_STATUS_CMD:
					BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
					//Bootloader_Get_Version(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_OTP_READ_CMD:
					BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
					//Bootloader_Get_Version(Host_Buffer);
					status = BL_ACK;
					break;
				case CBL_CHANGE_ROP_Level_CMD:
					BL_Print_Message((uint8_t*)"Change Protection Level\r\n");
					Bootloader_Change_Protection_Level(Host_Buffer);
					status = BL_ACK;
					break;
			}
		}
		else
		{
			HAL_Status = HAL_ERROR ;
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
#endif
		}
	}
	else
	{
		HAL_Status = HAL_ERROR ;
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"HAL_ERROR {usart}\r\n");
#endif
	}


	return (status) ;
}


static BL_CRC_status Bootloader_CRC_Verify(uint8_t *pData, uint8_t Data_Length, uint32_t Host_CRC)
{
	BL_CRC_status status = CRC_NOK ;
	uint32_t BL_Calculated = 0 ;
	uint8_t counter = 0 ;
	uint32_t CRC_Data = 0 ;

	for(counter = 0;counter < Data_Length ; counter++)
	{
		CRC_Data = (uint32_t)pData[counter];
		BL_Calculated = HAL_CRC_Accumulate(CRC_handler,(uint32_t*)CRC_Data, 1);
	}

	if(BL_Calculated == Host_CRC)
	{
		status = CRC_OK ;
	}
	else
	{
		status = CRC_NOK ;
	}
	return (status);
}

static void Bootloader_Send_ACK(uint8_t Replay_Len){
	uint8_t Ack_Value[2] = {0};
	Ack_Value[0] = CBL_SEND_ACK;
	Ack_Value[1] = Replay_Len;
	HAL_UART_Transmit(BL_Host_Cummunication_Usart, Ack_Value,ACK_Length, Uart_MAX_DELAY);
}

static void Bootloader_Send_NACK(void){
	uint8_t NACK_Value = CBL_SEND_NACK;
	HAL_UART_Transmit(BL_Host_Cummunication_Usart, &NACK_Value,NACK_Length, Uart_MAX_DELAY);
}

static void Bootloader_Send_Data_To_Host(uint8_t *BL_Buffer, uint8_t Data_Len){
	HAL_UART_Transmit(BL_Host_Cummunication_Usart, BL_Buffer, (uint16_t)Data_Len,
					  HAL_MAX_DELAY);
}

static BL_ADD_Verification Bootloader_ADD_Verification(uint32_t Address)
{
	BL_ADD_Verification status = ADD_Not_Available;

	if(Address >= SRAM_BASE && Address <= SRAM_ADD_END)
	{
		status = ADD_Available;
	}
	else if(Address >= FLASH_BASE && Address <= FLASH_ADD_END)
	{
		status = ADD_Available;
	}
	else
	{
		status = ADD_Not_Available;
	}

	return (status);
}

static BL_FLASH_ERASE Perform_Flash_Erase(uint8_t Page_Number ,uint8_t Number_OF_Pages)
{
	BL_FLASH_ERASE status = FLASH_ERASE_NOK ;
	HAL_StatusTypeDef HAL_Status = HAL_ERROR ;
	uint32_t PageError = 0 ;

	if(Page_Number <= Number_OF_Pages_MAX && Number_OF_Pages <= (Number_OF_Pages_MAX -Page_Number))
	{

		FLASH_EraseInitTypeDef pEraseInit = {0};
		pEraseInit.Banks = FLASH_BANK_1 ;
		pEraseInit.NbPages = Number_OF_Pages ;
		pEraseInit.TypeErase = FLASH_TYPEERASE_PAGES ;
		pEraseInit.PageAddress = (uint32_t)(Flash_Page_Base(Page_Number)) ;

		HAL_Status |= HAL_FLASH_Unlock();
		HAL_Status |= HAL_FLASHEx_Erase(&pEraseInit, &PageError);
		HAL_Status |= HAL_FLASH_Lock();
		if(PageError == Successful_Erase && HAL_Status == HAL_OK )
		{
			status = FLASH_ERASE_OK ;
		}
		else
		{
			status = FLASH_ERASE_NOK ;
		}
	}
	else
	{
		status = FLASH_ERASE_NOK ;
	}




	return (status);
}

static BL_Memory_Write Perform_Memory_Write(uint32_t Destination_ADD ,uint32_t* APP_Data ,uint8_t Payload_len)
{
	BL_Memory_Write status = Memory_Write_NOK ;
	HAL_StatusTypeDef HAL_Status = HAL_ERROR ;
	BL_ADD_Verification	ADD_Verification = ADD_Not_Available ;
	uint8_t counter = 0 ;

	ADD_Verification = Bootloader_ADD_Verification(Destination_ADD);

	if(ADD_Verification == ADD_Available)
	{
		HAL_Status = HAL_FLASH_Unlock();
			if(HAL_Status == HAL_OK)
			{
				for(counter = 0;counter <= Payload_len;counter++)
				{
					HAL_Status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, Destination_ADD + counter, APP_Data[counter]);
				}
				if(HAL_Status == HAL_OK)
				{
					HAL_FLASH_Lock();
					status = Memory_Write_OK ;
				}
				else
				{
					status = Memory_Write_NOK ;
				}
			}
			else
			{
				status = Memory_Write_NOK ;
			}

	}
	else
	{
		status = Memory_Write_NOK ;
	}

	return (status);
}

static BL_RDP_status Get_RDP_Level(uint8_t* RDP_Level)
{
	BL_RDP_status status = RDP_NOK;
	FLASH_OBProgramInitTypeDef pOBInit ;

	HAL_FLASHEx_OBGetConfig(&pOBInit) ;

	*RDP_Level = pOBInit.RDPLevel;
	return (status);
}

static BL_RDP_status Change_ROP_Level(uint8_t RDP_Level)
{
	BL_RDP_status status = RDP_NOK;
	HAL_StatusTypeDef HAL_Status = HAL_ERROR ;
	if(RDP_Level == RDP_LEVEL_0 || RDP_Level == RDP_LEVEL_1)
	{
		FLASH_OBProgramInitTypeDef pOBInit ;
		HAL_Status = HAL_FLASH_OB_Unlock();
		if(HAL_Status == HAL_OK)
		{
			pOBInit.OptionType = OPTIONBYTE_RDP ;
			pOBInit.RDPLevel = RDP_Level ;
			pOBInit.Banks = FLASH_BANK_1 ;

			HAL_FLASHEx_OBGetConfig(&pOBInit) ;

			HAL_FLASH_OB_Launch();

			HAL_Status = HAL_FLASH_OB_Lock();
			if(HAL_Status == HAL_OK)
			{
				status = RDP_OK;
			}
			else
			{
				status = RDP_NOK;
			}
		}
		else
		{
			status = RDP_NOK;
		}
	}
	else
	{
		status = RDP_NOK;
	}


	return (status);
}

static BL_status Bootloader_Get_Version(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(4);
			Bootloader_Send_Data_To_Host(BL_VERSION, 4);
			status = BL_ACK ;
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_Get_Help(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"Read the commands supported by the bootloader \r\n");
#endif
	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(NUM_BL_CMD);
			Bootloader_Send_Data_To_Host(BL_CMD, NUM_BL_CMD);
			status = BL_ACK ;
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_Get_Chip_ID(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;
	uint16_t MCU_ID = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			MCU_ID = (uint16_t)((DBGMCU->IDCODE) & 0x0FFF);
			Bootloader_Send_ACK(2);
			Bootloader_Send_Data_To_Host((uint8_t*)&MCU_ID, 2);
			status = BL_ACK ;
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_JumpTo_APP(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;

	uint32_t MSP_APP = *((volatile uint32_t*)(FLASH_APP_Address));
	uint32_t Reset_Handler_Address = *((volatile uint32_t*)(FLASH_APP_Address + 4));

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			/*send acknowledge to Host*/
			Bootloader_Send_ACK(0);
			/* Set Main Stack Pointer */
			__set_MSP(MSP_APP);
			/* Fetch the reset handler address of the user application */
			Ptr_Function Reset_Handler_Fun = (Ptr_Function)Reset_Handler_Address ;
			/* DeInitialize */

			/* DeInitialize the RCC clock configuration to the default reset state. */
				HAL_RCC_DeInit();

			/* Jump to Application Reset Handler */
			Reset_Handler_Fun();


			status = BL_ACK ;
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_JumpTo_ADD(uint8_t* Host_Packet)
{
	BL_ADD_Verification ADD_status = ADD_Not_Available ;
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;
	uint32_t Host_ADD = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			/*send acknowledge to Host*/
			Bootloader_Send_ACK(1);
			/*extract the address from host packet*/
			Host_ADD = *((uint32_t*)&Host_Packet[2]);
			/*verify the address*/
			ADD_status = Bootloader_ADD_Verification(Host_ADD);

			if(ADD_status == ADD_Available)
			{
				//Bootloader_Send_Data_To_Host(, );
				Bootloader_Send_Data_To_Host((uint8_t*)ADD_status, 1);

				Ptr_Function JumpTO_Fun = (Ptr_Function)Host_ADD; // AHMED
				JumpTO_Fun();
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"Jump to : 0x%X \r\n", Host_ADD);
#endif
				status = BL_ACK ;
			}
			else
			{
				status = BL_NACK ;
			}

	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_Flash_Erase(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	BL_FLASH_ERASE FLASH_status = FLASH_ERASE_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(1);

			FLASH_status = Perform_Flash_Erase(Host_Packet[2],Host_Packet[3]);
			if(FLASH_status == FLASH_ERASE_OK)
			{
				status = BL_ACK ;
			}
			else
			{
				status = BL_NACK ;
			}
			Bootloader_Send_Data_To_Host((uint8_t*)FLASH_status, 1);
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_Memory_Write(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	BL_Memory_Write FLASH_status = FLASH_ERASE_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;
	uint32_t APP_ADD_TO_Write = 0 ;
	uint8_t Payload_length = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(1);

			APP_ADD_TO_Write = *((uint32_t*)&Host_Packet[2]);
			Payload_length = Host_Packet[6] ;

			FLASH_status = Perform_Memory_Write(APP_ADD_TO_Write, ((uint32_t*)&Host_Packet[7]), Payload_length);
			if(FLASH_status == Memory_Write_OK)
			{
				status = BL_ACK ;
			}
			else
			{
				status = BL_NACK ;
			}
			Bootloader_Send_Data_To_Host((uint8_t*)FLASH_status, 1);
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}


static BL_status Bootloader_Read_Protection_Level(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	BL_RDP_status RDP_status = RDP_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;
	uint8_t RDP_Level = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(1);
			RDP_status = Get_RDP_Level(&RDP_Level);
			if(RDP_status == RDP_OK)
			{
				status = BL_ACK ;
			}
			else
			{
				status = BL_NACK ;
			}

			Bootloader_Send_Data_To_Host((uint8_t*)&RDP_Level, 1);
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

static BL_status Bootloader_Change_Protection_Level(uint8_t* Host_Packet)
{
	BL_status status = BL_NACK ;
	BL_CRC_status CRC_status = CRC_NOK ;
	BL_RDP_status RDP_status = RDP_NOK ;
	uint8_t Host_packet_length = 0 ;
	uint32_t Host_crc = 0 ;

	Host_packet_length = Host_Packet[0] + 1 ;
	Host_crc = *((uint32_t*)(Host_Packet + Host_packet_length - CRC_Size_Byte));
	CRC_status = Bootloader_CRC_Verify(Host_Packet,Host_packet_length - CRC_Size_Byte,Host_crc);
	/*CRC Verification*/
	if(CRC_status == CRC_OK)
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Passed\r\n");
#endif
			Bootloader_Send_ACK(1);

			RDP_status = Change_ROP_Level(Host_Packet[2]);

			if(RDP_status == RDP_OK)
			{
				status = BL_ACK ;
			}
			else
			{
				status = BL_NACK ;
			}

			Bootloader_Send_Data_To_Host((uint8_t*)RDP_status, 1);
	}
	else
	{
#if (CODE_DEBUG == BL_DEBUG)
			BL_Print_Message((uint8_t*)"CRC Verification Failed\r\n");
#endif
			Bootloader_Send_NACK();
			status = BL_NACK ;
	}
	return (status);
}

