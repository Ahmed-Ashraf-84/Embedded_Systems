/*
 * stm32f103c6_USART_driver.c
 *
 *  Created on: Sep 24, 2023
 *      Author: Ahmed Ashraf
 */

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6_USART_driver.h"

//void (*USARTx_G_IRQ [5]) (void);
void(*USARTx_G_IRQ)(void);

void USART_init(USART_config_t * USARTx)
{
	uint16_t Baud_rate_register =0;
	uint16_t DIV_Mantissa =0;
	uint16_t DIV_Fraction =0;

	if((USARTx->USARTx)==USART1)
	{
		CLK_USART1_EN

		Baud_rate_register = (RCC_GET_PCLK2_CLK()/(16*(USARTx->Baud_rates)))*100;
		DIV_Mantissa = Baud_rate_register/100 ;
		DIV_Fraction = (uint16_t)((Baud_rate_register%100)*(16/100));

	}
	else if((USARTx->USARTx)==USART2)
	{
		CLK_USART2_EN

		Baud_rate_register = (RCC_GET_PCLK1_CLK()/(16*(USARTx->Baud_rates)))*100;
		DIV_Mantissa = Baud_rate_register/100 ;
		DIV_Fraction = (uint16_t)((Baud_rate_register%100)*(16/100));
	}
	else
	{
		CLK_USART3_EN

		Baud_rate_register = (RCC_GET_PCLK1_CLK()/(16*(USARTx->Baud_rates)))*100;
		DIV_Mantissa = Baud_rate_register/100 ;
		DIV_Fraction = (uint16_t)((Baud_rate_register%100)*(16/100));
	}

	//Enable the USART by writing the UE bit in USART_CR1 register to 1
	(USARTx->USARTx)->CR1.UE = 1;
	//Program the M bit in USART_CR1 to define the word length.
	(USARTx->USARTx)->CR1.M = USARTx->payload_length ;
	//Program the number of stop bits in USART_CR2.
	(USARTx->USARTx)->CR2.STOP = USARTx->Stop_bits ;
	//Program parity bits in USART_CR1.
	(USARTx->USARTx)->CR1.PS_PCE = USARTx->Parity_bits ;
	//Select the desired baud rate using the USART_BRR register.
	(USARTx->USARTx)->BRR.DIV_Fraction = (DIV_Fraction & 0xF) ;
	(USARTx->USARTx)->BRR.DIV_Mantissa = (DIV_Mantissa & 0x1FFF) ;
	//Set the TE bit in USART_CR1 to send an idle frame as first transmission
	(USARTx->USARTx)->CR1.RE_TE = USARTx->Mode_TX_RX ;
	//program the flow control bits
	(USARTx->USARTx)->CR3.RTS_CTS = USARTx->HW_Flow_ctrl ;


	if((USARTx->IRQ_ENABLE) != interrupt_DISABLED)
	{
		(USARTx->USARTx)->CR1.RXNEIE_TCIE_TXEIE_PEIE = USARTx->IRQ_ENABLE ;
		USARTx_G_IRQ = USARTx->ptr_IRQ_call_back; //fun_IRQ
		if((USARTx->USARTx)==USART1)
		{
			USART1_ENABLE_ISR

		}
		else if((USARTx->USARTx)==USART2)
		{
			USART2_ENABLE_ISR
		}
		else
		{
			USART3_ENABLE_ISR
		}


	}



}
void USART_deit(USART_config_t * USARTx)
{
	if((USARTx->USARTx)==USART1)
	{
		CLK_USART1_RST
	}
	else if((USARTx->USARTx)==USART2)
	{
		CLK_USART2_RST
	}
	else
	{
		CLK_USART3_RST
	}
}
void USART_AFIO_Set_Pins(USART_config_t * USARTx)
{

	GPIO_PIN_config_t pinconfig ;

	if((USARTx->USARTx)==USART1)
		{
		if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS) )
					{
							//A11 CTS
							pinconfig.GPIO_PIN_Number = PIN11;
							pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
							pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
							GPIO_init(GPIOA, &pinconfig);
					}
		if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_RTS) )
					{
							//A12 RTS
							pinconfig.GPIO_PIN_Number = PIN12;
							pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
							pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
							GPIO_init(GPIOA, &pinconfig);
					}
					//A9 TX
					pinconfig.GPIO_PIN_Number = PIN9;
					pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
					pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
					GPIO_init(GPIOA, &pinconfig);
					//A10 RX
					pinconfig.GPIO_PIN_Number = PIN10;
					pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
					pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
					GPIO_init(GPIOA, &pinconfig);
		}
		else if((USARTx->USARTx)==USART2)
		{
			if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS) )
					{
							//A0 CTS
							pinconfig.GPIO_PIN_Number = PIN0;
							pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
							pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
							GPIO_init(GPIOA, &pinconfig);
					}
			if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_RTS) )
					{
							//A1 RTS
							pinconfig.GPIO_PIN_Number = PIN1;
							pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
							pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
							GPIO_init(GPIOA, &pinconfig);
					}
					//A2 TX
					pinconfig.GPIO_PIN_Number = PIN2;
					pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
					pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
					GPIO_init(GPIOA, &pinconfig);
					//A3 RX
					pinconfig.GPIO_PIN_Number = PIN3;
					pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
					pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
					GPIO_init(GPIOA, &pinconfig);
		}
		else
		{
			if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS) )
						{
								//B13 CTS
								pinconfig.GPIO_PIN_Number = PIN13;
								pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
								pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
								GPIO_init(GPIOB, &pinconfig);
						}
			if((USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_CTS_RTS) ||(USARTx->HW_Flow_ctrl) == (HW_Flow_ctrl_RTS) )
						{
								//B14 RTS
								pinconfig.GPIO_PIN_Number = PIN14;
								pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
								pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
								GPIO_init(GPIOB, &pinconfig);
						}
						//B10 TX
						pinconfig.GPIO_PIN_Number = PIN10;
						pinconfig.GPIO_MODE = MODE_OUTPUT_AF_PP ;
						pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
						GPIO_init(GPIOB, &pinconfig);
						//B11 RX
						pinconfig.GPIO_PIN_Number = PIN11;
						pinconfig.GPIO_MODE = MODE_INPUT_FLO ;
						pinconfig.GPIO_OUTPUT_SPEED = OUTPUT_SPEED_10 ;
						GPIO_init(GPIOB, &pinconfig);
		}
}
void USART_Send_data(USART_config_t * USARTx)
{
	if(USARTx->polling == polling_ENABLED)
	{
		while(! (USARTx->USARTx->SR.TXE));
	}

	if(USARTx->payload_length == Data_bits_9)
			USARTx->USARTx->DR.DR=(*(USARTx->Buffer)& 0x1FF);
	else
		USARTx->USARTx->DR.DR=(*(USARTx->Buffer)& 0xFF);
}
void USART_Receive_data(USART_config_t * USARTx)
{
	if(USARTx->polling == polling_ENABLED)
	{
		while(! (USARTx->USARTx->SR.RXNE));
	}

	if(USARTx->payload_length == Data_bits_9)
	{

		if(USARTx->Parity_bits == Parity_DISABLED)
		{
			*(USARTx->Buffer) = USARTx->USARTx->DR.DR ;
		}
		else
		{
			*(USARTx->Buffer) = ( USARTx->USARTx->DR.DR) & 0xFF ;
		}
	}

	else
	{
		if(USARTx->Parity_bits == Parity_DISABLED)
		{
			*(USARTx->Buffer) = ( USARTx->USARTx->DR.DR) & 0xFF ;
		}
		else
		{
			*(USARTx->Buffer) = ( USARTx->USARTx->DR.DR) & 0x7F ;
		}
	}

}
void USART_Transmission_complete(USART_config_t * USARTx)
{
	while(!(USARTx->USARTx->SR.TC));
}

void USART3_IRQHandler(void)
{
	/*uint8_t flag = 0 ;
	if(USART3->SR.PE)
	{
		flag = PEIE_ENABLED ;
	}
	else if(USART3->SR.RXNE)
	{
		flag = RXNEIE_ENABLED ;
	}
	else if(USART3->SR.TC)
	{
		flag = TCIE_ENABLED ;
	}
	else
	{
		flag = TXEIE_ENABLED ;
	}
*/   // send flag to the user function to specify the interrupt reason
	// flag >>= 1 ;   if many interrupts enabled     array

	USARTx_G_IRQ();
}

void USART2_IRQHandler(void)
{
	USARTx_G_IRQ();
}
//USART2_IRQHandler

void USART1_IRQHandler(void)
{
	USARTx_G_IRQ();
}
//USART1_IRQHandler


