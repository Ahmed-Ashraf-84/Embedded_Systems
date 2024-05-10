/*
 * stm32f103c6_I2C_driver.h
 *
 *  Created on: Oct 10, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_I2C_DRIVER_H_
#define INC_STM32F103C6_I2C_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------

#include "stm32f103c6_LQFP48.h"
#include "stm32f103c6_GPIO_driver.h"
#include "stm32f103c6_RCC_driver.h"


//-----------------------------
//Macros Configuration References
//-----------------------------

#define CCR_calc(SCLK_FREQ)					((RCC_GET_PCLK1_CLK())/(2000*SCLK_FREQ));

//#define CCR_calc(SCLK_FREQ)					((1/(SCLK_FREQ*1000))/(1/RCC_GET_PCLK1_CLK()));
//#define T_rise_calc()						(1000/(1/RCC_GET_PCLK1_CLK()));



//@ref stretch_mode_Definition
enum stretch_mode
{
	stretch_ENABLED 	= 0b1 ,
	stretch_DISABLED 	= 0b0

};

//@ref Peripheral_mode_Definition
enum Peripheral_mode
{
	SMBus_mode 	= 0b1 ,
	I2C_mode 	= 0b0

};

//@ref ADD_MODE_Definition
enum Add_mode
{
	slave_address_10 	= 0b1 ,
	slave_address_7  	= 0b0

};


//@ref Dual_addressing_mode_Definition
enum Dual_addressing_mode
{
	Dual_addressing_ENABLED 	= 0b1 , //Both OAR1 and OAR2 are recognized in 7-bit addressing mode
	Dual_addressing_DISABLED   	= 0b0

};


//@ref ACK_Definition
enum ACK_HW
{
	ACK_ENABLED 	= 0b1 ,
	ACK_DISABLED 	= 0b0

};

//@ref General_call_enable_Definition
enum General_call
{
	General_call_ENABLED 	= 0b1 ,
	General_call_DISABLED 	= 0b0

};

//@ref I2C_mode_Definition
enum I2C_mode
{
	Master 	= 0b1 ,
	Slave 	= 0b0

};

//@ref I2C_mode_Definition
enum I2C_SM_FM
{
	FM 	= 0b1 ,
	SM 	= 0b0

};

enum interrupt_ENABLED
{
	IRQ_ENABLED 	= 0b1 ,
	IRQ_DISABLED   	= 0b0

};

enum EN_Peripheral
{
	ENABLED 	= 0b1 ,
	DISABLED 	= 0b0

};
enum bit
{
	SET_bit 	= 0b1 ,
	RESET_bit 	= 0b0

};

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	enum Add_mode add_mode :1 ;
	enum Dual_addressing_mode dual_mode :1 ;
	uint8_t Primary_Slave_ADD :7 ;
	uint16_t Secondary_Slave_ADD :10;

}Slave_address;

typedef struct
{
	I2C_t * I2Cx ;
	enum I2C_SM_FM  I2C_SM_FM :1;
	uint8_t SCLK_FREQ ;  // up to 100 KHZ in SM mode and 400 KHZ in FM mode   in KHZ
	enum stretch_mode stretch_mode :1;
	enum Peripheral_mode Peripheral_mode  :1;
	enum I2C_mode I2C_mode:1;
	Slave_address Slave_config ;
	enum ACK_HW ACK_enable :1;
	enum General_call General_call_ADD :1;

	void(* ptr_slave_callback)();

}I2C_config_t;


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void I2C_init(I2C_config_t * I2C);
void I2C_RST(I2C_config_t * I2C);
void I2C_AFIO_Set_Pins(I2C_config_t * I2C);
void I2C_Master_TX(I2C_config_t * I2C,uint16_t Des_Add ,uint8_t * Data ,uint8_t Data_length );
void I2C_Master_RX(I2C_config_t * I2C,uint16_t Des_Add ,uint8_t * Data ,uint8_t Data_length );


#endif /* INC_STM32F103C6_I2C_DRIVER_H_ */
