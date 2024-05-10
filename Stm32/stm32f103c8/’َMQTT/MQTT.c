 /**
 ******************************************************************************
 * @file           : MQTT.c
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code of MQTT protocol
 ******************************************************************************
**/

/*--------------------------------------------Includes Start----------------------------------*/
#include "MQTT.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/
/*
#define Password_condition		(*Password != 0) ? (10 + strlen(clientID) + 10 +strlen(will_Topic)+strlen(will_Message)+strlen(User_Name)+strlen(Password))\
								: (10 + strlen(clientID) + 8 +strlen(will_Topic)+strlen(will_Message)+strlen(User_Name))
#define User_Name_condition		(*User_Name != 0) ? (Password_condition) \
								: (10 + strlen(clientID) + 6 +strlen(will_Topic)+strlen(will_Message))
#define will_Message_condition  (*will_Message != 0) ? (User_Name_condition)\
								: (10 + strlen(clientID) + 4 +strlen(will_Topic))
*/
#define Flags_mask				0xFE

/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

static uint8_t packet[200];
static uint8_t packet_index;
static uint8_t protcol_name[] = "MQTT" ;
static uint8_t protcol_version = 0x04 ;
/*--------------------------------------------Data Type Declaration----------------------------------*/

/*--------------------------------------------Functions----------------------------------*/


return_status MQTT_Connect_packet(uint8_t* clientID ,uint8_t Flags ,uint16_t Keep_Alive_Time
									,uint8_t* will_Topic , uint8_t* will_Message
									,uint8_t* User_Name , uint8_t* Password)
{
	return_status status = Error;
	packet_index = 0;
	uint8_t rem_length = (10 + strlen(clientID) + 2) ;



	rem_length += (*will_Topic == '0') ? (0) : (strlen(will_Topic) + 2) ;
	rem_length += (*will_Message == '0') ? (0) : ( strlen(will_Message) + 2) ;
	rem_length += (*User_Name == '0') ? (0) : ( strlen(User_Name) + 2) ;
	rem_length += (*Password == '0') ? (0) : ( strlen(Password) + 2) ;

	packet[packet_index++] = 0x10 ;
	packet[packet_index++] = rem_length  ;

	packet[packet_index++] = 0x00 ;
	packet[packet_index++] = strlen(protcol_name) ;
	strcpy(packet+packet_index , protcol_name);
	packet_index += strlen(protcol_name) ;

	packet[packet_index++] = protcol_version ;
	packet[packet_index++] = (uint8_t)(Flags & Flags_mask ) ;
	packet[packet_index++] = (Keep_Alive_Time >> 8) ;
	packet[packet_index++] = (Keep_Alive_Time & 0xFF) ;

	packet[packet_index++] = 0x00 ;
	packet[packet_index++] = strlen(clientID) ;
	strcpy(packet+packet_index , clientID);
	packet_index += strlen(clientID) ;

	if(*will_Topic != 0 )
	{
		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(will_Topic) ;
		strcpy(packet+packet_index , will_Topic);
		packet_index += strlen(will_Topic) ;
	}

	if(*will_Message != 0 )
	{
		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(will_Message) ;
		strcpy(packet+packet_index , will_Message);
		packet_index += strlen(will_Message) ;
	}

	if(*User_Name != 0 )
	{
		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(User_Name) ;
		strcpy(packet+packet_index , User_Name);
		packet_index += strlen(User_Name) ;
	}

	if(*Password != 0 )
	{
		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(Password) ;
		strcpy(packet+packet_index , Password);
		packet_index += strlen(Password) ;
	}



	//send packet
	HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);

	return status ;
}


void MQTT_Publish_packet(uint8_t* message ,uint8_t Flags ,uint16_t PacketID
								 ,uint8_t* Topic_Name )
{
	uint8_t rem_length = (*message == 0) ? ( 4 + strlen(Topic_Name) )
										  :( 4 + strlen(Topic_Name) + strlen(message) ) ;
	packet_index = 0;
	packet[packet_index++] = (uint8_t)(0x30 & (Flags & 0x0B)) ;
	packet[packet_index++] = rem_length ;

	packet[packet_index++] = 0x00 ;
	packet[packet_index++] = strlen(Topic_Name) ;
	strcpy(packet+packet_index ,Topic_Name);
	packet_index += strlen(Topic_Name) ;

	packet[packet_index++] = (PacketID >> 8) ;
	packet[packet_index++] = (PacketID & 0x00FF) ;

	strcpy(packet+packet_index ,message);
	packet_index += strlen(message) ;

	//send packet
	HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);

}


/*void MQTT_Subscribe_packet(uint16_t PacketID ,uint8_t num_of_Topics,...)
{
	//uint8_t buffer[100]={0};
	uint8_t* buffer_ptr = NULL;
	uint8_t counter = 0;
	uint8_t sum = 0;
	uint8_t rem_length = 0 ;
	va_list list ;
	va_start(list,num_of_Topics);

	for(counter=1;counter<=num_of_Topics;counter++)
	{
		packet_index = 4 ;
		buffer_ptr = va_arg(list,uint8_t*);//ahmed 1 mariam 2
		packet[(sum+(counter-1)+2*(counter-1))+packet_index] = 0x00;
		packet[(sum+(counter-1)+2*(counter-1))+1+packet_index] = strlen(buffer_ptr);
		strcpy(packet+(sum+(counter-1)+2*counter)+packet_index,buffer_ptr);
		sum += strlen(buffer_ptr);//11
		packet[(sum+(counter-1)+2*counter)+packet_index] = va_arg(list,uint8_t);
	}

	rem_length = (2+num_of_Topics*3+sum) ;
	packet_index = 0 ;
	packet[packet_index++] = 0x82 ;
	packet[packet_index++] = rem_length ;

	packet[packet_index++] = (PacketID >> 8) ;
	packet[packet_index++] = (PacketID & 0x00FF) ;

	packet_index = 2 + rem_length ;

	HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);
}
*/
void MQTT_Subscribe_packet(uint16_t PacketID ,uint8_t* Topic_Name ,uint8_t Quality_OS)
{
	uint8_t rem_length = ( 5 + strlen(Topic_Name) ) ;
		packet_index = 0 ;
		packet[packet_index++] = 0x82 ;
		packet[packet_index++] = rem_length ;

		packet[packet_index++] = (PacketID >> 8) ;
		packet[packet_index++] = (PacketID & 0x00FF) ;

		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(Topic_Name) ;
		strcpy(packet+packet_index ,Topic_Name);
		packet_index += strlen(Topic_Name) ;

		packet[packet_index++] = Quality_OS ;

		HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);
}

void MQTT_UnSubscribe_packet(uint16_t PacketID ,uint8_t* Topic_Name )
{
	uint8_t rem_length = ( 4 + strlen(Topic_Name) ) ;
		packet_index = 0 ;
		packet[packet_index++] = 0xA2 ;
		packet[packet_index++] = rem_length ;

		packet[packet_index++] = (PacketID >> 8) ;
		packet[packet_index++] = (PacketID & 0x00FF) ;

		packet[packet_index++] = 0x00 ;
		packet[packet_index++] = strlen(Topic_Name) ;
		strcpy(packet+packet_index ,Topic_Name);
		packet_index += strlen(Topic_Name) ;


		HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);
}

void MQTT_DisConnect_packet(void)
{
	packet_index=0;
	packet[packet_index++] = 0xE0 ;
	packet[packet_index++] = 0x00 ;

	HAL_UART_Transmit(&huart1,packet, packet_index, packet_index*2);
}

/*--------------------------------------------Functions----------------------------------*/



