/*
 * stm32f103c6_GPIO_driver.c
 *
 *  Created on: Sep 8, 2023
 *      Author: Ahmed Ashraf
 */
#include "stm32f103c6_GPIO_driver.h"

static uint8_t get_position (uint16_t pin_number)
{
	switch(pin_number)
	{
	case PIN0 :
		return 0;
		break;
	case PIN1 :
		return 4;
		break;
	case PIN2 :
		return 8;
		break;
	case PIN3 :
		return 12;
		break;
	case PIN4 :
		return 16;
		break;
	case PIN5 :
		return 20;
		break;
	case PIN6 :
		return 24;
		break;
	case PIN7 :
		return 28;
		break;
	case PIN8 :
		return 0;
		break;
	case PIN9 :
		return 4;
		break;
	case PIN10 :
		return 8;
		break;
	case PIN11 :
		return 12;
		break;
	case PIN12 :
		return 16;
		break;
	case PIN13 :
		return 20;
		break;
	case PIN14 :
		return 24;
		break;
	case PIN15 :
		return 28;
		break;



	}
	return 0;
}


/**================================================================
* @Fn			- GPIO_init
* @brief		- Initialize the GPIOx Piny according to the specified members in GPIO_PIN_config_t
* @param [in]   - GPIOx     : select the GPIO port (from A to E)
* @param [in]   - pinconfig : contain the configuration information of the specified pin (pass by reference)
* @retval       - none
* Note			- GPIOx 		: pointer to GPIO_register structure
* 				- pinconfig  : pointer to GPIO_PIN_config structure
*/

void GPIO_init(GPIO_t *GPIOx , GPIO_PIN_config_t *pinconfig)
{
	volatile uint32_t *register_L_H =NULL;

	register_L_H = ((pinconfig->GPIO_PIN_Number)<= PIN7) ? &(GPIOx->CRL): &(GPIOx->CRH) ;

	if( (pinconfig->GPIO_MODE)==MODE_OUTPUT_PP ||(pinconfig->GPIO_MODE)==MODE_OUTPUT_OD
	|| (pinconfig->GPIO_MODE)==MODE_OUTPUT_AF_PP ||(pinconfig->GPIO_MODE)==MODE_OUTPUT_AF_OD )
	{
		*register_L_H |= ((pinconfig->GPIO_OUTPUT_SPEED)<<get_position(pinconfig->GPIO_PIN_Number) );

		*register_L_H |= (((pinconfig->GPIO_MODE)-4)<<(get_position(pinconfig->GPIO_PIN_Number)+2) );
	}
	else
	{
		*register_L_H &= ~(0x3<<get_position(pinconfig->GPIO_PIN_Number) );

		if((pinconfig->GPIO_MODE)==MODE_INPUT_PD)
		{
			*register_L_H |= (((pinconfig->GPIO_MODE)-1)<<(get_position(pinconfig->GPIO_PIN_Number)+2) );
			GPIOx->BRR |= (pinconfig->GPIO_PIN_Number) ;
		}
		else if((pinconfig->GPIO_MODE)==MODE_INPUT_PU)
		{
			*register_L_H |= (((pinconfig->GPIO_MODE))<<(get_position(pinconfig->GPIO_PIN_Number)+2) );
			GPIOx->BSRR |= (pinconfig->GPIO_PIN_Number) ;
		}
		else
		{
			*register_L_H |= (((pinconfig->GPIO_MODE))<<(get_position(pinconfig->GPIO_PIN_Number)+2) );
		}

	}


}

