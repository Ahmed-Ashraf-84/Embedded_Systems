/*
 * stm32f103c6_USART_driver.h
 *
 *  Created on: Sep 24, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_LQFP48.h"
#include "stm32f103c6_GPIO_driver.h"
#include "stm32f103c6_RCC_driver.h"

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref payload_length_Definition
enum payload_length_Definition
{
	 Data_bits_8 = 0b0 ,
	 Data_bits_9 = 0b1

};



//@ref Stop_bits_Definition

enum Stop_bits_Definition
{
	 Stop_bits_1 = 0b00 ,
	 Stop_bits_Half = 0b01 ,
	 Stop_bits_1_Half = 0b11 ,
	 Stop_bits_2 = 0b10

};

//@ref Parity_Definition

enum Parity_Definition
{
	 Even_Parity = 0b10 ,
	 Odd_Parity = 0b11 ,
	 Parity_DISABLED = 0b00

};

//@ref Baud_Rate_Definition

enum Baud_Rate_Definition
{
	 Baud_Rate_2400		= 2400 ,
	 Baud_Rate_9600		= 9600 ,
	 Baud_Rate_19200	= 19200 ,
	 Baud_Rate_57600	= 57600 ,
	 Baud_Rate_115200	= 115200 ,
	 Baud_Rate_230400	= 230400 ,
	 Baud_Rate_460800	= 460800 ,
	 Baud_Rate_921600	= 921600 ,
	 Baud_Rate_2250000	= 2250000 ,
	 Baud_Rate_4500000	= 4500000 ,

};


//@ref Mode_Definition

enum Mode_Definition
{
	 Mode_RX = 0b01 ,
	 Mode_TX = 0b10 ,
	 Mode_TX_RX = 0b11

};

//@ref interrupt_Definition

//TCIE: Transmission complete -interrupt enable
//PEIE: Parity- interrupt enable
//TXEIE: Transmit data register empty -interrupt enable
//RXNEIE: Received data ready to be read -interrupt enable

enum interrupt_Definition
{
	 TCIE_ENABLED 				= 0b0010  ,					//1
	 PEIE_ENABLED 				= 0b1000  ,					//4
	 TXEIE_ENABLED 				= 0b0100  ,					//2
	 RXNEIE_ENABLED 			= 0b0001  ,//if condition   //0
	 interrupt_DISABLED			= 0b0000

};


//@ref HW_Flow_ctrl_Definition

enum HW_Flow_ctrl_Definition
{
	HW_Flow_ctrl_DISABLED 	= 0b00 ,
	HW_Flow_ctrl_RTS 		= 0b01 ,
	HW_Flow_ctrl_CTS 		= 0b10 ,
	HW_Flow_ctrl_CTS_RTS	= 0b11

};
//@ref polling_mechanism_Definition
enum polling_mechanism
{
	polling_ENABLED 	= 0b1 ,
	polling_DISABLED 	= 0b0

};

//-----------------------------
//User type definitions (structures)
//-----------------------------


typedef struct
{

	USART_t  *USARTx ;		  						  //this member can be a value of @ref USART_Peripheral Instants
	void (* ptr_IRQ_call_back )(void);			  	  //void (* ptr_IRQ_call_back [4])(void);
	enum Baud_Rate_Definition Baud_rates:23 ;		  //this member can be a value of @ref Baud_Rate_Definition
	enum interrupt_Definition IRQ_ENABLE :4 ;		  //this member can be a value of @ref interrupt_Definition
	enum Mode_Definition Mode_TX_RX :2;				  //this member can be a value of @ref Mode_Definition
	enum Parity_Definition Parity_bits :2; 		      //this member can be a value of @ref Parity_Definition
	enum payload_length_Definition payload_length:1;  //this member can be a value of @ref payload_length_Definition
	enum Stop_bits_Definition Stop_bits:2;  	   	  //this member can be a value of @ref Stop_bits_Definition
	enum HW_Flow_ctrl_Definition HW_Flow_ctrl :2 ; 	  //this member can be a value of @ref HW_Flow_ctrl_Definition
	enum polling_mechanism polling :1;				  //this member can be a value of @ref polling_mechanism_Definition
	uint16_t *Buffer ;

}USART_config_t;










/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void USART_init(USART_config_t * USARTx);
void USART_deit(USART_config_t * USARTx);
void USART_AFIO_Set_Pins(USART_config_t * USARTx);
void USART_Send_data(USART_config_t * USARTx);
void USART_Receive_data(USART_config_t * USARTx);
void USART_Transmission_complete(USART_config_t * USARTx);

#endif /* INC_STM32F103C6_USART_DRIVER_H_ */
