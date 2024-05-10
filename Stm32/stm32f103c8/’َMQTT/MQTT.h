 /**
 ******************************************************************************
 * @file           : MQTT.h
 * @author         : Ahmed Ashraf Mahgob Ahmed
 * @brief          : Contain the code of MQTT protocol
 ******************************************************************************
**/
#ifndef INC_MQTT_H_
#define INC_MQTT_H_

										// connect packet

/*	fixed header --> bits[0:3] :reserved -------  bits[4:7] : control packet "TYPE"  == 0x10
 * 		+ remaining length which is variable header (10 bytes) plus the length of the Payload
 *
 * 	variable header --> CONNECT Packet consists of four fields : Protocol Name, Protocol Level,
 * 																 Connect Flags, and Keep Alive
 * 						Protocol Name
 * 							b1,2 = 	   0x0004
 * 							b3,4,5,6 = "MQTT"
 * 						Protocol Level : revision level
 * 							version 3.1.1 of the protocol is 4 == (0x04) b7
 * 						Connect Flags b8
 * 							/Clean Session bit [1] and bit [0] reserved = 0
 * 								if 0 the server save the state and message even if the client disconnected
 * 								if 1 the server remove the session and no message will send to client
 * 							/Will Flag	datasheet	[2]
 * 								If the Will Flag is set to 1, the Will QoS and Will Retain fields in the Connect Flags will be used by the
 	 	 	 	 	 	 	 	 Server, and the Will Topic and Will Message fields MUST be
 	 	 	 	 	 	 	 	 present in the payload

 	 	 	 	 	 	 	 	 If the Will Flag is set to 0 the Will QoS and Will Retain fields in the Connect Flags MUST be set to zero
 	 	 	 	 	 	 	 	 and the Will Topic and Will Message fields MUST NOT be
 	 	 	 	 	 	 	 	 present in the payload .
  	  	  	  	  	  	  	  	 Will Message MUST NOT be published when this Network Connection ends
 	 	 	 	 	 	 	 /Will QoS bits [3:4] specify the QoS level to be used when publishing the Will Message
 	 	 	 	 	 	 	     If the Will Flag is set to 0, then the Will QoS MUST be set to 0 (0x00)
 	 	 	 	 	 	 	     If the Will Flag is set to 1, the value of Will QoS can be
 	 	 	 	 	 	 	      0 (0x00), 1 (0x01), or 2 (0x02). It MUST NOT be 3 (0x03)
 	 	 	 	 	 	 	 /Will Retain bit [5] specifies if the Will Message is to be Retained when it is published
 	 	 	 	 	 	 	     If the Will Flag is set to 0, then the Will Retain Flag MUST be set to 0
 	 	 	 	 	 	 	     If the Will Flag is set to 1:
 	 	If Will Retain is set to 0, the Server MUST publish the Will Message as a non-retained message

 	 	If Will Retain is set to 1, the Server MUST publish the Will Message as a retained message
							 /User Name Flag [6]
							  	 If the User Name Flag is set to 0, a user name MUST NOT be present in the payload
 * 								 If the User Name Flag is set to 1, a user name MUST be present in the payload
 * 							 / Password Flag [7]
 * 								 If the Password Flag is set to 0, a password MUST NOT be present in the payload
 * 								 If the Password Flag is set to 1, a password MUST be present in the payload
 * 								 **If the User Name Flag is set to 0, the Password Flag MUST be set to 0
 * 						 Keep Alive 	b9,10
 * 								 The actual value of the Keep Alive is application specific. The
 	 	 	 	 	 	 	 	 maximum value is 18 hours 12 minutes and 15 seconds
 	 	summary in page 28 "variable header"

 	 Payload
 	 					/Client Identifier "ClientId" :MUST be present and MUST be the first field
 	 					 	 	 	 	 	 	 	   in the CONNECT packet Payload
 	 					 	 	 	 	 	 	 	   data sheet
 	 					/Will Topic
 	 					/Will Message
 	 					/User Name
 	 					/Password

 */

//												Publish message

/*
		fixed header --> b1 == bits[4:7] Control Packet type (3) : 0x3 ----- bit[3] :DUP flag ,
		 	 	 	 	 	 	 	 	 	 	 	 	    bits[0:1] :QoS level , bit[0] :RETAIN
						 b2	== remaining length

		Variable header -->	Topic Name UTF-8 encoded string , Packet Identifier number

		Payload	-->	optional

*/


//												Subscribe message

/*
		fixed header --> b1 == bits[4:7] Control Packet type (8) : 0x8 ----- bit[3]: reversed 0x2
						 b2	== remaining length

		Variable header -->	 Packet Identifier is a number

		Payload	-->	list of Topic UTF-8 encoded topic name ,Requested QoS

*/

/*--------------------------------------------Includes Start----------------------------------*/
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
//#include <stdio.h>
/*--------------------------------------------Includes End----------------------------------*/

/*--------------------------------------------Macro Declaration----------------------------------*/



/*--------------------------------------------Macro Declaration----------------------------------*/

/*--------------------------------------------Macro Functions Declaration----------------------------------*/
/*--------------------------------------------Macro Functions Declaration----------------------------------*/

/*--------------------------------------------Data Type Declaration----------------------------------*/

typedef enum
{
	Error =0 ,
	Done

}return_status;



/*--------------------------------------------Data Type Declaration----------------------------------*/


/*--------------------------------------------Functions Declaration----------------------------------*/

return_status MQTT_Connect_packet(uint8_t* clientID ,uint8_t Flags ,uint16_t Keep_Alive_Time
									,uint8_t* will_Topic , uint8_t* will_Message
									,uint8_t* User_Name , uint8_t* Password);

void MQTT_Publish_packet(uint8_t* message ,uint8_t Flags ,uint16_t PacketID
								 ,uint8_t* Topic_Name );

void MQTT_Subscribe_packet(uint16_t PacketID ,uint8_t* Topic_Name ,uint8_t Quality_OS);

void MQTT_UnSubscribe_packet(uint16_t PacketID ,uint8_t* Topic_Name );

void MQTT_DisConnect_packet(void);


/*--------------------------------------------Functions Declaration----------------------------------*/




#endif /* INC_MQTT_H_ */
