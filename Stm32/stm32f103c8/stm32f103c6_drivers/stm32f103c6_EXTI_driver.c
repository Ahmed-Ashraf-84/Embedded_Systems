/*
 * stm32f103c6_EXTI_driver.c
 *
 *  Created on: Sep 9, 2023
 *      Author: Ahmed Ashraf
 */

#include "stm32f103c6_GPIO_driver.h"
#include "stm32f103c6_EXTI_driver.h"
#include "stm32f103c6_LQFP48.h"


#define AFIO_GPIO_Mapping(x) 	(	(x == GPIOA)?0:\
									(x == GPIOB)?1:\
									(x == GPIOC)?2:\
									(x == GPIOD)?3:0 )


void (* GP_intertupt[15] )(void);


void EXTI_RST(void)
{
	EXTI->EMR 	= 0x00000000;
	EXTI->FTSR 	= 0x00000000;
	EXTI->IMR 	= 0x00000000;
	EXTI->PR 	= 0x00000000;
	EXTI->RTSR 	= 0x00000000;
	EXTI->SWIER = 0x00000000;

	//DISable EXTI from NVIC
	EXTI0_DISABLE
	EXTI1_DISABLE
	EXTI2_DISABLE
	EXTI3_DISABLE
	EXTI4_DISABLE
	EXTI5_DISABLE
	EXTI6_DISABLE
	EXTI7_DISABLE
	EXTI8_DISABLE
	EXTI9_DISABLE
	EXTI10_DISABLE
	EXTI11_DISABLE
	EXTI12_DISABLE
	EXTI13_DISABLE
	EXTI14_DISABLE
	EXTI15_DISABLE

}

/*static uint8_t portx(GPIO_t *port)
{
	uint8_t ret_value=0;

	if(port == GPIOA)
	{
		ret_value =0;
	}
	else if(port == GPIOB)
	{
		ret_value =1;
	}
	else if(port == GPIOC)
	{
		ret_value =2;
	}
	else if(port == GPIOD)
	{
		ret_value =3;
	}

	return (ret_value);

}
*/
static void EXTIX_ENABLE(uint16_t pin_number)
{
	switch(pin_number)
	{
	case PIN0 :
		EXTI0_ENABLE
		break;
	case PIN1 :
			EXTI1_ENABLE
			break;

	case PIN2 :
			EXTI2_ENABLE
			break;
	case PIN3 :
			EXTI3_ENABLE
			break;
	case PIN4 :
			EXTI4_ENABLE
			break;
	case PIN5 :
			EXTI5_ENABLE
			break;
	case PIN6 :
			EXTI6_ENABLE
			break;
	case PIN7 :
			EXTI7_ENABLE
			break;
	case PIN8 :
			EXTI8_ENABLE
			break;
	case PIN9 :
			EXTI9_ENABLE
			break;
	case PIN10 :
			EXTI10_ENABLE
			break;
	case PIN11 :
			EXTI11_ENABLE
			break;
	case PIN12 :
			EXTI12_ENABLE
			break;
	case PIN13 :
			EXTI13_ENABLE
			break;
	case PIN14 :
			EXTI14_ENABLE
			break;
	case PIN15 :
			EXTI15_ENABLE
			break;
	}

}