/**================================================================
* @Fn			- GPIO_RST
* @brief		- Rest the GPIOx
* @param [in]   - GPIOx     : select the GPIO port (from A to E)
* @retval       - none
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

void GPIO_RST(GPIO_t *GPIOx)
{
#ifdef Rest_controller

if(GPIOx == GPIOA)
{
	CLK_GPIOA_RST
}
else if(GPIOx == GPIOB)
{
	CLK_GPIOB_RST
}
else if(GPIOx == GPIOC)
{
	CLK_GPIOC_RST
}
else if(GPIOx == GPIOD)
{
	CLK_GPIOD_RST

}


#else

GPIOx->CRL  = 0x44444444;
GPIOx->CRH  = 0x44444444;
GPIOx->BRR  = 0x00000000;
GPIOx->BSRR = 0x00000000;
GPIOx->LCKR = 0x00000000;
GPIOx->ODR  = 0x00000000;

#endif
}

/**================================================================
* @Fn			- GPIO_init
* @brief		- Read the specified pin value (HIGH , LOW)
* @param [in]   - GPIOx      : select the GPIO port (from A to E)
* @param [in]   - pin_number : specify the pin which wanted to read
* @retval       - the value of the pin (HIGH , LOW)[ return value according to //@ref GPIO_status_Definition ]
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

uint8_t GPIO_Read_Pin(GPIO_t *GPIOx , uint16_t pin_number)
{
	uint8_t status=0 ;

	if(((uint16_t)GPIOx->IDR & pin_number) != GPIO_status_RESET)
	{
		status = GPIO_status_SET ;
	}
	else
	{
		status = GPIO_status_RESET ;
	}

	return (status);
}

/**================================================================
* @Fn			- GPIO_init
* @brief		- Read the value of the specified port
* @param [in]   - GPIOx     : select the GPIO port (from A to E)
* @retval       - port value
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

uint16_t GPIO_Read_Port(GPIO_t *GPIOx)
{
	uint16_t status =0;

	status = (uint16_t)GPIOx->IDR;

	return(status);
}

/**================================================================
* @Fn			- GPIO_init
* @brief		- specify the output of the pin
* @param [in]   - GPIOx      : select the GPIO port (from A to E)
* @param [in]   - pin_number : specify the pin which wanted to read
* @param [in]   - value		 : HIGH or LOW
* @retval       - none
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

void GPIO_Write_Pin(GPIO_t *GPIOx , uint16_t pin_number , uint8_t value)
{
	if(value == GPIO_status_SET)
	{
		GPIOx->BSRR = (uint32_t)pin_number;
	}
	else
	{
		GPIOx->BRR = (uint32_t)pin_number;
	}


}

/**================================================================
* @Fn			- GPIO_Write_Port
* @brief		- specify the output of the port
* @param [in]   - GPIOx      : select the GPIO port (from A to E)
* @param [in]   - value		 : HIGH or LOW
* @retval       - none
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

void GPIO_Write_Port(GPIO_t *GPIOx , uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}

/**================================================================
* @Fn			- GPIO_Toggle_Pin
* @brief		- toggle the specified pin
* @param [in]   - GPIOx      : select the GPIO port (from A to E)
* @param [in]   - pin_number : specify the pin which wanted to toggle
* @retval       - none
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

void GPIO_Toggle_Pin(GPIO_t *GPIOx , uint16_t pin_number)
{
	GPIOx->ODR ^= pin_number;
}

/**================================================================
* @Fn			- GPIO_Lock_Pin
* @brief		- lock the specified pin
* @param [in]   - GPIOx      : select the GPIO port (from A to E)
* @param [in]   - pin_number : specify the pin which wanted to toggle
* @retval       - return value according to //@ref GPIO_LOCK_Definition
* Note			- GPIOx 		: pointer to GPIO_register structure
*/

uint8_t GPIO_Lock_Pin(GPIO_t *GPIOx , uint16_t pin_number)
{
	GPIOx->LCKR |= pin_number;
	//write 1
	GPIOx->LCKR |= (1<<16);
	//write 0
	GPIOx->LCKR &= ~(1<<16);
	//write 1
	GPIOx->LCKR |= (1<<16);
	//read 0
	GPIOx->LCKR = GPIOx->LCKR ;
	//read 1 (confirm)
	if(((GPIOx->LCKR)&(1<<16))>>16)
	{
		return (GPIO_LOCK_ENABLE);
	}
	else
	{
		return (GPIO_LOCK_ERORR);
	}

}

