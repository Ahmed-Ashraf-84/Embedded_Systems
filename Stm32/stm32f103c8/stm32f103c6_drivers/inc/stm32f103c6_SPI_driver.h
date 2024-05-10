/*
 * stm32f103c6_SPI_driver.h
 *
 *  Created on: Oct 4, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_LQFP48.h"
#include "stm32f103c6_GPIO_driver.h"
#include "stm32f103c6_RCC_driver.h"



//-----------------------------
//Macros Configuration References
//-----------------------------

// @ref Device_Mode_Definition
enum Device_Mode
{
	 Master = 0b1 ,
	 Slave  = 0b0
};

//@ref Data_size_Definition
enum Data_size
{
	 Data_bit_16 = 0b1 ,
	 Data_bit_8  = 0b0
};

//@ref LSB_MSB_Definition
enum LSB_MSB
{
	 LSB = 0b1 ,
	 MSB = 0b0
};

//@ref CLK_polarity_phase_Definition
enum CLK_polarity_phase
{
	 First_Edge_LOW_idle     = 0b00  ,
	 First_Edge_HIGH_idle    = 0b10  ,
	 Second_Edge_LOW_idle    = 0b01  ,
	 Second_Edge_HIGH_idle   = 0b11
};

//@ref NSS_HW_SW_Definition
enum NSS_HW_SW
{
	 SW     			  = 0b101  , //ssm -> ssoe -> ssi
	 HW_output_enabled    = 0b010  ,
	 HW_output_disabled   = 0b000
};


//@ref Communication_Mode_Definition
enum Communication_Mode
{
	 FULL_Duplex    	= 0b000  ,// BIDIMODE ->  BIDIOE ->  RXONLY
	 Half_Duplex_TX		= 0b110  , //master
	 Half_Duplex_RX		= 0b100  ,
	 Simplex_TX_ONLY   	= 0b000  , //the receive pins free -- ignore the  Rx buffer
	 Simplex_RX_ONLY   	= 0b001    //the transmit pins free -- ignore the Tx buffer
};

//@ref CLK_Frequency_Definition
enum CLK_Frequency
{
	 Baud_rate_prescaler_2    	= 0b000  ,
	 Baud_rate_prescaler_4		= 0b001  ,
	 Baud_rate_prescaler_8   	= 0b010  ,
	 Baud_rate_prescaler_16		= 0b011  ,
	 Baud_rate_prescaler_32		= 0b100  ,
	 Baud_rate_prescaler_64		= 0b101  ,
	 Baud_rate_prescaler_128	= 0b110  ,   //<<3
	 Baud_rate_prescaler_256	= 0b111

};

//@ref Interrupt_Enable_Definition

//TXEIE: Tx buffer empty interrupt enable
//RXNEIE: RX buffer not empty interrupt enable
//ERRIE: Error interrupt enable


enum Interrupt_Enable
{
	 ERRIE_ENABLED 				= 0b001  ,
	 TXEIE_ENABLED 				= 0b100  ,
	 RXNEIE_ENABLED 			= 0b010  ,  //if condition
	 interrupt_DISABLED			= 0b000		//shift left -> 5
};

//@ref polling_mechanism_Definition
enum polling_mechanism
{
	polling_ENABLED 	= 0b1 ,
	polling_DISABLED 	= 0b0

};

//@ref Num_Slave_Definition
enum Num_Slave
{
	point_to_point 	= 0b1 ,
	multi_slave 	= 0b0

};


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	SPI_t *SPIx;				//this member can be a value of @ref SPI
	enum Device_Mode Device_Mode :1;	//this member can be a value of @ref Device_Mode_Definition
	enum Data_size Data_size   :1;	//this member can be a value of @ref Data_size_Definition
	enum LSB_MSB LSB_MSB     :1;	//this member can be a value of @ref LSB_MSB_Definition
	enum CLK_polarity_phase CLK_polarity_phase :2;	//this member can be a value of @ref CLK_polarity_phase_Definition
	enum NSS_HW_SW NSS_HW_SW :3;	//this member can be a value of @ref NSS_HW_SW_Definition
	enum Communication_Mode Communication_Mode :3;	//this member can be a value of @ref Communication_Mode_Definition
	enum CLK_Frequency CLK_Frequency :3;	//this member can be a value of @ref CLK_Frequency_Definition
	enum Interrupt_Enable Interrupt_Enable :3;	//this member can be a value of @ref Interrupt_Enable_Definition
	enum polling_mechanism polling :1;				  //this member can be a value of @ref polling_mechanism_Definition
	enum Num_Slave Slave :1;				  //this member can be a value of @ref Num_Slave_Definition

	uint16_t *Buffer ;
	void (*Ptr_IRQ)(void);



}SPI_config_t;






/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void SPI_init(SPI_config_t * SPI);
void SPI_RST(SPI_config_t * SPI);
void SPI_Send_data(SPI_config_t * SPI);
void SPI_Receive_data(SPI_config_t * SPI);
void SPI_TX_RX(SPI_config_t * SPI);
void SPI_AFIO_Set_Pins(SPI_config_t * SPI);


#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
