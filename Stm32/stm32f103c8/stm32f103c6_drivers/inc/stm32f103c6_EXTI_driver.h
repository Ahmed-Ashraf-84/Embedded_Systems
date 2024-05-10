/*
 * stm32f103c6_EXTI_driver.h
 *
 *  Created on: Sep 9, 2023
 *      Author: Ahmed Ashraf
 */

#ifndef INC_STM32F103C6_EXTI_DRIVER_H_
#define INC_STM32F103C6_EXTI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------

#include "stm32f103c6_LQFP48.h"
#include "stm32f103c6_GPIO_driver.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct{

	//GPIO_PIN_config_t *PIN_config;

	volatile uint8_t LINE_Number ;

	volatile uint16_t GPIO_PIN_Number ;//specify which pin to configure
									   //this member can be a value of @ref GPIO_PIN_Definition

	GPIO_t *GPIO_PORT;        //specify the pin options (input,output,...)
									   //this member can be a value of @ref GPIO_MODE_Definition

}EXTI_GPIO_config_t;


typedef struct{

	EXTI_GPIO_config_t PORT_PIN ;	//specify which port and pin to configure
									//this member can be a value of @ref PORT_PIN_Definition

	volatile uint8_t PIN_Trigger ;		//specify trigger type
									   //this member can be a value of @ref EXTI_Trigger_Definition

	volatile void(*FUN_POINTER)(void);  //specify the function which will be executed after interrupt
									   //this member can be a value of @ref GPIO_MODE_Definition**********

}EXTI_config_t;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref PORT_PIN_Definition
//port A
#define EXTIA_PIN0			(EXTI_GPIO_config_t){0, PIN0 , GPIOA}
#define EXTIA_PIN1			(EXTI_GPIO_config_t){1, PIN1 , GPIOA}
#define EXTIA_PIN2			(EXTI_GPIO_config_t){2, PIN2 , GPIOA}
#define EXTIA_PIN3			(EXTI_GPIO_config_t){3, PIN3 , GPIOA}
#define EXTIA_PIN4			(EXTI_GPIO_config_t){4, PIN4 , GPIOA}
#define EXTIA_PIN5			(EXTI_GPIO_config_t){5, PIN5 , GPIOA}
#define EXTIA_PIN6			(EXTI_GPIO_config_t){6, PIN6 , GPIOA}
#define EXTIA_PIN7			(EXTI_GPIO_config_t){7, PIN7 , GPIOA}
#define EXTIA_PIN8			(EXTI_GPIO_config_t){8, PIN8 , GPIOA}
#define EXTIA_PIN9			(EXTI_GPIO_config_t){9, PIN9 , GPIOA}
#define EXTIA_PIN10			(EXTI_GPIO_config_t){10, PIN10 , GPIOA}
#define EXTIA_PIN11			(EXTI_GPIO_config_t){11, PIN11 , GPIOA}
#define EXTIA_PIN12			(EXTI_GPIO_config_t){12, PIN12 , GPIOA}
#define EXTIA_PIN13			(EXTI_GPIO_config_t){13, PIN13 , GPIOA}
#define EXTIA_PIN14			(EXTI_GPIO_config_t){14, PIN14 , GPIOA}
#define EXTIA_PIN15			(EXTI_GPIO_config_t){15, PIN15 , GPIOA}
//port B
#define EXTIB_PIN0			(EXTI_GPIO_config_t){0, PIN0 , GPIOB}
#define EXTIB_PIN1			(EXTI_GPIO_config_t){1, PIN1 , GPIOB}
#define EXTIB_PIN2			(EXTI_GPIO_config_t){2, PIN2 , GPIOB}
#define EXTIB_PIN3			(EXTI_GPIO_config_t){3, PIN3 , GPIOB}
#define EXTIB_PIN4			(EXTI_GPIO_config_t){4, PIN4 , GPIOB}
#define EXTIB_PIN5			(EXTI_GPIO_config_t){5, PIN5 , GPIOB}
#define EXTIB_PIN6			(EXTI_GPIO_config_t){6, PIN6 , GPIOB}
#define EXTIB_PIN7			(EXTI_GPIO_config_t){7, PIN7 , GPIOB}
#define EXTIB_PIN8			(EXTI_GPIO_config_t){8, PIN8 , GPIOB}
#define EXTIB_PIN9			(EXTI_GPIO_config_t){9, PIN9 , GPIOB}
#define EXTIB_PIN10			(EXTI_GPIO_config_t){10, PIN10 , GPIOB}
#define EXTIB_PIN11			(EXTI_GPIO_config_t){11, PIN11 , GPIOB}
#define EXTIB_PIN12			(EXTI_GPIO_config_t){12, PIN12 , GPIOB}
#define EXTIB_PIN13			(EXTI_GPIO_config_t){13, PIN13 , GPIOB}
#define EXTIB_PIN14			(EXTI_GPIO_config_t){14, PIN14 , GPIOB}
#define EXTIB_PIN15			(EXTI_GPIO_config_t){15, PIN15 , GPIOB}

//@ref EXTI_Trigger_Definition

#define Rising_Trigger						0
#define Falling_Trigger						1
#define Rising_Falling_Trigger				2

//@ref EXTI_interrupt_Definition

#define interrupt_ENABLE					1
#define interrupt_DISABLE					0


/*
* ===============================================
* APIs Supported by "MCAL GPIO DRIVER"
* ===============================================
*/

void EXTI_RST(void);

void EXTI_init(EXTI_config_t *EXTIx);

void EXTI_update(EXTI_config_t *EXTIx,uint8_t interrupt);

void SW_interrupt(EXTI_config_t *EXTIx,uint8_t interrupt);




#endif /* INC_STM32F103C6_EXTI_DRIVER_H_ */