void EXTI_init(EXTI_config_t *EXTIx)
{
	GPIO_PIN_config_t pin_config ;

	pin_config.GPIO_MODE=MODE_INPUT_FLO;
	pin_config.GPIO_PIN_Number=EXTIx->PORT_PIN.GPIO_PIN_Number;

	GPIO_init(EXTIx->PORT_PIN.GPIO_PORT ,&pin_config );			//input floating
	/*
	if((EXTIx->PORT_PIN->PIN_config->GPIO_PIN_Number)<=PIN3)
	{
		AFIO->EXTICR1 = (uint32_t)portx(EXTIx->PORT_PIN->GPIO_PORT);
	}
	else if(((EXTIx->PORT_PIN->PIN_config->GPIO_PIN_Number)>PIN3) &&
			((EXTIx->PORT_PIN->PIN_config->GPIO_PIN_Number)<=PIN7) )
	{
		AFIO->EXTICR2 = (uint32_t)portx(EXTIx->PORT_PIN->GPIO_PORT);
	}
	else if(((EXTIx->PORT_PIN->PIN_config->GPIO_PIN_Number)>PIN7) &&
			((EXTIx->PORT_PIN->PIN_config->GPIO_PIN_Number)<=PIN11) )
	{
		AFIO->EXTICR3 = (uint32_t)portx(EXTIx->PORT_PIN->GPIO_PORT);
	}
	else
	{
		AFIO->EXTICR4 = (uint32_t)portx(EXTIx->PORT_PIN->GPIO_PORT);
	}
	*/

	uint8_t AFIO_EXTICRx        = (EXTIx->PORT_PIN.LINE_Number)/4;
	uint8_t AFIO_EXTICRx_pos    = ((EXTIx->PORT_PIN.LINE_Number)%4)*4;
	AFIO->EXTICR[AFIO_EXTICRx] &= ~(0xF << AFIO_EXTICRx_pos) ;

	AFIO->EXTICR[AFIO_EXTICRx] |= ((AFIO_GPIO_Mapping(EXTIx->PORT_PIN.GPIO_PORT))<<AFIO_EXTICRx_pos);




	//=================================================================

	//trigger
	if((EXTIx->PIN_Trigger)==Rising_Trigger)
	{
		EXTI->RTSR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
	}
	else if((EXTIx->PIN_Trigger)==Falling_Trigger)
	{
		EXTI->FTSR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
	}
	else
	{
		EXTI->RTSR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
		EXTI->FTSR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
	}
	//===================

	EXTIX_ENABLE(EXTIx->PORT_PIN.GPIO_PIN_Number);
	EXTI->IMR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);

	GP_intertupt[EXTIx->PORT_PIN.LINE_Number] = EXTIx->FUN_POINTER ;




}

void EXTI_update(EXTI_config_t *EXTIx,uint8_t interrupt)
{
	if(interrupt==interrupt_ENABLE)
	{
		EXTI->IMR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
	}
	else
	{
		EXTI->IMR &= ~(EXTIx->PORT_PIN.GPIO_PIN_Number);
	}


}

void SW_interrupt(EXTI_config_t *EXTIx,uint8_t interrupt)
{
	if(interrupt==interrupt_ENABLE)
		{
			EXTI->SWIER |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
		}
		else
		{
			EXTI->PR |= (EXTIx->PORT_PIN.GPIO_PIN_Number);
		}
}

void EXTI0_IRQHandler(void)
{
	EXTI->PR |= (1<<0);

	GP_intertupt[0]();
}

void EXTI1_IRQHandler(void)
{
	EXTI->PR |= (1<<1);

	GP_intertupt[1]();
}

void EXTI2_IRQHandler(void)
{
	EXTI->PR |= (1<<2);

	GP_intertupt[2]();
}

void EXTI3_IRQHandler(void)
{
	EXTI->PR |= (1<<3);

	GP_intertupt[3]();
}

void EXTI4_IRQHandler(void)
{
	EXTI->PR |= (1<<4);

	GP_intertupt[4]();
}

void EXTI9_5_IRQHandler(void)
{
	if (EXTI->PR & 1<<5)	{EXTI->PR |= (1<<5); GP_intertupt[5]();}
	if (EXTI->PR & 1<<6)	{EXTI->PR |= (1<<6); GP_intertupt[6]();}
	if (EXTI->PR & 1<<7)	{EXTI->PR |= (1<<7); GP_intertupt[7]();}
	if (EXTI->PR & 1<<8)	{EXTI->PR |= (1<<8); GP_intertupt[8]();}
	if (EXTI->PR & 1<<9)	{EXTI->PR |= (1<<9); GP_intertupt[9]();}
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI->PR & 1<<10)	{EXTI->PR |= (1<<10); GP_intertupt[10]();}
	if (EXTI->PR & 1<<11)	{EXTI->PR |= (1<<11); GP_intertupt[11]();}
	if (EXTI->PR & 1<<12)	{EXTI->PR |= (1<<12); GP_intertupt[12]();}
	if (EXTI->PR & 1<<13)	{EXTI->PR |= (1<<13); GP_intertupt[13]();}
	if (EXTI->PR & 1<<14)	{EXTI->PR |= (1<<14); GP_intertupt[14]();}
	if (EXTI->PR & 1<<15)	{EXTI->PR |= (1<<15); GP_intertupt[15]();}
}












