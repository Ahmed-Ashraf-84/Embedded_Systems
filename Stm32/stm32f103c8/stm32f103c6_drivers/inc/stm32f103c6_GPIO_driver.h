/*
 * stm32f103c6_GPIO_driver.h
 *
 *  Created on: Sep 8, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_GPIO_DRIVER_H_
#define INC_STM32F103C6_GPIO_DRIVER_H_



//-----------------------------
//Includes
//-----------------------------

#include "stm32f103c6_LQFP48.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct{

	volatile uint16_t GPIO_PIN_Number ;//specify which pin to configure
									   //this member can be a value of @ref GPIO_PIN_Definition

	volatile uint8_t GPIO_MODE;        //specify the pin options (input,output,...)
									   //this member can be a value of @ref GPIO_MODE_Definition

	volatile uint8_t GPIO_OUTPUT_SPEED;//specify the output speed
	   	   	   	   	   	   	   	   	   //this member can be a value of @ref GPIO_OUTPUT_SPEED_Definition

}GPIO_PIN_config_t;



//-----------------------------
//Macros Configuration References
//-----------------------------
// @ref GPIO_PIN_Definition

#define PIN0				((uint16_t)0x0001) //pin 0 selected 0
#define PIN1				((uint16_t)0x0002) //pin 1 selected 4
#define PIN2				((uint16_t)0x0004) //pin 2 selected 8
#define PIN3				((uint16_t)0x0008) //pin 3 selected 12
#define PIN4				((uint16_t)0x0010) //pin 4 selected 16
#define PIN5				((uint16_t)0x0020) //pin 5 selected
#define PIN6				((uint16_t)0x0040) //pin 6 selected
#define PIN7				((uint16_t)0x0080) //pin 7 selected
#define PIN8				((uint16_t)0x0100) //pin 8 selected
#define PIN9				((uint16_t)0x0200) //pin 9 selected
#define PIN10				((uint16_t)0x0400) //pin 10 selected
#define PIN11				((uint16_t)0x0800) //pin 11 selected
#define PIN12				((uint16_t)0x1000) //pin 12 selected
#define PIN13				((uint16_t)0x2000) //pin 13 selected
#define PIN14				((uint16_t)0x4000) //pin 14 selected
#define PIN15				((uint16_t)0x8000) //pin 15 selected

#define PIN_ALL				((uint16_t)0xFFFF) //ALL pins selected

//#define PIN1	mask			((uint16_t)0x0001) //pin 0 selected


//@ref GPIO_MODE_Definition

#define MODE_ANALOG							0x0u  //Analog mode
#define MODE_INPUT_FLO						0x1u  //Floating input
#define MODE_INPUT_PU						0x2u  //Input with pull-up
#define MODE_INPUT_PD						0x3u  //Input with pull-down
#define MODE_OUTPUT_PP						0x4u  //General purpose output push-pull
#define MODE_OUTPUT_OD						0x5u  //General purpose output Open-drain
#define MODE_OUTPUT_AF_PP					0x6u  //Alternate function output Push-pull
#define MODE_OUTPUT_AF_OD					0x7u  //Alternate function output Open-drain
#define MODE_INPUT_AF						0x8u  //Alternate function input

//@ref GPIO_OUTPUT_SPEED_Definition

#define OUTPUT_SPEED_10						0x1u //Output mode, max speed 10 MHz
#define OUTPUT_SPEED_2						0x2u //Output mode, max speed 2 MHz
#define OUTPUT_SPEED_50						0x3u //Output mode, max speed 50 MHz


//@ref GPIO_status_Definition

#define GPIO_status_SET						1
#define GPIO_status_RESET					0

//@ref GPIO_LOCK_Definition

#define GPIO_LOCK_ENABLE						1
#define GPIO_LOCK_ERORR							0

/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void GPIO_init(GPIO_t *GPIOx , GPIO_PIN_config_t *pinconfig);

void GPIO_RST(GPIO_t *GPIOx);

uint8_t GPIO_Read_Pin(GPIO_t *GPIOx , uint16_t pin_number);

uint16_t GPIO_Read_Port(GPIO_t *GPIOx);

void GPIO_Write_Pin(GPIO_t *GPIOx , uint16_t pin_number , uint8_t value);

void GPIO_Write_Port(GPIO_t *GPIOx , uint16_t value);

void GPIO_Toggle_Pin(GPIO_t *GPIOx , uint16_t pin_number);

uint8_t GPIO_Lock_Pin(GPIO_t *GPIOx , uint16_t pin_number);

#endif /* INC_STM32F103C6_GPIO_DRIVER_H_ */
